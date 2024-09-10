/* <dclarg_text>:
 * Allocate (or re-allocate) a 'DCLARG' entry, given the text-buffer to load.
 * This procedure can be used to allocate a new entry (if 'this_' is null), or
 * to reallocate an entry when the text buffer's size has altered.  The status
 * and field indices are unaltered.
 */
DCLARG	*dclarg_text(
	DCLARG	*this_,		/* Entry to (re)allocate	*/
	DCLARG	*last_,		/* Entry containing link to it	*/
	char	*s_,		/* Text-buffer (mustn't be null)*/
	int	uc)		/* TRUE if uppercase		*/
{
	size_t	size	= sizeof(DCLARG) + strlen(s_) + 2;
	char	*text_;

	if (this_)	this_	= realloc (this_, size);
	else		this_	= calloc (1, size);

	this_->dcl_size	= strlen(s_);
	text_	= (char *) this_ + sizeof(DCLARG);

	/*
	 * Strip out blanks from the string as I load it.  (patch: Should look
	 * for quoted strings here.)
	 */
	for (this_->dcl_text = text_; *s_; s_++)
	{
		if (!uc || !isspace(*s_))	*text_++ = *s_;
	}
	*text_ = EOS;

	/*
	 * Do uppercase conversion if needed.  This is used for all filenames
	 * and option strings.  Error messages are left alone.
	 */
	if (uc)
	{
		for (text_ = this_->dcl_text; *text_; text_++)
			*text_ = _toupper(*text_);
	}
	if (last_ != 0)
		last_->dcl_next = (DCLARG *)this_;
	/*
	 * Don't allow empty name ".;" -- trim it off
	 */
	if ((size = strlen(text_ = this_->dcl_text)) > 2)
	{
		if (!strcmp(text_ + size - 2, ".;"))
			text_[size-2] = EOS;
	}
	return (this_);
}