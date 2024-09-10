void
studio::render_gradient_to_window(const Glib::RefPtr<Gdk::Drawable>& window,const Gdk::Rectangle& ca,const synfig::Gradient &gradient)
{
	int	height = ca.get_height();
	int	width = ca.get_width()-4;

	float sample_width(1.0f/(float)width);
	Glib::RefPtr<Gdk::GC> gc(Gdk::GC::create(window));
	const Color bg1(0.25, 0.25, 0.25);
	const Color bg2(0.5, 0.5, 0.5);
	Gdk::Color gdk_c;
	int i;
	for(i=0;i<width;i++)
	{
		const Color c(gradient(float(i)/float(width),sample_width));
		const Color c1(Color::blend(c,bg1,1.0).clamped());
		const Color c2(Color::blend(c,bg2,1.0).clamped());
		gushort r1(256*App::gamma.r_F32_to_U8(c1.get_r()));
		gushort g1(256*App::gamma.g_F32_to_U8(c1.get_g()));
		gushort b1(256*App::gamma.b_F32_to_U8(c1.get_b()));
		gushort r2(256*App::gamma.r_F32_to_U8(c2.get_r()));
		gushort g2(256*App::gamma.g_F32_to_U8(c2.get_g()));
		gushort b2(256*App::gamma.b_F32_to_U8(c2.get_b()));

		if((i*2/height)&1)
		{
			gdk_c.set_rgb(r1,g1,b1);
			gc->set_rgb_fg_color(gdk_c);
			window->draw_rectangle(gc, true, ca.get_x()+i+2, ca.get_y(), 1, height/2);

			gdk_c.set_rgb(r2,g2,b2);
			gc->set_rgb_fg_color(gdk_c);
			window->draw_rectangle(gc, true, ca.get_x()+i+2, ca.get_y()+height/2, 1, height/2);
		}
		else
		{
			gdk_c.set_rgb(r2,g2,b2);
			gc->set_rgb_fg_color(gdk_c);
			window->draw_rectangle(gc, true, ca.get_x()+i+2, ca.get_y(), 1, height/2);

			gdk_c.set_rgb(r1,g1,b1);
			gc->set_rgb_fg_color(gdk_c);
			window->draw_rectangle(gc, true, ca.get_x()+i+2, ca.get_y()+height/2, 1, height/2);
		}
	}
	gc->set_rgb_fg_color(Gdk::Color("#ffffff"));
	window->draw_rectangle(gc, false, ca.get_x()+1, ca.get_y()+1, ca.get_width()-3, height-3);
	gc->set_rgb_fg_color(Gdk::Color("#000000"));
	window->draw_rectangle(gc, false, ca.get_x(), ca.get_y(), ca.get_width()-1, height-1);
}