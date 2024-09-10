void VarDeclaration::semantic(Scope *sc)
{
#if 0
    printf("VarDeclaration::semantic('%s', parent = '%s')\n", toChars(), sc->parent->toChars());
    printf(" type = %s\n", type ? type->toChars() : "null");
    printf(" stc = x%x\n", sc->stc);
    printf(" storage_class = x%x\n", storage_class);
    printf("linkage = %d\n", sc->linkage);
    //if (strcmp(toChars(), "mul") == 0) halt();
#endif

    storage_class |= sc->stc;
    if (storage_class & STCextern && init)
        error("extern symbols cannot have initializers");

    AggregateDeclaration *ad = isThis();
    if (ad)
        storage_class |= ad->storage_class & STC_TYPECTOR;

    /* If auto type inference, do the inference
     */
    int inferred = 0;
    if (!type)
    {   inuse++;
        type = init->inferType(sc);
        inuse--;
        inferred = 1;

        /* This is a kludge to support the existing syntax for RAII
         * declarations.
         */
        storage_class &= ~STCauto;
        originalType = type;
    }
    else
    {   if (!originalType)
            originalType = type;
        type = type->semantic(loc, sc);
    }
    //printf(" semantic type = %s\n", type ? type->toChars() : "null");

    type->checkDeprecated(loc, sc);
    linkage = sc->linkage;
    this->parent = sc->parent;
    //printf("this = %p, parent = %p, '%s'\n", this, parent, parent->toChars());
    protection = sc->protection;
    //printf("sc->stc = %x\n", sc->stc);
    //printf("storage_class = x%x\n", storage_class);

#if DMDV2
    if (storage_class & STCgshared && global.params.safe && !sc->module->safe)
    {
        error("__gshared not allowed in safe mode; use shared");
    }
#endif

    Dsymbol *parent = toParent();
    FuncDeclaration *fd = parent->isFuncDeclaration();

    Type *tb = type->toBasetype();
    if (tb->ty == Tvoid && !(storage_class & STClazy))
    {   error("voids have no value");
        type = Type::terror;
        tb = type;
    }
    if (tb->ty == Tfunction)
    {   error("cannot be declared to be a function");
        type = Type::terror;
        tb = type;
    }
    if (tb->ty == Tstruct)
    {   TypeStruct *ts = (TypeStruct *)tb;

        if (!ts->sym->members)
        {
            error("no definition of struct %s", ts->toChars());
        }
    }
    if ((storage_class & STCauto) && !inferred)
       error("storage class 'auto' has no effect if type is not inferred, did you mean 'scope'?");

    if (tb->ty == Ttuple)
    {   /* Instead, declare variables for each of the tuple elements
         * and add those.
         */
        TypeTuple *tt = (TypeTuple *)tb;
        size_t nelems = Parameter::dim(tt->arguments);
        Objects *exps = new Objects();
        exps->setDim(nelems);
        Expression *ie = init ? init->toExpression() : NULL;

        for (size_t i = 0; i < nelems; i++)
        {   Parameter *arg = Parameter::getNth(tt->arguments, i);

            OutBuffer buf;
            buf.printf("_%s_field_%zu", ident->toChars(), i);
            buf.writeByte(0);
            const char *name = (const char *)buf.extractData();
            Identifier *id = Lexer::idPool(name);

            Expression *einit = ie;
            if (ie && ie->op == TOKtuple)
            {   einit = (Expression *)((TupleExp *)ie)->exps->data[i];
            }
            Initializer *ti = init;
            if (einit)
            {   ti = new ExpInitializer(einit->loc, einit);
            }

            VarDeclaration *v = new VarDeclaration(loc, arg->type, id, ti);
            //printf("declaring field %s of type %s\n", v->toChars(), v->type->toChars());
            v->semantic(sc);

#if !IN_LLVM
// removed for LDC since TupleDeclaration::toObj already creates the fields;
// adding them to the scope again leads to duplicates
            if (sc->scopesym)
            {   //printf("adding %s to %s\n", v->toChars(), sc->scopesym->toChars());
                if (sc->scopesym->members)
                    sc->scopesym->members->push(v);
            }
#endif

            Expression *e = new DsymbolExp(loc, v);
            exps->data[i] = e;
        }
        TupleDeclaration *v2 = new TupleDeclaration(loc, ident, exps);
        v2->isexp = 1;
        aliassym = v2;
        return;
    }

    if (storage_class & STCconst && !init && !fd)
        // Initialize by constructor only
        storage_class = (storage_class & ~STCconst) | STCctorinit;

    if (isConst())
    {
    }
    else if (isStatic())
    {
    }
    else if (isSynchronized())
    {
        error("variable %s cannot be synchronized", toChars());
    }
    else if (isOverride())
    {
        error("override cannot be applied to variable");
    }
    else if (isAbstract())
    {
        error("abstract cannot be applied to variable");
    }
    else if (storage_class & STCtemplateparameter)
    {
    }
    else if (storage_class & STCctfe)
    {
    }
    else
    {
        AggregateDeclaration *aad = sc->anonAgg;
        if (!aad)
            aad = parent->isAggregateDeclaration();
        if (aad)
        {
#if DMDV2
            assert(!(storage_class & (STCextern | STCstatic | STCtls | STCgshared)));

            if (storage_class & (STCconst | STCimmutable) && init)
            {
                if (!type->toBasetype()->isTypeBasic())
                    storage_class |= STCstatic;
            }
            else
#endif
                aad->addField(sc, this);
        }

        InterfaceDeclaration *id = parent->isInterfaceDeclaration();
        if (id)
        {
            error("field not allowed in interface");
        }

        /* Templates cannot add fields to aggregates
         */
        TemplateInstance *ti = parent->isTemplateInstance();
        if (ti)
        {
            // Take care of nested templates
            while (1)
            {
                TemplateInstance *ti2 = ti->tempdecl->parent->isTemplateInstance();
                if (!ti2)
                    break;
                ti = ti2;
            }

            // If it's a member template
            AggregateDeclaration *ad = ti->tempdecl->isMember();
            if (ad && storage_class != STCundefined)
            {
                error("cannot use template to add field to aggregate '%s'", ad->toChars());
            }
        }
    }

#if DMDV2
    if ((storage_class & (STCref | STCparameter | STCforeach)) == STCref &&
        ident != Id::This)
    {
        error("only parameters or foreach declarations can be ref");
    }
#endif

    if (type->isscope() && !noscope)
    {
        if (storage_class & (STCfield | STCout | STCref | STCstatic) || !fd)
        {
            error("globals, statics, fields, ref and out parameters cannot be auto");
        }

        if (!(storage_class & STCscope))
        {
            if (!(storage_class & STCparameter) && ident != Id::withSym)
                error("reference to scope class must be scope");
        }
    }

    enum TOK op = TOKconstruct;
    if (!init && !sc->inunion && !isStatic() && !isConst() && fd &&
        !(storage_class & (STCfield | STCin | STCforeach)) &&
        type->size() != 0)
    {
        // Provide a default initializer
        //printf("Providing default initializer for '%s'\n", toChars());
        if (type->ty == Tstruct &&
            ((TypeStruct *)type)->sym->zeroInit == 1)
        {   /* If a struct is all zeros, as a special case
             * set it's initializer to the integer 0.
             * In AssignExp::toElem(), we check for this and issue
             * a memset() to initialize the struct.
             * Must do same check in interpreter.
             */
            Expression *e = new IntegerExp(loc, 0, Type::tint32);
            Expression *e1;
            e1 = new VarExp(loc, this);
            e = new AssignExp(loc, e1, e);
            e->op = TOKconstruct;
            e->type = e1->type;         // don't type check this, it would fail
            init = new ExpInitializer(loc, e);
            return;
        }
        else if (type->ty == Ttypedef)
        {   TypeTypedef *td = (TypeTypedef *)type;
            if (td->sym->init)
            {   init = td->sym->init;
                ExpInitializer *ie = init->isExpInitializer();
                if (ie)
                    // Make copy so we can modify it
                    init = new ExpInitializer(ie->loc, ie->exp);
            }
            else
                init = getExpInitializer();
        }
        else
        {
            init = getExpInitializer();
        }
        // Default initializer is always a blit
        op = TOKblit;
    }

    if (init)
    {
        sc = sc->push();
        sc->stc &= ~(STC_TYPECTOR | STCpure | STCnothrow | STCref);

        ArrayInitializer *ai = init->isArrayInitializer();
        if (ai && tb->ty == Taarray)
        {
            init = ai->toAssocArrayInitializer();
        }

        StructInitializer *si = init->isStructInitializer();
        ExpInitializer *ei = init->isExpInitializer();

        // See if initializer is a NewExp that can be allocated on the stack
        if (ei && isScope() && ei->exp->op == TOKnew)
        {   NewExp *ne = (NewExp *)ei->exp;
            if (!(ne->newargs && ne->newargs->dim))
            {   ne->onstack = 1;
                onstack = 1;
                if (type->isBaseOf(ne->newtype->semantic(loc, sc), NULL))
                    onstack = 2;
            }
        }

        // If inside function, there is no semantic3() call
        if (sc->func)
        {
            // If local variable, use AssignExp to handle all the various
            // possibilities.
            if (fd && !isStatic() && !isConst() && !init->isVoidInitializer())
            {
                //printf("fd = '%s', var = '%s'\n", fd->toChars(), toChars());
                if (!ei)
                {
                    Expression *e = init->toExpression();
                    if (!e)
                    {
                        init = init->semantic(sc, type);
                        e = init->toExpression();
                        if (!e)
                        {   error("is not a static and cannot have static initializer");
                            return;
                        }
                    }
                    ei = new ExpInitializer(init->loc, e);
                    init = ei;
                }

                Expression *e1 = new VarExp(loc, this);

                Type *t = type->toBasetype();
                if (t->ty == Tsarray && !(storage_class & (STCref | STCout)))
                {
                    ei->exp = ei->exp->semantic(sc);
                    if (!ei->exp->implicitConvTo(type))
                    {
                        int dim = ((TypeSArray *)t)->dim->toInteger();
                        // If multidimensional static array, treat as one large array
                        while (1)
                        {
                            t = t->nextOf()->toBasetype();
                            if (t->ty != Tsarray)
                                break;
                            dim *= ((TypeSArray *)t)->dim->toInteger();
                            e1->type = new TypeSArray(t->nextOf(), new IntegerExp(0, dim, Type::tindex));
                        }
                    }
                    e1 = new SliceExp(loc, e1, NULL, NULL);
                }
                else if (t->ty == Tstruct)
                {
                    ei->exp = ei->exp->semantic(sc);
                    ei->exp = resolveProperties(sc, ei->exp);
                    StructDeclaration *sd = ((TypeStruct *)t)->sym;
#if DMDV2
                    /* Look to see if initializer is a call to the constructor
                     */
                    if (sd->ctor &&             // there are constructors
                        ei->exp->type->ty == Tstruct && // rvalue is the same struct
                        ((TypeStruct *)ei->exp->type)->sym == sd &&
                        ei->exp->op == TOKstar)
                    {
                        /* Look for form of constructor call which is:
                         *    *__ctmp.ctor(arguments...)
                         */
                        PtrExp *pe = (PtrExp *)ei->exp;
                        if (pe->e1->op == TOKcall)
                        {   CallExp *ce = (CallExp *)pe->e1;
                            if (ce->e1->op == TOKdotvar)
                            {   DotVarExp *dve = (DotVarExp *)ce->e1;
                                if (dve->var->isCtorDeclaration())
                                {   /* It's a constructor call, currently constructing
                                     * a temporary __ctmp.
                                     */
                                    /* Before calling the constructor, initialize
                                     * variable with a bit copy of the default
                                     * initializer
                                     */
                                    Expression *e = new AssignExp(loc, new VarExp(loc, this), t->defaultInit(loc));
                                    e->op = TOKblit;
                                    e->type = t;
                                    ei->exp = new CommaExp(loc, e, ei->exp);

                                    /* Replace __ctmp being constructed with e1
                                     */
                                    dve->e1 = e1;
                                    return;
                                }
                            }
                        }
                    }
#endif
                    if (!ei->exp->implicitConvTo(type))
                    {
                        /* Look for opCall
                         * See bugzilla 2702 for more discussion
                         */
                        Type *ti = ei->exp->type->toBasetype();
                        // Don't cast away invariant or mutability in initializer
                        if (search_function(sd, Id::call) &&
                            /* Initializing with the same type is done differently
                             */
                            !(ti->ty == Tstruct && t->toDsymbol(sc) == ti->toDsymbol(sc)))
                        {   // Rewrite as e1.call(arguments)
                            Expression * eCall = new DotIdExp(loc, e1, Id::call);
                            ei->exp = new CallExp(loc, eCall, ei->exp);
                        }
                    }
                }
                ei->exp = new AssignExp(loc, e1, ei->exp);
                ei->exp->op = TOKconstruct;
                canassign++;
                ei->exp = ei->exp->semantic(sc);
                canassign--;
                ei->exp->optimize(WANTvalue);
            }
            else
            {
                init = init->semantic(sc, type);
                if (fd && isConst() && !isStatic())
                {   // Make it static
                    storage_class |= STCstatic;
                }
            }
        }
        else if (isConst() || isFinal() ||
                 parent->isAggregateDeclaration())
        {
            /* Because we may need the results of a const declaration in a
             * subsequent type, such as an array dimension, before semantic2()
             * gets ordinarily run, try to run semantic2() now.
             * Ignore failure.
             */

            if (!global.errors && !inferred)
            {
                unsigned errors = global.errors;
                global.gag++;
                //printf("+gag\n");
                Expression *e;
                Initializer *i2 = init;
                inuse++;
                if (ei)
                {
                    e = ei->exp->syntaxCopy();
                    e = e->semantic(sc);
                    e = e->implicitCastTo(sc, type);
                }
                else if (si || ai)
                {   i2 = init->syntaxCopy();
                    i2 = i2->semantic(sc, type);
                }
                inuse--;
                global.gag--;
                //printf("-gag\n");
                if (errors != global.errors)    // if errors happened
                {
                    if (global.gag == 0)
                        global.errors = errors; // act as if nothing happened
#if DMDV2
                    /* Save scope for later use, to try again
                     */
                    scope = new Scope(*sc);
                    scope->setNoFree();
#endif
                }
                else if (ei)
                {
                    if (isDataseg() || (storage_class & STCmanifest))
                        e = e->optimize(WANTvalue | WANTinterpret);
                    else
                        e = e->optimize(WANTvalue);
                    switch (e->op)
                    {
                        case TOKint64:
                        case TOKfloat64:
                        case TOKstring:
                        case TOKarrayliteral:
                        case TOKassocarrayliteral:
                        case TOKstructliteral:
                        case TOKnull:
                            ei->exp = e;            // no errors, keep result
                            break;

                        default:
#if DMDV2
                            /* Save scope for later use, to try again
                             */
                            scope = new Scope(*sc);
                            scope->setNoFree();
#endif
                            break;
                    }
                }
                else
                    init = i2;          // no errors, keep result
            }
        }
        sc = sc->pop();
    }
}