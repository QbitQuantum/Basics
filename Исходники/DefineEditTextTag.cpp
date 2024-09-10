void
DefineEditTextTag::read(SWFStream& in, movie_definition& m)
{

	_rect = readRect(in);

	in.align();
	in.ensureBytes(2);
    
    int flags = in.read_u8();
	_hasText  = flags & (1 << 7);
	_wordWrap = flags & (1 << 6);
	_multiline = flags & (1 << 5);
	_password  = flags & (1 << 4);
	_readOnly  = flags & (1 << 3); 

    const bool hasColor = flags & (1 << 2); 
	const bool hasMaxChars = flags & (1 << 1); 
	const bool hasFont = flags & (1 << 0); 

    flags = in.read_u8();
	// 0: no font class, 1 font class and height, can't be true if has_font was true
	bool hasFontClass = flags & (1 << 7);
	if (hasFontClass && hasFont )
	{
		IF_VERBOSE_MALFORMED_SWF(
		    log_swferror("DefineEditText: hasFontClass can't be true if "
                "hasFont is true, ignoring");
		);