static gboolean gtk_tuner_expose (GtkWidget *widget, GdkEventExpose *event)
{
	static const char* note[12] = {"F#","G ","G#","A ","A#","B ","C ","C#","D ","D#","E ","F "};
	static const char* octave[] = {"0","1","2","3","4","5"," "};
	GxTuner *tuner = GX_TUNER(widget);
	cairo_t *cr;

	double x0      = (widget->allocation.width - 100 * tuner->scale) * 0.5;
	double y0      = (widget->allocation.height - 90 * tuner->scale) * 0.5;

	cr = gdk_cairo_create(widget->window);
	cairo_set_source_surface(cr, tuner->surface_tuner, x0, y0);
	cairo_scale(cr, tuner->scale, tuner->scale);
	cairo_paint (cr);

	float scale = -0.5;
	if (tuner->freq) {
		float fvis = 12 * (log2f(tuner->freq/tuner->reference_pitch) + 4) + 3;
		float fvisr = round(fvis);
		int vis = fvisr;
		int indicate_oc = round(fvisr/12);
		const int octsz = sizeof(octave) / sizeof(octave[0]);
		if (indicate_oc < 0 || indicate_oc >= octsz) {
			// just safety, should not happen with current parameters
			// (pitch tracker output 23 .. 999 Hz)
			indicate_oc = octsz - 1;
		}
		scale = (fvis-vis) / 2;
		vis = vis % 12;
		if (vis < 0) {
			vis += 12;
		}

		// display note
		float pitch_add = fabsf(tuner->reference_pitch - 440.00);
		cairo_set_source_rgba(cr, fabsf(scale)*2+(pitch_add*0.1), 1-(scale*scale*4+(pitch_add*0.1)), 0.2,1-(fabsf(scale)*2));
		cairo_set_font_size(cr, 18.0);
		cairo_move_to(cr,x0+50 -9 , y0+30 +9 );
		cairo_show_text(cr, note[vis]);
        cairo_set_font_size(cr, 8.0);
        cairo_move_to(cr,x0+54  , y0+30 +16 );
        cairo_show_text(cr, octave[indicate_oc]);
	}

	// display frequency
	char s[10];
	snprintf(s, sizeof(s), "%.0f Hz", tuner->freq);
	cairo_set_source_rgba (cr, 0.8, 0.8, 0.2,0.6);
	cairo_set_font_size (cr, 8.0);
	cairo_text_extents_t ex;
	cairo_text_extents(cr, s, &ex);
	cairo_move_to (cr, x0+90-ex.width, y0+58);
	cairo_show_text(cr, s);

	// indicator (line)
	cairo_move_to(cr,x0+50, y0+rect_height-5);
	cairo_set_dash (cr, dash_ind, sizeof(dash_ind)/sizeof(dash_ind[0]), 0);
	cairo_line_to(cr, (scale*2*rect_width)+x0+50, y0+(scale*scale*30)+2);
	cairo_set_source_rgb(cr,  0.5, 0.1, 0.1);
	cairo_stroke(cr);

	cairo_destroy(cr);

	return FALSE;
}