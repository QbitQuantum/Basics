int PaintFileName(Draw& w, const Rect& r, String h, Color ink)
{
	if(*h == '\xff')
		h.Remove(0, 1);
	return DrawFileName0(w, r, h, ink, 0);
}