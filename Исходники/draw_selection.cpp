void SelectionScanlineSweeper::DrawImpl_rgb(agg::rect_d rect, RenderingData *data, unsigned int width, unsigned int height, int stride,
																				agg::trans_affine const &mtx, agg::trans_affine const &viewport_mtx) {
	//ScanlineSource source(data);

	typedef agg::pixfmt_alpha_blend_rgb<agg::blender_rgb<agg::rgba8,  agg::order_rgb>, agg::scanline_accessor> pixfmt_type;
	typedef pixfmt_type::color_type                        color_type;
	typedef color_type::value_type                         value_type;
	typedef agg::renderer_base<pixfmt_type>                renderer_base;
	typedef agg::renderer_scanline_aa_solid<renderer_base> renderer_solid;

	agg::rasterizer_scanline_aa<> l_rasterizer;
	agg::scanline_u8              l_scanline;

	//pixfmt_type       pixfmt(agg::scanline_accessor(&source, ScanlineSource::get_scanline, width, height, stride));
	pixfmt_type       pixfmt((agg::scanline_accessor(data)));
	renderer_base     rb(pixfmt);

	l_rasterizer.clip_box(0.0, 0.0, width, height);
	l_rasterizer.filling_rule(agg::fill_non_zero);
	
	if (flip_y) {
		mtx.transform(&rect.x1, &rect.y1);
		mtx.transform(&rect.x2, &rect.y2);
	}
	
	double vertexes[] = {
		rect.x1, rect.y2,
		rect.x1, rect.y1,
		rect.x2, rect.y1,
		rect.x2, rect.y2
	};
	
	agg::test_vertex_source vertex_source(vertexes, 4);
	agg::conv_transform<agg::test_vertex_source> vertex_source_converted(vertex_source, viewport_mtx);
	l_rasterizer.add_path(vertex_source_converted);
	
	renderer_solid r(rb);
	{
		r.color(color);
		agg::render_scanlines(l_rasterizer, l_scanline, r);
	}
}