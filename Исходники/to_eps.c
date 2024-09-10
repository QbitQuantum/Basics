int
to_eps (const GEN_PAR *pg, const OUT_PAR *po)
{
    PlotCmd	cmd;
    HPGL_Pt	pt1 = {0,0};
    FILE		*md;
    int		pen_no=0, pencolor=0, err;
    PEN_W		pensize;

    err = 0;
    if (!pg->quiet)
        Eprintf ("\n\n- Writing EPS code to \"%s\"\n",
                 *po->outfile == '-' ? "stdout" : po->outfile);

    /* Init. of PostScript file: */
    if (*po->outfile != '-')
    {
        if ((md = fopen(po->outfile, "w")) == NULL)
        {
            PError("hp2xx (eps)");
            return ERROR;
        }
    }
    else
        md = stdout;

    /* PS header */

    pensize = pt.width[DEFAULT_PEN_NO]; /* Default pen	*/
    ps_init (pg, po, md, pensize);

    if (pensize > 0.05)
        fprintf(md," %6.3f W\n", pensize);

    /* Factor for transformation of HP coordinates to mm	*/

    xcoord2mm = po->width  / (po->xmax - po->xmin);
    ycoord2mm = po->height / (po->ymax - po->ymin);
    xmin	    = po->xmin;
    ymin	    = po->ymin;

    /**
     ** Command loop: While temporary file not empty: process command.
     **/

    while ((cmd = PlotCmd_from_tmpfile()) != CMD_EOF)
    {
        switch (cmd)
        {
        case NOP:
            break;
        case SET_PEN:
            if ((pen_no = fgetc(pg->td)) == EOF)
            {
                PError("Unexpected end of temp. file: ");
                err = ERROR;
                goto EPS_exit;
            }
            pensize = pt.width[pen_no];
            pencolor = pt.color[pen_no];
            break;
        case DEF_PW:
            if(!load_pen_width_table(pg->td)) {
                PError("Unexpected end of temp. file");
                err = ERROR;
                goto EPS_exit;
            }
            pensize=pt.width[pen_no];
            break;
        case DEF_PC:
            err=load_pen_color_table(pg->td);
            if (err<0) {
                PError("Unexpected end of temp. file");
                err = ERROR;
                goto EPS_exit;
            }
            if (err==pencolor) pencolor *=-1; /*current pen changed*/
            break;
        case DEF_LA:
            if(load_line_attr(pg->td) <0) {
                PError("Unexpected end of temp. file");
                err = ERROR;
                goto EPS_exit;
            }
            break;
        case MOVE_TO:
            ps_set_linewidth(pensize, &pt1, md);
            ps_set_linecap(CurrentLineAttr.End, pensize, &pt1, md);

            if(pencolor <0) {
                pencolor=pt.color[pen_no];
                ps_set_color (  pt.clut[pencolor][0]/255.0,
                                pt.clut[pencolor][1]/255.0,
                                pt.clut[pencolor][2]/255.0,
                                &pt1, md);
            }

            HPGL_Pt_from_tmpfile (&pt1);
            if (pensize > 0.05)
                ps_stroke_and_move_to (&pt1, md);
            break;
        case DRAW_TO:
            ps_set_linewidth(pensize, &pt1, md);
            ps_set_linecap(CurrentLineAttr.End, pensize, &pt1, md);

            if(pencolor <0) {
                pencolor=pt.color[pen_no];
                ps_set_color (  pt.clut[pencolor][0]/255.0,
                                pt.clut[pencolor][1]/255.0,
                                pt.clut[pencolor][2]/255.0,
                                &pt1, md);
            }

            HPGL_Pt_from_tmpfile (&pt1);
            if (pensize > 0.05)
                ps_line_to (&pt1, 'D', md);
            break;
        case PLOT_AT:
            ps_set_linewidth(pensize, &pt1, md);
            ps_set_linecap(CurrentLineAttr.End, pensize, &pt1, md);

            if(pencolor<0) {
                pencolor=pt.color[pen_no];
                ps_set_color (  pt.clut[pencolor][0]/255.0,
                                pt.clut[pencolor][1]/255.0,
                                pt.clut[pencolor][2]/255.0,
                                &pt1, md);
            }

            HPGL_Pt_from_tmpfile (&pt1);
            if (pensize > 0.05) {
                ps_line_to (&pt1, 'M', md);
                ps_line_to (&pt1, 'D', md); /* not sure whether this is needed */
                ps_draw_dot(&pt1,pensize/2,md);
            }
            break;
        default:
            Eprintf ("Illegal cmd in temp. file!");
            err = ERROR;
            goto EPS_exit;
        }
    }

    /* Finish up */

    ps_end (md);

EPS_exit:
    if (md != stdout)
        fclose (md);

    if (!pg->quiet)
        Eprintf ("\n");
    return err;
}