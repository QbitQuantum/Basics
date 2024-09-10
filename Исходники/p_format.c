static void r_print_format_time(const RPrint* p, int endian, int mode,
		const char* setval, ut64 seeki, ut8* buf, int i, int size) {
	ut64 addr;
	int elem = -1;
	if (size >= ARRAYINDEX_COEF) {
		elem = size/ARRAYINDEX_COEF-1;
		size %= ARRAYINDEX_COEF;
	}
	updateAddr (buf, i, endian, &addr, NULL);
	if (MUSTSET) {
		p->cb_printf ("wv4 %s @ 0x%08"PFMT64x"\n", setval, seeki+((elem>=0)?elem*4:0));
	} else if (MUSTSEE) {
		char *timestr = strdup(asctime (gmtime ((time_t*)&addr)));
		*(timestr+24) = '\0';
		if (!SEEVALUE) p->cb_printf ("0x%08"PFMT64x" = ", seeki+((elem>=0)?elem*4:0));
		if (size==-1) {
			p->cb_printf ("%s", timestr);
		} else {
			if (!SEEVALUE) p->cb_printf ("[ ");
			while (size--) {
				updateAddr (buf, i, endian, &addr, NULL);
				free (timestr);
				timestr = strdup (asctime (gmtime ((time_t*)&addr)));
				*(timestr+24) = '\0';
				if (elem == -1 || elem == 0) {
					p->cb_printf ("%s", timestr);
					if (elem == 0) elem = -2;
				}
				if (size != 0 && elem == -1)
					p->cb_printf (", ");
				if (elem > -1) elem--;
				i += 4;
			}
			if (!SEEVALUE) p->cb_printf (" ]");
		}
		free (timestr);
	} else if (MUSTSEEJSON) {
		char *timestr = strdup (asctime (gmtime ((time_t*)&addr)));
		*(timestr+24) = '\0';
		if (size==-1) {
			p->cb_printf ("\"%s\"", timestr);
		} else {
			p->cb_printf ("[ ");
			while (size--) {
				updateAddr (buf, i, endian, &addr, NULL);
				free (timestr);
				timestr = strdup (asctime (gmtime ((time_t*)&addr)));
				*(timestr+24) = '\0';
				if (elem == -1 || elem == 0) {
					p->cb_printf ("\"%s\"", timestr);
					if (elem == 0) elem = -2;
				}
				if (size != 0 && elem == -1)
					p->cb_printf (", ");
				if (elem > -1) elem--;
				i += 4;
			}
			p->cb_printf (" ]");
		}
		free (timestr);
		p->cb_printf ("}");
	}
}