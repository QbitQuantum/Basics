void
prnt_Status(void)
{
    static char scratchbuf[TEMPLATE_COLS+1];
    pad_Strcpy(TITLE_PTR, title, TITLE_LEN - 1);
    pad_Strcpy(TIMER_PTR, timer, TIMER_LEN - 1);
    pad_Strcpy(F_SCRIPT_PTR, script_file, 32);
    sprintf(scratchbuf, "%11.4f", view_size);
    bu_strlcpy(VU_SIZE_PTR, scratchbuf, strlen(scratchbuf));
    pad_Strcpy(F_ERRORS_PTR, err_file, 32);
    sprintf(scratchbuf, "%11.4f", grid_dist);
    bu_strlcpy(GRID_DIS_PTR, scratchbuf, strlen(scratchbuf));
    pad_Strcpy(F_MAT_DB_PTR, mat_db_file, 32);
    sprintf(scratchbuf, "%11.4f", x_grid_offset);
    bu_strlcpy(GRID_XOF_PTR, scratchbuf, strlen(scratchbuf));
    pad_Strcpy(F_LGT_DB_PTR, lgt_db_file, 32);
    sprintf(scratchbuf, "%11.4f", y_grid_offset);
    bu_strlcpy(GRID_YOF_PTR, scratchbuf, strlen(scratchbuf));
    pad_Strcpy(F_RASTER_PTR, fb_file, 32);
    sprintf(scratchbuf, "%11.4f", modl_radius);
    bu_strlcpy(MODEL_RA_PTR, scratchbuf, strlen(scratchbuf));
    sprintf(scratchbuf, "%3d %3d %3d",
	    background[0], background[1], background[2]);
    bu_strlcpy(BACKGROU_PTR, scratchbuf, strlen(scratchbuf));
    snprintf(scratchbuf, TEMPLATE_COLS+1,
	     "%4s",	pix_buffered == B_PAGE ? "PAGE" :
	     pix_buffered == B_PIO ? "PIO" :
	     pix_buffered == B_LINE ? "LINE" : "?"
	);
    bu_strlcpy(BUFFERED_PTR, scratchbuf, strlen(scratchbuf));
    sprintf(scratchbuf, "0x%06x", RT_G_DEBUG);
    bu_strlcpy(DEBUGGER_PTR, scratchbuf, strlen(scratchbuf));
    sprintf(scratchbuf, "%-2d", max_bounce);
    bu_strlcpy(MAX_BOUN_PTR, scratchbuf, strlen(scratchbuf));
    snprintf(scratchbuf, TEMPLATE_COLS+1, " LGT");
    bu_strlcpy(PROGRAM_NM_PTR, scratchbuf, strlen(scratchbuf));
    snprintf(scratchbuf, TEMPLATE_COLS+1, " %s ",
	     ged_file == NULL ? "(null)" : ged_file);
    bu_strlcpy(F_GED_DB_PTR, scratchbuf, FMIN(strlen(scratchbuf), 26));
    sprintf(scratchbuf, " [%04d-", grid_x_org);
    bu_strlcpy(GRID_PIX_PTR, scratchbuf, strlen(scratchbuf));
    sprintf(scratchbuf, "%04d, ", grid_x_fin);
    bu_strlcpy(GRID_SIZ_PTR, scratchbuf, strlen(scratchbuf));
    sprintf(scratchbuf, "%04d-", grid_y_org);
    bu_strlcpy(GRID_SCN_PTR, scratchbuf, strlen(scratchbuf));
    sprintf(scratchbuf, "%04d:", grid_y_fin);
    bu_strlcpy(GRID_FIN_PTR, scratchbuf, strlen(scratchbuf));
    sprintf(scratchbuf, "%04d] ", frame_no);
    bu_strlcpy(FRAME_NO_PTR, scratchbuf, strlen(scratchbuf));
    update_Screen();
    return;
}