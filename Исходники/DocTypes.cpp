bool Paragraph::Format(ParaTypo& pfmt, int cx, int zoom) const {
	int len = length + !!style.indent;
	Buffer<char> chr(len);
	Buffer<int>  width(len);
	Buffer<ParaTypo::Part *> info(len);
	Buffer<ParaTypo::Part>   pinfo(part.GetCount() + !!style.indent);
	const Part *pptr = part.Begin();
	const Part *plim = part.End();
	ParaTypo::Part *pp = pinfo;
	char *cp = chr;
	int  *wp = width;
	ParaTypo::Part **ip = info;
	if(!IsNull(parafont)) {
		Font pf = parafont;
//		pf.Height(max(1, DocZoom(zoom, parafont.GetHeight())));
		int n = DocZoom(zoom, parafont.GetHeight());
		pf.Height(n ? n : 1);
		FontInfo f = pf.Info();
		pfmt.SetMin(f.GetAscent(), f.GetDescent(), f.GetExternal());
	}
/*	if(!IsNull(parafont)) {
		FontInfo f = w.GetFontInfo(parafont);
		pfmt.SetMin(DocZoom(zoom, f.GetAscent()),
			        DocZoom(zoom, f.GetDescent()),
					DocZoom(zoom, f.GetExternal()));
	}
*/	if(style.indent) {
		static Part dummy;
		*cp++ = ' ';
		*wp++ = DocZoom(zoom, style.indent);
		pp->Set(Arial(0), Black);
		pp->voidptr = &dummy;
		*ip++ = pp;
		pp++;
	}
	while(pptr != plim) {
		if(pptr->pr) {
			*cp++ = '@';
			Size sz = pptr->pr.GetStdSize();
			*wp++ = pp->width = pptr->pr && !pptr->sz.cx ? sz.cx : DocZoom(zoom, pptr->sz.cx);
			*ip++ = pp;
			pp->ascent = minmax(pptr->pr && !pptr->sz.cy ? sz.cy : DocZoom(zoom, pptr->sz.cy), 0, 1000);
			pp->descent = 0;
			pp->external = pp->overhang = 0;
			pp->color = pptr->color;
		}
		else {
			Font font = pptr->font;
			font.Height(DocZoom(zoom, pptr->font.GetHeight()));
			FontInfo pf = pp->Set(font, pptr->color);
			const char *s = pptr->text;
			int n = pptr->text.GetLength();
			while(n--) {
				*cp++ = *s;
				*wp++ = pf[*s == 31 ? 32 : ToUnicode((byte) *s, CHARSET_DEFAULT)];
				*ip++ = pp;
				s++;
			}
		}
		pp->voidptr = (void *)pptr;
		pp++;
		pptr++;
	}
	return pfmt.Format(style.align, len, chr, width, info, cx);
}