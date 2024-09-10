int InsetERT::docbook(odocstream & os, OutputParams const &) const
{
	// FIXME can we do the same thing here as for LaTeX?
	ParagraphList::const_iterator par = paragraphs().begin();
	ParagraphList::const_iterator end = paragraphs().end();

	int lines = 0;
	while (par != end) {
		pos_type siz = par->size();
		for (pos_type i = 0; i < siz; ++i)
			os.put(par->getChar(i));
		++par;
		if (par != end) {
			os << "\n";
			++lines;
		}
	}

	return lines;
}