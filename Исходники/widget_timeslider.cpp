void
studio::render_time_point_to_window(
	const Glib::RefPtr<Gdk::Drawable>& window,
	const Gdk::Rectangle& area,
	const synfig::TimePoint &tp,
	bool selected
)
{
	Glib::RefPtr<Gdk::GC> gc(Gdk::GC::create(window));
	const Gdk::Color black("#2e3436");

	if(selected)
		gc->set_line_attributes(2,Gdk::LINE_SOLID,Gdk::CAP_BUTT,Gdk::JOIN_MITER);
	else
		gc->set_line_attributes(1,Gdk::LINE_SOLID,Gdk::CAP_BUTT,Gdk::JOIN_MITER);

	Gdk::Color color;
	std::vector<Gdk::Point> points;

/*-	BEFORE ------------------------------------- */

	color=get_interp_color(tp.get_before());
	color=color_darken(color,1.0f);
	if(selected)color=color_darken(color,1.3f);
	gc->set_rgb_fg_color(color);

	switch(tp.get_before())
	{
	case INTERPOLATION_TCB:
		window->draw_arc(
			gc,
			true,
			area.get_x(),
			area.get_y(),
			area.get_width(),
			area.get_height(),
			64*90,
			64*180
		);
		gc->set_rgb_fg_color(black);
		window->draw_arc(
			gc,
			false,
			area.get_x(),
			area.get_y(),
			area.get_width(),
			area.get_height(),
			64*90,
			64*180
		);
		break;

	case INTERPOLATION_HALT:
		window->draw_arc(
			gc,
			true,
			area.get_x(),
			area.get_y(),
			area.get_width(),
			area.get_height()*2,
			64*90,
			64*90
		);
		gc->set_rgb_fg_color(black);
		window->draw_arc(
			gc,
			false,
			area.get_x(),
			area.get_y(),
			area.get_width(),
			area.get_height()*2,
			64*90,
			64*90
		);

		points.clear();
		points.push_back(Gdk::Point(area.get_x(),area.get_y()+area.get_height()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()+area.get_height()));
		window->draw_lines(gc,points);

		break;

	case INTERPOLATION_LINEAR:
		points.clear();
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()));
		points.push_back(Gdk::Point(area.get_x(),area.get_y()+area.get_height()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()+area.get_height()));
		window->draw_polygon(gc,true,points);
		gc->set_rgb_fg_color(black);
		window->draw_lines(gc,points);
		break;

	case INTERPOLATION_CONSTANT:
		points.clear();
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/4,area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/4,area.get_y()+area.get_height()/2));
		points.push_back(Gdk::Point(area.get_x(),area.get_y()+area.get_height()/2));
		points.push_back(Gdk::Point(area.get_x(),area.get_y()+area.get_height()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()+area.get_height()));
		window->draw_polygon(gc,true,points);
		gc->set_rgb_fg_color(black);
		window->draw_lines(gc,points);
		break;

	case INTERPOLATION_CLAMPED:
		points.clear();
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()));
		points.push_back(Gdk::Point(area.get_x(),area.get_y()+area.get_height()/2));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()+area.get_height()));
		window->draw_polygon(gc,true,points);
		gc->set_rgb_fg_color(black);
		window->draw_lines(gc,points);
		break;

	case INTERPOLATION_UNDEFINED: default:
		points.clear();
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/3,area.get_y()));
		points.push_back(Gdk::Point(area.get_x(),area.get_y()+area.get_height()/3));
		points.push_back(Gdk::Point(area.get_x(),area.get_y()+area.get_height()-area.get_height()/3));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/3,area.get_y()+area.get_height()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()+area.get_height()));
		window->draw_polygon(gc,true,points);
		gc->set_rgb_fg_color(black);
		window->draw_lines(gc,points);
		break;
	}

/*-	AFTER -------------------------------------- */

	color=get_interp_color(tp.get_after());
	color=color_darken(color,0.8f);
	if(selected)color=color_darken(color,1.3f);
	gc->set_rgb_fg_color(color);

	switch(tp.get_after())
	{
	case INTERPOLATION_TCB:
		window->draw_arc(
			gc,
			true,
			area.get_x(),
			area.get_y(),
			area.get_width(),
			area.get_height(),
			64*270,
			64*180
		);
		gc->set_rgb_fg_color(black);
		window->draw_arc(
			gc,
			false,
			area.get_x(),
			area.get_y(),
			area.get_width(),
			area.get_height(),
			64*270,
			64*180
		);
		break;

	case INTERPOLATION_HALT:
		window->draw_arc(
			gc,
			true,
			area.get_x(),
			area.get_y()-area.get_height(),
			area.get_width(),
			area.get_height()*2,
			64*270,
			64*90
		);
		gc->set_rgb_fg_color(black);
		window->draw_arc(
			gc,
			false,
			area.get_x(),
			area.get_y()-area.get_height(),
			area.get_width(),
			area.get_height()*2,
			64*270,
			64*90
		);

		points.clear();
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width(),area.get_y()));
		window->draw_lines(gc,points);

		break;

	case INTERPOLATION_LINEAR:
		points.clear();
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width(),area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()+area.get_height()));
		window->draw_polygon(gc,true,points);
		gc->set_rgb_fg_color(black);
		window->draw_lines(gc,points);
		break;

	case INTERPOLATION_CONSTANT:
		points.clear();
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width(),area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width(),area.get_y()+area.get_height()/2));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()-area.get_width()/4,area.get_y()+area.get_height()/2));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()-area.get_width()/4,area.get_y()+area.get_height()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()+area.get_height()));
		window->draw_polygon(gc,true,points);
		gc->set_rgb_fg_color(black);
		window->draw_lines(gc,points);
		break;

	case INTERPOLATION_CLAMPED:
		points.clear();
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width(),area.get_y()+area.get_height()/2));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()+area.get_height()));
		window->draw_polygon(gc,true,points);
		gc->set_rgb_fg_color(black);
		window->draw_lines(gc,points);
		break;

	case INTERPOLATION_UNDEFINED: default:
		points.clear();
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()-area.get_width()/3,area.get_y()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width(),area.get_y()+area.get_height()/3));
		points.push_back(Gdk::Point(area.get_x()+area.get_width(),area.get_y()+area.get_height()-area.get_height()/3));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()-area.get_width()/3,area.get_y()+area.get_height()));
		points.push_back(Gdk::Point(area.get_x()+area.get_width()/2,area.get_y()+area.get_height()));
		window->draw_polygon(gc,true,points);
		gc->set_rgb_fg_color(black);
		window->draw_lines(gc,points);
		break;
	}

}