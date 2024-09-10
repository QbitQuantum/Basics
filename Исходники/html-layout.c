static void layout_flow(fz_context *ctx, fz_html *box, fz_html *top, float em, float page_h)
{
	fz_html_flow *node, *line_start, *word_start, *word_end, *line_end;
	float glue_w;
	float word_w;
	float line_w;
	float indent;
	float avail, line_h;
	float baseline;
	int align;

	em = fz_from_css_number(box->style.font_size, em, em);
	indent = box->is_first_flow ? fz_from_css_number(top->style.text_indent, em, top->w) : 0;
	align = top->style.text_align;

	box->x = top->x;
	box->y = top->y + top->h;
	box->w = top->w;
	box->h = 0;

	if (!box->flow_head)
		return;

	for (node = box->flow_head; node; node = node->next)
		if (node->type == FLOW_IMAGE)
			measure_image(ctx, node, top->w, page_h);
		else
			measure_word(ctx, node, em);

	line_start = find_next_word(box->flow_head, &glue_w);
	line_end = NULL;

	line_w = indent;
	word_w = 0;
	word_start = line_start;
	while (word_start)
	{
		word_end = find_next_glue(word_start, &word_w);
		if (line_w + word_w <= top->w)
		{
			line_w += word_w;
			glue_w = 0;
			line_end = word_end;
			word_start = find_next_word(word_end, &glue_w);
			word_w = glue_w;
		}
		else
		{
			avail = page_h - fmodf(box->y + box->h, page_h);
			line_h = measure_line(line_start, line_end, &baseline);
			if (line_h > avail)
				box->h += avail;
			layout_line(ctx, indent, top->w, line_w, align, line_start, line_end, box, baseline);
			box->h += line_h;
			word_start = find_next_word(line_end, &glue_w);
			line_start = word_start;
			line_end = NULL;
			indent = 0;
			line_w = 0;
			word_w = 0;
		}
	}

	/* don't justify the last line of a paragraph */
	if (align == TA_JUSTIFY)
		align = TA_LEFT;

	if (line_start)
	{
		avail = page_h - fmodf(box->y + box->h, page_h);
		line_h = measure_line(line_start, line_end, &baseline);
		if (line_h > avail)
			box->h += avail;
		layout_line(ctx, indent, top->w, line_w, align, line_start, line_end, box, baseline);
		box->h += line_h;
	}
}