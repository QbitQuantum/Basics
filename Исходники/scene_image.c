static void scene_show_info(int selidx)
{
	char infostr[64];
	int ilen;

	if (config.fit == conf_fit_custom)
		SPRINTF_S(infostr, _("%dx%d  %d%%  旋转角度 %d  %s"),
				  (int) width_rotated, (int) height_rotated,
				  (int) config.scale, (int) oldangle,
				  config.bicubic ? _("三次立方") : _("两次线性"));
	else
		SPRINTF_S(infostr, _("%dx%d  %s  旋转角度 %d  %s"),
				  (int) width_rotated, (int) height_rotated,
				  conf_get_fitname(config.fit), (int) oldangle,
				  config.bicubic ? _("三次立方") : _("两次线性"));

	ilen = strlen(infostr);

	if (config.imginfobar) {
		if (config.load_exif && exif_array && exif_array->used > 0) {
			int width = exif_max_width();
			int height, line_num, top, left, right;
			int i;

			width =
				width > PSP_SCREEN_WIDTH - 10 ? PSP_SCREEN_WIDTH - 10 : width;
			height = PSP_SCREEN_HEIGHT / DISP_FONTSIZE - 1;
			line_num =
				exif_array->used <= height ? exif_array->used : height;
			top =
				(PSP_SCREEN_HEIGHT -
				 (1 + height) * DISP_FONTSIZE) / 2 >
				1 ? (PSP_SCREEN_HEIGHT - (1 + height) * DISP_FONTSIZE) / 2 : 1;
			left =
				(PSP_SCREEN_WIDTH - width) / 4 - 10 <
				1 ? 1 : (PSP_SCREEN_WIDTH - width) / 4 - 10;
			right =
				(PSP_SCREEN_WIDTH + 3 * width) / 4 >=
				PSP_SCREEN_WIDTH - 1 ? PSP_SCREEN_WIDTH -
				2 : (PSP_SCREEN_WIDTH + 3 * width) / 4;
			disp_fillrect(left, top, right, top + DISP_FONTSIZE * line_num, 0);
			disp_rectangle(left - 1, top - 1, right + 1,
						   top + DISP_FONTSIZE * line_num + 1, COLOR_WHITE);

			for (i = 0; i < line_num; ++i) {
				const char *teststr = exif_array->ptr[i]->ptr;

				disp_putnstring((PSP_SCREEN_WIDTH -
								 width) / 4,
								top + i * DISP_FONTSIZE,
								COLOR_WHITE,
								(const byte *) teststr,
								strlen(teststr), 0, 0, DISP_FONTSIZE, 0);
			}
		}

		disp_fillrect(0, PSP_SCREEN_HEIGHT - DISP_FONTSIZE, 479, 271, 0);
		disp_putnstring(0, PSP_SCREEN_HEIGHT - DISP_FONTSIZE,
						COLOR_WHITE,
						(const byte *) filelist[selidx].name,
						960 / DISP_FONTSIZE - ilen - 1, 0, 0, DISP_FONTSIZE, 0);
		disp_putnstring(PSP_SCREEN_WIDTH -
						DISP_FONTSIZE / 2 * ilen,
						PSP_SCREEN_HEIGHT - DISP_FONTSIZE,
						COLOR_WHITE, (const byte *) infostr,
						ilen, 0, 0, DISP_FONTSIZE, 0);
	} else {
		disp_fillrect(11, 11, 10 + DISP_FONTSIZE / 2 * ilen,
					  10 + DISP_FONTSIZE, 0);
		disp_putnstring(11, 11, COLOR_WHITE,
						(const byte *) infostr, ilen, 0, 0, DISP_FONTSIZE, 0);
	}
}