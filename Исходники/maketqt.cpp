int	main(int argc, char* argv[])
{
	char*	infile = NULL;
	char*	outfile = NULL;
	int	tree_depth = 6;
	int	tile_size = 256;

	for ( int arg = 1; arg < argc; arg++ ) {
		if ( argv[arg][0] == '-' ) {
			// command-line switch.
			
			switch ( argv[arg][1] ) {
			case 'h':
			case '?':
				print_usage();
				exit( 1 );
				break;

			case 't':
				// Set the tilesize.
				if (arg + 1 >= argc) {
					printf("error: -t option requires an integer for tile_size\n");
					print_usage();
					exit(1);
				}
				arg++;
				tile_size = atoi(argv[arg]);
				break;
			case 'd':
				// Tree depth.
				if (arg + 1 >= argc) {
					printf("error: -d option requires an integer for tree_depth\n");
					print_usage();
					exit(1);
				}
				arg++;
				tree_depth = atoi(argv[arg]);
				break;

			default:
				printf("error: unknown command-line switch -%c\n", argv[arg][1]);
				exit(1);
				break;
			}

		} else {
			// File argument.
			if ( infile == NULL ) {
				infile = argv[arg];
			} else if ( outfile == NULL ) {
				outfile = argv[arg];
			} else {
				// This looks like extra noise on the command line; complain and exit.
				printf( "argument '%s' looks like extra noise; exiting.\n", argv[arg]);
				print_usage();
				exit( 1 );
			}
		}
	}

	// Must specify input filename.
	if (infile == NULL) {
		printf("error: you must supply an input filename which points to a .jpg image\n");
		print_usage();
		exit(1);
	}

	// Must specify an output filename.
	if (outfile == NULL) {
		printf("error: you must specify an output filename, for the texture quadtree output\n");
		print_usage();
		exit(1);
	}

	// Validate the tile_size.  Must be a power of two.
	int	logged_tile_size = 1 << frnd(log2((float) tile_size));
	if (tile_size <= 0 || logged_tile_size != tile_size) {
		printf("error: tile_size must be a power of two.\n");
		print_usage();
		exit(1);
	}

	// Validate tree depth.  Keep it within reason.
	if (tree_depth <= 0 || tree_depth > 12)
	{
		printf("error: tree_depth out of range.  Keep it between 1 and 12.\n");
		print_usage();
		exit(1);
	}
	
	// Open input file.
	tu_file*	in = new tu_file(infile, "rb");
	if (in->get_error())
	{
		printf("Can't open input file '%s'!\n", infile);
		delete in;
		exit(1);
	}

	// Open output file.
	tu_file*	out = new tu_file(outfile, "w+b");
	if (out->get_error())
	{
		printf("Can't open output file '%s'!\n", outfile);
		delete in;
		delete out;
		exit(1);
	}

	// Start reading the input.
	jpeg::input*	j_in = jpeg::input::create(in);
	if (j_in == NULL) {
		printf("Failure reading JPEG header of input file '%s'!\n", infile);
		delete in;
		delete out;
		exit(1);
	}

	// Size the tiles.
	int	tile_dim = 1 << (tree_depth - 1);

	// Write .tqt header.
	out->write_bytes("tqt\0", 4);	// filetype tag
	out->write_le32(1);			// version number.
	out->write_le32(tree_depth);
	out->write_le32(tile_size);

	// Make a null table of contents, and write it to the file.
	array<Uint32>	toc;
	toc.resize(tqt::node_count(tree_depth));

	int	toc_start = out->get_position();
	for (int i = 0; i < toc.size(); i++) {
		toc[i] = 0;
		out->write_le32(toc[i]);
	}

	int	tile_max_source_height = int(j_in->get_height() / float(tile_dim) + 1);

	// Create a horizontal strip, as wide as the image, and tall
	// enough to cover a whole tile.
	image::rgb*	strip = image::create_rgb(j_in->get_width(), tile_max_source_height);

	// Initialize the strip by reading the first set of scanlines.
	int	next_scanline = 0;
	int	strip_top = 0;
	while (next_scanline < tile_max_source_height) {
		j_in->read_scanline(image::scanline(strip, next_scanline));
		next_scanline++;
	}

	image::rgb*	tile = image::create_rgb(tile_size, tile_size);

	printf("making leaf tiles....     ");

	// generate base level tiles.
	for (int row = 0; row < tile_dim; row++) {
		float	y0 = float(row) / tile_dim * j_in->get_height();
		float	y1 = float(row + 1) / tile_dim * j_in->get_height();

		int	lines_to_read = imin(int(y1), j_in->get_height()) - (strip_top + strip->m_height);
		if (lines_to_read > 0)
		{
			// Copy existing lines up...
			int	lines_to_keep = strip->m_height - lines_to_read;
			{for (int i = 0; i < lines_to_keep; i++) {
				memcpy(image::scanline(strip, i), image::scanline(strip, i + lines_to_read /*keep*/), strip->m_width * 3);
			}}

			// Read new lines
			{for (int i = lines_to_keep; i < strip->m_height; i++) {
				j_in->read_scanline(image::scanline(strip, i));
			}}

			strip_top += lines_to_read;
		}

		for (int col = 0; col < tile_dim; col++) {
			float	x0 = float(col) / tile_dim * j_in->get_width();
			float	x1 = float(col + 1) / tile_dim * j_in->get_width();

			// Resample from the input strip to the output tile.
			image::resample(tile, 0, 0, tile_size - 1, tile_size - 1,
					strip, x0, y0 - strip_top, x1, y1 - strip_top);

			// Update the table of contents with an offset
			// to the data we're about to write.
			int	offset = out->get_position();
			int	quadtree_index = tqt::node_index(tree_depth - 1, col, row);
			toc[quadtree_index] = offset;

			// Write the jpeg data.
			image::write_jpeg(out, tile, 90);

			int	percent_done = int(100.f * float(col + row * tile_dim) / (tile_dim * tile_dim));
			printf("\b\b\b\b\b\b%3d%% %c", percent_done, spinner[(spin_count++)&3]);
		}
	}


	// Done reading the input file.
	delete j_in;
	delete in;

	delete strip;
	delete tile;	// done with the working tile surface.

	printf("\n");

	printf("making interior tiles....");

	// Now generate the upper levels of the tree by resampling the
	// lower levels.
	// 
	// The output file is both input and output at this point.
	tqt_info	inf(out, &toc, tree_depth, tile_size);
	image::rgb*	root_tile = generate_tiles(&inf, 0, 0, 0);

	delete root_tile;	// dispose of root tile.

	// Write the TOC back into the head of the file.
	out->set_position(toc_start);
	{for (int i = 0; i < toc.size(); i++) {
		out->write_le32(toc[i]);
	}}

	delete out;

	return 0;
}