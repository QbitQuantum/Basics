static void plot_data_fft(SFSUI* ui) {
	cairo_t* cr;
	cr = cairo_create (ui->sf_dat);

	rounded_rectangle (cr, SS_BORDER, SS_BORDER, SS_SIZE, SS_SIZE, SS_BORDER);
	cairo_clip_preserve (cr);

	const float persistence = robtk_dial_get_value(ui->screen);
	float transp;
	cairo_set_operator (cr, CAIRO_OPERATOR_OVER);
	if (persistence > 0) {
		cairo_set_source_rgba(cr, 0, 0, 0, .25 - .0025 * persistence);
		transp = 0.05;
	} else {
		cairo_set_source_rgba(cr, 0, 0, 0, 1.0);
		transp = .5;
	}
	cairo_fill(cr);

	cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
	cairo_set_line_width (cr, 1.0);

	const float xmid = rintf(SS_BORDER + SS_SIZE *.5) + .5;
	const float dnum = SS_SIZE / ui->log_base;
	const float denom = ui->log_rate / (float)ui->fft_bins;

	cairo_set_operator (cr, CAIRO_OPERATOR_OVER);
	for (uint32_t i = 1; i < ui->fft_bins-1 ; ++i) {
		if (ui->level[i] < 0) continue;

		const float level = MAKEUP_GAIN + fftx_power_to_dB(ui->level[i]);
		if (level < -80) continue;

		const float y  = rintf(SS_BORDER + SS_SIZE - dnum * fast_log10(1.0 + i * denom)) + .5;
		const float y1 = rintf(SS_BORDER + SS_SIZE - dnum * fast_log10(1.0 + (i+1) * denom)) + .5;
		const float pk = level > 0.0 ? 1.0 : (80 + level) / 80.0;
		const float a_lr = ui->lr[i];

		float clr[3];
		hsl2rgb(clr, .70 - .72 * pk, .9, .3 + pk * .4);
		cairo_set_source_rgba(cr, clr[0], clr[1], clr[2], transp  + pk * .2);
		cairo_set_line_width (cr, MAX(1.0, (y - y1)));

		cairo_move_to(cr, xmid, y);
		cairo_line_to(cr, SS_BORDER + SS_SIZE * a_lr, y);
		cairo_stroke(cr);

	}
	cairo_destroy (cr);
}