//*******************************************************************
// command loop over tmp_file
static int plotit(HANDLE outDC, const GEN_PAR * pg, const OUT_PAR * po)
{
	PlotCmd cmd;
	HPGL_Pt pt1 = { 0 };
	int pen_no = 0, pencolor = 0, err = 0;
	PEN_W pensize;
	pensize = pt.width[DEFAULT_PEN_NO];	/* Default pen      */
	pencolor = pt.color[DEFAULT_PEN_NO];
	emf_new_pen(0, pt.clut[pencolor][0],	// no draw pen
		    pt.clut[pencolor][1], pt.clut[pencolor][2], &pt1,
		    outDC);

	emf_init(po, outDC);	// invisible boundingbox
	emf_new_pen(pensize, pt.clut[pencolor][0], pt.clut[pencolor][1],
		    pt.clut[pencolor][2], &pt1, outDC);

	/**
	** Command loop: While temporary file not empty: process command.
	**/

	while ((cmd = PlotCmd_from_tmpfile()) != CMD_EOF) {
		switch (cmd) {
		case NOP:
			break;
		case SET_PEN:
			if ((pen_no = fgetc(pg->td)) == EOF) {
				PError("Unexpected end of temp. file: ");
				err = ERROR;
				goto emf_exit;
			}
			pensize = pt.width[pen_no];
			pencolor = pt.color[pen_no];
			emf_new_pen(pensize, pt.clut[pencolor][0],
				    pt.clut[pencolor][1],
				    pt.clut[pencolor][2], &pt1, outDC);
			break;
		case DEF_PW:	// DEFine penwidth
			if (!load_pen_width_table(pg->td)) {
				PError("Unexpected end of temp. file");
				err = ERROR;
				goto emf_exit;
			}
			break;
		case DEF_PC:	//DEFpen color
			err = load_pen_color_table(pg->td);
			if (err < 0) {
				PError("Unexpected end of temp. file");
				err = ERROR;
				goto emf_exit;
			}
			if (err == pencolor)
				pencolor *= -1;	/*current pen changed */
			break;
		case DEF_LA:
			if (load_line_attr(pg->td) < 0) {
				PError("Unexpected end of temp. file");
				err = ERROR;
				goto emf_exit;
			}
			break;
		case MOVE_TO:	// Moveto

			HPGL_Pt_from_tmpfile(&pt1);
			if (pensize != 0)
				emf_move_to(&pt1, outDC);
			break;
		case DRAW_TO:	// Draw line
			HPGL_Pt_from_tmpfile(&pt1);
			if (pensize != 0)
				emf_line_to(&pt1, 'D', outDC);
			break;
		case PLOT_AT:
			HPGL_Pt_from_tmpfile(&pt1);
			if (pensize != 0) {
				emf_line_to(&pt1, 'M', outDC);
				emf_line_to(&pt1, 'D', outDC);
			}
			break;
		default:
			Eprintf("Illegal cmd in temp. file!");
			err = ERROR;
			goto emf_exit;
		}
	}
	/* Finish up */
      emf_exit:
	{
		HANDLE old =
		    SelectObject(outDC, GetStockObject(BLACK_PEN));
		DeleteObject(old);
	}
	return err;
}