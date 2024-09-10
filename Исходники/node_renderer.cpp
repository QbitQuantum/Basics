void NodeRenderer::casing(const Cairo::RefPtr<Cairo::Context>& cr)
{
	// nothing to render
	if (s->casing_width <= 0.0)
		return;

	cr->save();

	cr->arc(location.x, location.y, s->width/2.0 + s->casing_width, 0, 2*boost::math::constants::pi<double>());

	cr->set_source_color(s->casing_color);

	cr->fill();
	cr->restore();
}