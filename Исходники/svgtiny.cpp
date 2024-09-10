struct svgtiny_shape *svgtiny_add_shape(struct svgtiny_parse_state *state)
{
	struct svgtiny_shape *shape = (svgtiny_shape *) realloc(state->diagram->shape,
			(state->diagram->shape_count + 1) * sizeof (state->diagram->shape[0]));
	if (!shape)
		return 0;
	state->diagram->shape = shape;

	shape += state->diagram->shape_count;
	shape->path = 0;
	shape->path_length = 0;
	shape->text = 0;
	shape->fill = state->fill;
	shape->stroke = state->stroke;
	shape->stroke_width = lroundf((float) state->stroke_width *
			(state->ctm.a + state->ctm.d) / 2.0);
	if (0 < state->stroke_width && shape->stroke_width == 0)
		shape->stroke_width = 1;

	return shape;
}