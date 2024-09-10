void
studio::render_color_to_window(const Cairo::RefPtr<Cairo::Context> &cr, const Gdk::Rectangle &ca, const synfig::Color &color)
{
	const int height(ca.get_height());
	const int width(ca.get_width());

	const int square_size(height/2);

	if(color.get_alpha()!=1.0)
	{
		// In this case we need to render the alpha squares

		const Color bg1(
			colorconv_apply_gamma(
				Color::blend(color,Color(0.75, 0.75, 0.75),1.0).clamped() ));
		const Color bg2(
			colorconv_apply_gamma(
				Color::blend(color,Color(0.5, 0.5, 0.5),1.0).clamped() ));

		bool toggle(false);
		for(int i=0;i<width;i+=square_size)
		{
			const int square_width(min(square_size,width-i));

			if(toggle)
			{
		        cr->set_source_rgb(bg1.get_r(), bg1.get_g(), bg1.get_b());
		        cr->rectangle(ca.get_x()+i, ca.get_y(), square_width, square_size);
		        cr->fill();

		        cr->set_source_rgb(bg2.get_r(), bg2.get_g(), bg2.get_b());
		        cr->rectangle(ca.get_x()+i, ca.get_y()+square_size, square_width, square_size);
		        cr->fill();
				toggle=false;
			}
			else
			{
		        cr->set_source_rgb(bg2.get_r(), bg2.get_g(), bg2.get_b());
		        cr->rectangle(ca.get_x()+i, ca.get_y(), square_width, square_size);
		        cr->fill();

		        cr->set_source_rgb(bg1.get_r(), bg1.get_g(), bg1.get_b());
		        cr->rectangle(ca.get_x()+i, ca.get_y()+square_size, square_width, square_size);
		        cr->fill();
				toggle=true;
			}
		}
	}
	else
	{
		synfig::Color c = colorconv_apply_gamma(color);
        cr->set_source_rgb(c.get_r(), c.get_g(), c.get_b());
        cr->rectangle(ca.get_x(), ca.get_y(), width-1, height-1);
        cr->fill();
	}

	cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->rectangle(ca.get_x()+1, ca.get_y()+1, width-3, height-3);
    cr->stroke();

    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->rectangle(ca.get_x(), ca.get_y(), width-1, height-1);
    cr->stroke();
}