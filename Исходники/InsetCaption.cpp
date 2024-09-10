docstring InsetCaption::xhtml(XHTMLStream & xs, OutputParams const & rp) const
{
	if (rp.html_disable_captions)
		return docstring();
	InsetLayout const & il = getLayout();
	string const tag = il.htmltag();
	string attr = il.htmlattr();
	if (!type_.empty()) {
		string const our_class = "float-caption-" + type_;
		size_t const loc = attr.find("class='");
		if (loc != string::npos)
			attr.insert(loc + 1, our_class);
	}
	xs << html::StartTag(tag, attr);
	docstring def = getCaptionAsHTML(xs, rp);
	xs << html::EndTag(tag);
	return def;
}