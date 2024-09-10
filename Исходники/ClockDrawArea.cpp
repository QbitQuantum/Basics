bool ClockDrawArea::on_draw(const Cairo::RefPtr<Cairo::Context>& context){
	//Get the drawing area
	auto allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();

	//Set the scale to a unit square
	context->scale(width, height);

	//Set (0.5, 0.5) to (0, 0). convenient to draw with arc.
	context->translate(0.5, 0.5);

	//Paint the background of the window;
	context->save();
	context->set_source_rgba(0.337, 0.612, 0.117, 0.9);
	context->paint();
	context->restore();

	//Draw the outer edge of the clock
	context->set_line_width(3 * m_LineWidth);
	context->arc(0, 0, m_Radius, 0, 2 * M_PI);

	//Paint the background color of the clock
	context->save();
	context->set_source_rgba(1.0, 1.0, 1.0, 0.8);
	context->fill_preserve();
	context->restore();

	//Draw a center point for good looking
	context->stroke();
	context->arc(0, 0, 0.05 * m_Radius, 0, 2 * M_PI);
	context->stroke();

	//Draw ticks
	context->save();
	double l = 1;

	for(int i = 0; i <= 11; i++){

		if((i % 3) == 0) {
			l = m_Radius * 0.8;
		}else{
			l = m_Radius * 0.9;
		}

		context->move_to(l * cos(i * 2* M_PI /12), l * sin(i * 2 * M_PI /12));
		context->line_to(m_Radius * cos(i * 2 * M_PI /12), m_Radius * sin(i * 2 * M_PI /12));

	}
	context->stroke();
	context->restore();

	//Get the current time from system and save info to a timeinfo struct
	time_t rawTime;
	time(&rawTime);

	struct tm * timeinfo = localtime(&rawTime);

	//Calculate the angle of hands of the clock
	auto radSeconds = (timeinfo->tm_sec * 2 * M_PI /60) - M_PI/2;
	auto radMinutes = (timeinfo->tm_min * 2 * M_PI /60) - M_PI/2;
	auto radHours = (timeinfo->tm_hour * 2 * M_PI /12) - M_PI/2  + timeinfo->tm_min * 2 * M_PI /(60 * 12);

	//Draw the hands of the clock
	context->save();

	//The hand of seconds
	context->set_source_rgba(0.823, 0.322, 0.155, 0.9);
	context->set_line_width(m_LineWidth);
	l = 0.9 * m_Radius;
	context->move_to(0,0);
	context->line_to(l * cos(radSeconds), l * sin(radSeconds));
	context->stroke();

	//The hand of minutes
	context->set_source_rgba(0.632, 0.802, 0.266, 0.9);
	context->set_line_width(2 * m_LineWidth);
	l = 0.8 * m_Radius;
	context->move_to(0,0);
	context->line_to(l * cos(radMinutes), l * sin(radMinutes));
	context->stroke();

	//The hand of hours
	context->set_source_rgba(0.104, 0.582, 0.723, 0.9);
	context->set_line_width(3 * m_LineWidth);
	l = 0.65 * m_Radius;
	context->move_to(0,0);
	context->line_to(l * cos(radHours), l * sin(radHours));
	context->stroke();

	context->restore();


	return true;
}