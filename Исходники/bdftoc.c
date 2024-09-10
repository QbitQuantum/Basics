int main(int argc, char *argv[])
{
	struct bogl_font *font;
	int index_size = 0;
	int content_size = 0;
	int i, j, k, cp, n;
	char buf[MB_LEN_MAX + 1];

	setlocale(LC_ALL, "");

	/* Check for proper usage. */
	if (!argc == 2 ) {
		fprintf(stderr, "Usage:\n%s font.bdf > font.c\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Read font file. */
	font = bogl_read_bdf(argv[1]);
	if (!font) {
		return EXIT_FAILURE;
	}

	/* Output header. */
	printf("#include \"font.h\"\n");

	/* Output offsets, and get index_size and content_size. */
	printf("\n/* Offsets into index. */\n");
	printf("static int _%s_offset[%d] = {\n", font->name,
	       font->index_mask + 1);
	for (i = 0; i <= font->index_mask; i++) {
		printf("  %d, /* (0x%x) */\n", font->offset[i], i);
		for (j = font->offset[i]; font->index[j] != 0; j += 2) {
			k = font->index[j + 1] +
			    font->height *
			    (((font->index[j] & font->index_mask) +
			      31) / 32);
			if (k > content_size)
				content_size = k;
		}
		if (j > index_size)
			index_size = j;
	}
	++index_size;
	printf("};\n");

	/* Output index. */
	printf("\n/* Index into content data. */\n");
	printf("static int _%s_index[%d] = {\n", font->name, index_size);
	i = 0;
	while (i < index_size)
		if (font->index[i] != 0 && i < index_size - 1) {
			printf("  0x%x, %d,\n", font->index[i],
			       font->index[i + 1]);
			i += 2;
		} else if (font->index[i] == 0)
			printf("  %d,\n", font->index[i++]);
		else
			printf("  %d, /* Hm... */\n", font->index[i++]);
	printf("};\n");

	/* Print out each character's picture and data. */
	printf("\n/* Font character content data. */\n");
	printf("static u_int32_t _%s_content[] = {\n\n", font->name);
	cp = 0;
	while (cp < content_size) {
		int width = 0;
		for (i = 0; i <= font->index_mask; i++)
			for (j = font->offset[i]; font->index[j] != 0;
			     j += 2)
				if (font->index[j + 1] == cp) {
					wchar_t wc =
					    (font->index[j] & ~font->
					     index_mask) | i;
					int w =
					    font->index[j] & font->
					    index_mask;
					if (iswprint(wc)) {
						wctomb(0, 0);
						n = wctomb(buf, wc);
						buf[(n == -1) ? 0 : n] =
						    '\0';
						printf
						    ("/* %d: character %s (0x%lx), width %d */\n",
						     cp, buf, (long) wc,
						     w);
					} else
						printf
						    ("/* %d: unprintable character 0x%lx, width %d */\n",
						     cp, (long) wc, w);
					if (w > width)
						width = w;
				}
		if (width
		    && cp + font->height * ((width + 31) / 32) <=
		    content_size) {
			print_glyph(&font->content[cp], font->height,
				    width);
			printf("\n");
			cp += font->height * ((width + 31) / 32);
		} else
			printf("0x%08x,\n", font->content[cp++]);
	}
	printf("};\n\n");

	/* Print the font structure definition. */
	printf("/* Exported structure definition. */\n");
	printf("const struct Font %s_font = {\n", font->name);
	printf("  \"%s\",\n", font->name);
	printf("  %d,\n", font->height);
	printf("  0x%x,\n", font->index_mask);
	printf("  _%s_offset,\n", font->name);
	printf("  _%s_index,\n", font->name);
	printf("  _%s_content,\n", font->name);
	printf("};\n");

	return EXIT_SUCCESS;
}