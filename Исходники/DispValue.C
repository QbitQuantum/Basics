// Initialization
void DispValue::init(DispValue *parent, int depth, string& value,
		     DispValueType given_type)
{
#if LOG_CREATE_VALUES
    std::clog << "Building value from " << quote(value) << "\n";
#endif

    // Be sure the value is not changed in memory
    value.consuming(true);

    const char *initial_value = value.chars();

    static const DispValueArray empty(0);
    _children = empty;

    if (background(value.length()))
    {
	clear();

	mytype = Simple;
	_value = "(Aborted)";
	value  = "Aborted\n";
	return;
    }

    mytype = given_type;
    if (mytype == UnknownType && 
	(parent == 0 || parent->type() == List) && print_name.empty())
	mytype = Text;
    if (mytype == UnknownType && parent == 0 && is_user_command(print_name))
	mytype = List;
    if (mytype == UnknownType)
	mytype = determine_type(value);

    bool ignore_repeats = (parent != 0 && parent->type() == Array);

    char perl_type = '\0';

    switch (mytype)
    {

    case Simple:
    {
	_value = read_simple_value(value, depth, ignore_repeats);
#if LOG_CREATE_VALUES
	std::clog << mytype << ": " << quote(_value) << "\n";
#endif
	perl_type = '$';
	break;
    }

    case Text:
    {
	// Read in a line of text
	if (value.contains('\n'))
	    _value = value.through('\n');
	else
	    _value = value;
	value = value.after('\n');
#if LOG_CREATE_VALUES
	std::clog << mytype << ": " << quote(_value) << "\n";
#endif
	perl_type = '$';
	break;
    }

    case Pointer:
    {
	_value = read_pointer_value(value, ignore_repeats);
	_dereferenced = false;

#if LOG_CREATE_VALUES
	std::clog << mytype << ": " << quote(_value) << "\n";
#endif
	// Hide vtable pointers.
	if (_value.contains("virtual table") || _value.contains("vtable"))
	    myexpanded = false;
	perl_type = '$';

	// In Perl, pointers may be followed by indented `pointed to'
	// info.  Skip this.
	if (gdb->type() == PERL)
	{
	    while (value.contains("\n  ", 0))
	    {
		value = value.after("\n  ");
		value = value.from("\n");
	    }
	}		
	break;
    }

    case Array:
    {
	string base = normalize_base(myfull_name);

	_orientation = app_data.array_orientation;

#if LOG_CREATE_VALUES
	std::clog << mytype << ": " << "\n";
#endif

	read_array_begin(value, myaddr);

	// Check for `vtable entries' prefix.
	string vtable_entries = read_vtable_entries(value);
	if (!vtable_entries.empty())
	{
	    _children += parse_child(depth, vtable_entries, myfull_name);
	}

	// Read the array elements.  Assume that the type is the
	// same across all elements.
	DispValueType member_type = UnknownType;
	if (!_have_index_base)
	{
	    _index_base = index_base(base, depth);
	    _have_index_base = true;
	}
	int array_index = _index_base;

	// The array has at least one element.  Otherwise, GDB
	// would treat it as a pointer.
	do {
	    const char *repeated_value = value.chars();
	    string member_name = 
		gdb->index_expr("", itostring(array_index++));
	    DispValue *dv = parse_child(depth, value,
					add_member_name(base, member_name), 
					member_name, member_type);
	    member_type = dv->type();
	    _children += dv;

	    int repeats = read_repeats(value);

	    if (expand_repeated_values)
	    {
		// Create one value per repeat
		while (--repeats > 0)
		{
		    member_name = 
			gdb->index_expr("", itostring(array_index++));
		    string val = repeated_value;
		    DispValue *repeated_dv = 
			parse_child(depth, val, 
				    add_member_name(base, member_name),
				    member_name, member_type);
		    _children += repeated_dv;
		}
	    }
	    else
	    {
		// Show repetition in member
		if (repeats > 1)
		{
		    array_index--;

#if 0
		    // We use the GDB `artificial array' notation here,
		    // since repeat recognition is supported in GDB only.
		    member_name += "@" + itostring(repeats);

		    dv->full_name() = add_member_name(base, member_name);
		    dv->name()      = member_name;
#endif
		    dv->repeats()   = repeats;

		    array_index += repeats;
		}
	    }

	    if (background(value.length()))
	    {
		init(parent, depth, value);
		return;
	    }
	} while (read_array_next(value));
	read_array_end(value);

	// Expand only if at top-level.
	myexpanded = (depth == 0 || nchildren() <= 1);

#if LOG_CREATE_VALUES
	std::clog << mytype << " has " << nchildren() << " members\n";
#endif
	perl_type = '@';
	break;
    }

    case List:
	// Some DBXes issue the local variables via a frame line, just
	// like `set_date(d = 0x10003060, day_of_week = Sat, day = 24,
	// month = 12, year = 1994)'.  Make this more readable.
	munch_dump_line(value);

	// FALL THROUGH
    case Struct:
    {
	_orientation  = app_data.struct_orientation;
	_member_names = app_data.show_member_names;

	bool found_struct_begin   = false;
	bool read_multiple_values = false;
	
#if LOG_CREATE_VALUES
	std::clog << mytype << " " << quote(myfull_name) << "\n";
#endif
	string member_prefix = myfull_name;
	string member_suffix = "";
	if (mytype == List)
	{
	    member_prefix = "";
	    read_multiple_values = true;
	}
	else
	{
	    // In C and Java, `*' binds tighter than `.'
	    if (member_prefix.contains('*', 0))
	    {
		if (gdb->program_language() == LANGUAGE_C)
		{
		    // Use the C `->' operator instead
		    member_prefix.del("*");
		    if (member_prefix.contains('(', 0) &&
			member_prefix.contains(')', -1))
			member_prefix = unquote(member_prefix);

#if RUNTIME_REGEX
		    static regex rxchain("[-a-zA-Z0-9::_>.`]+");
#endif
		    if (member_prefix.matches(rxchain))
		    {
			// Simple chain of identifiers - prepend `->'
			member_prefix += "->";
		    }
		    else
		    {
			member_prefix.prepend("(");
			member_prefix += ")->";
		    }
		}
		else
		{
		    member_prefix.prepend("(");
		    member_prefix += ").";
		}
	    }
	    else if (gdb->program_language() == LANGUAGE_PERL)
	    {
		// In Perl, members of A are accessed as A{'MEMBER_NAME'}
		member_prefix = normalize_base(member_prefix) + "{'";
		member_suffix = "'}";
	    }
	    else if (gdb->program_language() == LANGUAGE_PHP)
	    {
		// In PHP, members of $A are accessed as $A['MEMBER_NAME']
		member_prefix = normalize_base(member_prefix) + "['";
		member_suffix = "']";
	    }
	    else if (gdb->program_language() == LANGUAGE_FORTRAN)
	    {
		// In Fortran, members of A are accessed as A%B
		member_prefix = normalize_base(member_prefix) + "%";
	    }
	    else
	    {
		// In all other languages, members are accessed as A.B
		member_prefix = normalize_base(member_prefix) + ".";
	    }

	    // In case we do not find a struct beginning, read only one value
	    found_struct_begin = read_struct_begin(value, myaddr);
	    read_multiple_values = found_struct_begin;
	}

	// Prepend base class in case of multiple inheritance
	// FIXME: This should be passed as an argument
	static string baseclass_prefix;
	member_prefix += baseclass_prefix;
	int base_classes = 0;

	bool more_values = true;
	while (more_values)
	{
	    // In a List, we may have `member' names like `(a + b)'.
	    // Don't be picky about this.
	    bool picky = (mytype == Struct);
	    string member_name = read_member_name(value, picky);

	    if (member_name.empty())
	    {
		// Some struct stuff that is not a member
		DispValue *dv = parse_child(depth, value, myfull_name, "");

		if (dv->type() == Struct)
		{
		    // What's this - a struct within a struct?  Just
		    // adopt the members.
		    // (This happens when we finally found the struct
		    // after having read all the AIX DBX base classes.)
		    for (int i = 0; i < dv->nchildren(); i++)
		    {
			DispValue *dv2 = dv->child(i)->link();
			_children += dv2;
		    }
		    dv->unlink();
		}
		else
		{
		    _children += dv;
		}

		more_values = read_multiple_values && read_struct_next(value);
	    }
	    else if (is_BaseClass_name(member_name))
	    {
		// Base class member
		string saved_baseclass_prefix = baseclass_prefix;
		base_classes++;

		if (base_classes > 1)
		{
		    // Multiple inheritance.  Be sure to
		    // reference further members unambiguously.
		    //
		    // Note: we don't do that for the first base class,
		    // because this might turn ambiguous again.
		    //
		    // Example:
		    //
		    //    Base
		    //    |   |
		    //    I1 I2
		    //     \ /
		    //      C
		    //
		    // Members of I1::Base are not prefixed, members
		    // of I2::Base get `I2::' as base class prefix.
		    // If we did this already for the first base class,
		    // members of both I1 and I2 would get `Base::' as
		    // base class prefix.

		    switch (gdb->program_language())
		    {
		    case LANGUAGE_C: // C++
			baseclass_prefix = unquote(member_name) + "::";
			break;

		    default:
			// Do nothing (yet)
			break;
		    }
		}

		DispValue *dv = 
		    parse_child(depth, value, myfull_name, member_name);
		_children += dv;

		baseclass_prefix = saved_baseclass_prefix;

		more_values = read_multiple_values && read_struct_next(value);

		// Skip a possible `members of CLASS:' prefix
		read_members_prefix(value);

		// AIX DBX does not place a separator between base
		// classes and the other members, so we always
		// continue reading after having found a base
		// class.  After all, the own class members are
		// still missing.
		if (mytype == Struct && !found_struct_begin)
		    more_values = true;
	    }
	    else
	    {
		// Ordinary member
		string full_name = "";

		if (member_name == " ")
		{
		    // Anonymous union
		    full_name = myfull_name;
		}
		
		if (member_name.contains('.'))
		{
		    if (gdb->has_quotes())
		    {
			// The member name contains `.' => quote it.  This
			// happens with vtable pointers on Linux (`_vptr.').
			full_name = member_prefix + quote(member_name, '\'') + 
			    member_suffix;
		    }
		    else
		    {
			// JDB (and others?) prepend the class name 
			// to inherited members.  Omit this.
			full_name = 
			    member_prefix + member_name.after('.', -1) + 
			    member_suffix;
		    }
		}
		
		if (full_name.empty())
		{
		    // Ordinary member
		    full_name = member_prefix + member_name + member_suffix;
		}

		DispValue *child = 
		    parse_child(depth, value, full_name, member_name);

		if (child->type() == Text)
		{
		    // Found a text as child - child value must be empty
		    string empty = "";
		    _children += 
			parse_child(depth, empty, full_name, member_name);

		    string v = child->value();
		    strip_space(v);
		    if (!v.empty())
			_children += child;
		}
		else
		{
		    _children += child;
		}

		more_values = read_multiple_values && read_struct_next(value);
	    }

	    if (background(value.length()))
	    {
		init(parent, depth, value);
		return;
	    }
	}

	if (mytype == List && !value.empty())
	{
	    // Add remaining value as text
	    _children += parse_child(depth, value, "");
	}

	if (found_struct_begin)
	{
	    // Skip the remainder
	    read_struct_end(value);
	}

	// Expand only if at top-level.
	myexpanded = (depth == 0 || nchildren() <= 1);

#if LOG_CREATE_VALUES
	std::clog << mytype << " "
		  << quote(myfull_name)
		  << " has " << nchildren() << " members\n";
#endif

	perl_type = '%';
	break;
    }

    case Reference:
    {
	myexpanded = true;

	int sep = value.index('@');
	sep = value.index(':', sep);

	string ref = value.before(sep);
	value = value.after(sep);

	string addr = gdb->address_expr(myfull_name);

	_children += parse_child(depth, ref, addr, myfull_name, Pointer);
	_children += parse_child(depth, value, myfull_name);

	if (background(value.length()))
	{
	    init(parent, depth, value);
	    return;
	}

	perl_type = '$';	// No such thing in Perl...
	break;
    }

    case Sequence:
    case UnknownType:
	assert(0);
	abort();
    }

    // Handle trailing stuff (`sequences')
    if (parent == 0 || parent->type() != Sequence)
    {
	bool need_clear = true;
	while (sequence_pending(value, parent))
	{
	    if (need_clear)
	    {
#if LOG_CREATE_VALUES
		std::clog << "Sequence detected at " << quote(value) << "\n";
#endif

		clear();
		value = initial_value;

		mytype = Sequence;

#if LOG_CREATE_VALUES
		std::clog << mytype << " " << quote(myfull_name) << "\n";
#endif

		need_clear = false;
	    }
	    
	    const char *old_value = value.chars();

	    DispValue *dv = parse_child(depth, value, myfull_name);

	    if (value == old_value)
	    {
		// Nothing consumed - stop here
		dv->unlink();
		break;
	    }
	    else if (dv->type() == Simple && dv->value().empty())
	    {
		// Empty value - ignore
		dv->unlink();
	    }
	    else
	    {
		_children += dv;
	    }
	}

#if LOG_CREATE_VALUES
	if (!need_clear)
	{
	    std::clog << mytype << " "
		      << quote(myfull_name)
		      << " has " << nchildren() << " members\n";
	}
#endif
    }

    if (gdb->program_language() == LANGUAGE_PERL && is_perl_prefix(perl_type))
    {
	// Set new type
	if (!myfull_name.empty() && is_perl_prefix(myfull_name[0]))
	    myfull_name[0] = perl_type;
    }

    background(value.length());
    changed = true;
}