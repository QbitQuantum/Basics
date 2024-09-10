void area___::test__(){
	int width, height;
	width=da_->get_allocation().get_width();
	height=da_->get_allocation().get_height();

	double m_radius=0.42;
	double m_line_width=0.05;

	// scale to unit square and translate (0, 0) to be (0.5, 0.5), i.e.
	// the center of the window
	cr_->scale(width, height);
	cr_->translate(0.5, 0.5);
	cr_->set_line_width(m_line_width);

	cr_->save();
	cr_->set_source_rgba(0.337, 0.612, 0.117, 0.9);   // green
	cr_->paint();
	cr_->restore();
	cr_->arc(0, 0, m_radius, 0, 2 * M_PI);
	cr_->save();
	cr_->set_source_rgba(1.0, 1.0, 1.0, 0.8);
	cr_->fill_preserve();
	cr_->restore();
	cr_->stroke_preserve();
	cr_->clip();

	//clock ticks
	for (int i = 0; i < 12; i++)
	{
		double inset = 0.05;

		cr_->save();
		cr_->set_line_cap(Cairo::LINE_CAP_ROUND);

		if(i % 3 != 0)
		{
			inset *= 0.8;
			cr_->set_line_width(0.03);
		}

		cr_->move_to(
				(m_radius - inset) * cos (i * M_PI / 6),
				(m_radius - inset) * sin (i * M_PI / 6));
		cr_->line_to (
				m_radius * cos (i * M_PI / 6),
				m_radius * sin (i * M_PI / 6));
		cr_->stroke();
		cr_->restore(); // stack-pen-size
	}

	// store the current time
	time_t rawtime;
	time(&rawtime);
	struct tm * timeinfo = localtime (&rawtime);

	// compute the angles of the indicators of our clock
	double minutes = timeinfo->tm_min * M_PI / 30;
	double hours = timeinfo->tm_hour * M_PI / 6;
	double seconds= timeinfo->tm_sec * M_PI / 30;
	cout<<timeinfo->tm_min<<","<<timeinfo->tm_hour<<","<<timeinfo->tm_sec<<endl;

	cr_->save();
	cr_->set_line_cap(Cairo::LINE_CAP_ROUND);

	// draw the seconds hand
	cr_->save();
	cr_->set_line_width(m_line_width / 3);
	cr_->set_source_rgba(0.7, 0.7, 0.7, 0.8); // gray
	cr_->move_to(0, 0);
	cr_->line_to(sin(seconds) * (m_radius * 0.9),
			-cos(seconds) * (m_radius * 0.9));
	cr_->stroke();
	cr_->restore();

	// draw the minutes hand
	cr_->set_source_rgba(0.117, 0.337, 0.612, 0.9);   // blue
	cr_->move_to(0, 0);
	cr_->line_to(sin(minutes + seconds / 60) * (m_radius * 0.8),
			-cos(minutes + seconds / 60) * (m_radius * 0.8));
	cr_->stroke();

	// draw the hours hand
	cr_->set_source_rgba(0.337, 0.612, 0.117, 0.9);   // green
	cr_->move_to(0, 0);
	cr_->line_to(sin(hours + minutes / 12.0) * (m_radius * 0.5),
			-cos(hours + minutes / 12.0) * (m_radius * 0.5));
	cr_->stroke();
	cr_->restore();

	// draw a little dot in the middle
	cr_->arc(0, 0, m_line_width / 3.0, 0, 2 * M_PI);
	cr_->fill();
}