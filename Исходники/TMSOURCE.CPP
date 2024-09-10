/**
Return the end of the paragraph - after the paragraph separator if any.
*/
EXPORT_C TInt MTmSource::ParagraphEnd(TInt aPos) const
	{
	TInt doc_end = DocumentLength();
	TPtrC text;
	TTmCharFormat format;
	while (aPos < doc_end)
		{
		GetText(aPos,text,format);
		const TText *p = text.Ptr();
		const TText *q = p + text.Length();
		while (p < q)
			if (*p == CEditableText::EParagraphDelimiter)
				return aPos + 1;
			else
				{
				p++;
				aPos++;
				}
		}
	return doc_end + 1;
	}