wxString CSourceDataGenerator::GetFontDefinition(const EMGL_font_t *font, const wxString &name)
{
	wxString result;
	result += wxString::Format("const EMGL_font_t font_%s = {%d, %u, %u, codePageTable};\n",
		name.ToAscii(), font->ascender, font->bpp, font->numCodepages);
	return result;
}