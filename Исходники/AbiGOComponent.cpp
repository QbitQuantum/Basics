void GOComponentView::render(UT_Rect & rec)
{
	UT_return_if_fail (component);
	if (rec.width == 0 || rec.height == 0) // Nothing to render
		return;
	GR_CairoGraphics *pUGG = static_cast<GR_CairoGraphics*>(m_pGOMan->getGraphics());
	UT_sint32 myWidth = pUGG->tdu(rec.width);
	UT_sint32 myHeight = pUGG->tdu(rec.height);
	UT_sint32 x = pUGG->tdu(rec.left), y;
	if ((width != rec.width || ascent + descent != rec.height) && go_component_is_resizable (component))
	{
		double _ascent, _descent;
		go_component_set_size (component, (double) rec.width / UT_LAYOUT_RESOLUTION, (double) rec.height / UT_LAYOUT_RESOLUTION);
		g_object_get (G_OBJECT (component), "ascent", &_ascent, "descent", &_descent, NULL);
		ascent =  (UT_sint32) rint (_ascent * UT_LAYOUT_RESOLUTION);
		descent =  (UT_sint32) rint (_descent * UT_LAYOUT_RESOLUTION);
	}
	y = pUGG->tdu(rec.top - ascent);
	pUGG->beginPaint();
	cairo_t *cr = pUGG->getCairo ();
	cairo_save (cr);
	cairo_translate (cr, x, y);
	go_component_render (component, cr, myWidth, myHeight);
	cairo_new_path (cr); // just in case a path has not been ended
	cairo_restore (cr);
	pUGG->endPaint();
}