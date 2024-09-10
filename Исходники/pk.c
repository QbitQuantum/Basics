static void
read_PK_char(struct font *fontp, wide_ubyte ch)
{
    int i, j;
    int n;
    int row_bit_pos;
    Boolean paint_switch;
    BMUNIT *cp;
    struct glyph *g;
    FILE *fp = fontp->file;
    long fpwidth;
    BMUNIT word = 0;
    int word_weight, bytes_wide;
    int rows_left, h_bit, count;

    g = &fontp->glyph[ch];
    PK_flag_byte = g->x2;
    PK_dyn_f = PK_flag_byte >> 4;
    paint_switch = ((PK_flag_byte & 8) != 0);
    PK_flag_byte &= 0x7;
    if (PK_flag_byte == 7)
	n = 4;
    else if (PK_flag_byte > 3)
	n = 2;
    else
	n = 1;

    if (debug & DBG_PK)
	Printf("loading pk char %d, char type %d ", ch, n);

    /*
     * now read rest of character preamble
     */
    if (n != 4)
	fpwidth = num(fp, 3);
    else {
	fpwidth = sfour(fp);
	(void)four(fp);	/* horizontal escapement */
    }
    (void)num(fp, n);	/* vertical escapement */
    {
	unsigned long w, h;

	w = num(fp, n);
	h = num(fp, n);
	if (w > 0x7fff || h > 0x7fff)
	    oops("Character %d too large in file %s", ch, fontp->fontname);
	g->bitmap.w = w;
	g->bitmap.h = h;
    }
    g->x = snum(fp, n);
    g->y = snum(fp, n);

    g->dvi_adv = fontp->dimconv * fpwidth;

    if (debug & DBG_PK) {
	if (g->bitmap.w != 0)
	    Printf(", size=%dx%d, dvi_adv=%ld", g->bitmap.w, g->bitmap.h,
		   g->dvi_adv);
	Putchar('\n');
    }

    alloc_bitmap(&g->bitmap);
    cp = (BMUNIT *) g->bitmap.bits;

    /*
     * read character data into *cp
     */
    bytes_wide = ROUNDUP((int)g->bitmap.w, BMBITS) * BMBYTES;
    PK_bitpos = -1;
    if (PK_dyn_f == 14) {	/* get raster by bits */
	bzero(g->bitmap.bits, (int)g->bitmap.h * bytes_wide);
	for (i = 0; i < (int)g->bitmap.h; i++) {	/* get all rows */
	    cp = ADD(g->bitmap.bits, i * bytes_wide);
#ifndef	WORDS_BIGENDIAN
	    row_bit_pos = -1;
#else
	    row_bit_pos = BMBITS;
#endif
	    for (j = 0; j < (int)g->bitmap.w; j++) {	/* get one row */
		if (--PK_bitpos < 0) {
		    word = one(fp);
		    PK_bitpos = 7;
		}
#ifndef	WORDS_BIGENDIAN
		if (++row_bit_pos >= BMBITS) {
		    cp++;
		    row_bit_pos = 0;
		}
#else
		if (--row_bit_pos < 0) {
		    cp++;
		    row_bit_pos = BMBITS - 1;
		}
#endif
		if (word & (1 << PK_bitpos))
		    *cp |= 1 << row_bit_pos;
	    }
	}
    }
    else {	/* get packed raster */
	rows_left = g->bitmap.h;
	h_bit = g->bitmap.w;
	PK_repeat_count = 0;
	word_weight = BMBITS;
	word = 0;
	while (rows_left > 0) {
	    count = PK_packed_num(fp);
	    while (count > 0) {
		if (count < word_weight && count < h_bit) {
#ifndef	WORDS_BIGENDIAN
		    if (paint_switch)
			word |= bit_masks[count] << (BMBITS - word_weight);
#endif
		    h_bit -= count;
		    word_weight -= count;
#ifdef	WORDS_BIGENDIAN
		    if (paint_switch)
			word |= bit_masks[count] << word_weight;
#endif
		    count = 0;
		}
		else if (count >= h_bit && h_bit <= word_weight) {
		    if (paint_switch)
			word |= bit_masks[h_bit] <<
#ifndef	WORDS_BIGENDIAN
			    (BMBITS - word_weight);
#else
			    (word_weight - h_bit);
#endif
		    *cp++ = word;
		    /* "output" row(s) */
		    for (i = PK_repeat_count * bytes_wide / BMBYTES; i > 0; --i) {
			*cp = *SUB(cp, bytes_wide);
			++cp;
		    }
		    rows_left -= PK_repeat_count + 1;
		    PK_repeat_count = 0;
		    word = 0;
		    word_weight = BMBITS;
		    count -= h_bit;
		    h_bit = g->bitmap.w;
		}
		else {
		    if (paint_switch)
#ifndef	WORDS_BIGENDIAN
			word |= bit_masks[word_weight] <<
			    (BMBITS - word_weight);
#else
			word |= bit_masks[word_weight];
#endif
		    *cp++ = word;
		    word = 0;
		    count -= word_weight;
		    h_bit -= word_weight;
		    word_weight = BMBITS;
		}
	    }
	    paint_switch = 1 - paint_switch;
	}
	if (cp != ((BMUNIT *) (g->bitmap.bits + bytes_wide * g->bitmap.h)))
	    oops("Wrong number of bits stored:  char. %d, font %s", ch,
		 fontp->fontname);
	if (rows_left != 0 || h_bit != g->bitmap.w)
	    oops("Bad pk file (%s), too many bits", fontp->fontname);
    }
}