void Pen_Color_to_tmpfile(int pen, int red, int green, int blue)
{
	PEN_N tp;
	PEN_C r, g, b;

	tp = (PEN_N) pen;
	r = (PEN_C) red;
	g = (PEN_C) green;
	b = (PEN_C) blue;

	if (record_off)		/* Wrong page!  */
		return;

	if (fwrite(&tp, sizeof(tp), 1, td) != 1) {
		PError("Pen_Color_to_tmpfile - pen");
		Eprintf("Error @ Cmd %ld\n", vec_cntr_w);
		exit(ERROR);
	}
	if (fwrite(&r, sizeof(r), 1, td) != 1) {
		PError("Pen_Color_to_tmpfile - red component");
		Eprintf("Error @ Cmd %ld\n", vec_cntr_w);
		exit(ERROR);
	}
	if (fwrite(&g, sizeof(g), 1, td) != 1) {
		PError("Pen_Color_to_tmpfile - green component");
		Eprintf("Error @ Cmd %ld\n", vec_cntr_w);
		exit(ERROR);
	}
	if (fwrite(&b, sizeof(b), 1, td) != 1) {
		PError("Pen_Color_to_tmpfile - blue component");
		Eprintf("Error @ Cmd %ld\n", vec_cntr_w);
		exit(ERROR);
	}
}