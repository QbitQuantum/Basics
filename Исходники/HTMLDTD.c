/* This function fills the "tags" part of the HTML_dtd structure with
   what we want to use, either tags_table0 or tags_table1.  Note that it
   has to be called at least once before HTML_dtd is used, otherwise
   the HTML_dtd contents will be invalid!  This could be coded in a way
   that would make an initialisation call unnecessary, but my C knowledge
   is limited and I didn't want to list the whole tags_table1 table
   twice... - kw */
void HTSwitchDTD(int new_flag)
{
    if (TRACE)
	CTRACE((tfp,
		"HTMLDTD: Copying %s DTD element info of size %d, %d * %d\n",
		new_flag ? "strict" : "tagsoup",
		(int) (new_flag ? sizeof(tags_table1) : sizeof(tags_table0)),
		HTML_ALL_ELEMENTS,
		(int) sizeof(HTTag)));
    if (new_flag)
	MemCpy(tags, tags_table1, HTML_ALL_ELEMENTS * sizeof(HTTag));
    else
	MemCpy(tags, tags_table0, HTML_ALL_ELEMENTS * sizeof(HTTag));
}