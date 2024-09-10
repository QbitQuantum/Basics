int
main(int argc, char *argv[])
{
	if (argc != 6)
	{
		fprintf(stderr, "Usage: %s <in bmp file> <out bmp file> <x> <y> <N>\n", argv[0]);
		return -1;
	}
	
	printf("Program started.\r\n");

	clock_t start_time = clock();

	int err_code = 0;
	try {
		// Read the input image
		bmp_in in;
		if ((err_code = bmp_in__open(&in, argv[1])) != 0)
			throw err_code;

		int location_x = atoi(argv[3]);
		int location_y = atoi(argv[4]);
		int out_size = atoi(argv[5]);

		int width = in.cols, height = in.rows;
		int n, num_comps = in.num_components;

		if (out_size % 2 == 1)
		{
			err_code = NOT_A_EVEN_NUMBER;
			throw err_code;
		}

		int half_outsize = out_size / 2;

		if (width < location_x) {
			err_code = X_ECCESS;
			throw err_code;
		}

		if (height < location_y) {
			err_code = Y_ECCESS;
			throw err_code;
		}

		my_aligned_image_comp *input_comps =
			new my_aligned_image_comp[num_comps];
		for (n = 0; n < num_comps; n++)
			input_comps[n].init(height, width, half_outsize+1); // Leave a border of output size

		int r; // Declare row index
		io_byte *line = new io_byte[width*num_comps];
		for (r = height - 1; r >= 0; r--)
		{ // "r" holds the true row index we are reading, since the image is
		  // stored upside down in the BMP file.
			if ((err_code = bmp_in__get_line(&in, line)) != 0)
				throw err_code;
			for (n = 0; n < num_comps; n++)
			{
				io_byte *src = line + n; // Points to first sample of component n
				float *dst = input_comps[n].buf + r * input_comps[n].stride;
				for (int c = 0; c < width; c++, src += num_comps)
					dst[c] = (float)*src; // The cast to type "float" is not
						  // strictly required here, since bytes can always be
						  // converted to floats without any loss of information.
			}
		}
		delete[] line;
		bmp_in__close(&in);

		// Allocate storage for the filtered output
		my_aligned_image_comp *output_comps =
			new my_aligned_image_comp[num_comps];

		for (n = 0; n < num_comps; n++) {
			output_comps[n].init(out_size, out_size, 0); // Don't need a border for output
		}

		  // Process the image, all in floating point (easy)
		for (n = 0; n < num_comps; n++) {
			input_comps[n].perform_boundary_extension();
		}

		for (int k = 0; k < num_comps; ++k)
			for (int i = -half_outsize; i < half_outsize; ++i)
				for (int j = -half_outsize; j < half_outsize; ++j) {
					output_comps[k].buf[(i+ half_outsize) * output_comps[k].stride + (j+ half_outsize)]
						= input_comps[k].buf[i * input_comps[k].stride + j 
						+ location_x + location_y * input_comps[k].stride];
				}

		for (n = 0; n < num_comps; n++) {
			output_comps[n].mean_substract();
			output_comps[n].hanning_window();
		}

		
		// Write the image back out again
		bmp_out out;
		io_byte *out_line = new io_byte[out_size*num_comps];
		if ((err_code = bmp_out__open(&out, argv[2], out_size, out_size, num_comps)) != 0)
			throw err_code;
		for (r = out_size - 1; r >= 0; r--)
		{ // "r" holds the true row index we are writing, since the image is
		  // written upside down in BMP files.
			for (n = 0; n < num_comps; n++)
			{
				io_byte *dst = out_line + n; // Points to first sample of component n
				float *src = output_comps[n].buf + r * output_comps[n].stride;
				for (int c = 0; c < out_size; c++, dst += num_comps) {
					
					if (src[c] > 255) {
						src[c] = 255;
					}
					else if (src[c] < 0) {
						src[c] = 0;
					}
						
					*dst = (io_byte)src[c];
				}
			}
			bmp_out__put_line(&out, out_line);
		}
		bmp_out__close(&out);
		delete[]out_line;
		delete[] input_comps;
		delete[] output_comps;

		clock_t end_time = clock();
		float elaps = ((float)(end_time - start_time)) / CLOCKS_PER_SEC;
		printf_s("The runtime is %f seconds!\n\r", elaps);
		system("Pause");

	}
	catch (int exc) {
		if (exc == IO_ERR_NO_FILE)
			fprintf(stderr, "Cannot open supplied input or output file.\n");
		else if (exc == IO_ERR_FILE_HEADER)
			fprintf(stderr, "Error encountered while parsing BMP file header.\n");
		else if (exc == IO_ERR_UNSUPPORTED)
			fprintf(stderr, "Input uses an unsupported BMP file format.\n  Current "
				"simple example supports only 8-bit and 24-bit data.\n");
		else if (exc == IO_ERR_FILE_TRUNC)
			fprintf(stderr, "Input or output file truncated unexpectedly.\n");
		else if (exc == IO_ERR_FILE_NOT_OPEN)
			fprintf(stderr, "Trying to access a file which is not open!(?)\n");
		else if (exc == X_ECCESS)
			fprintf(stderr, "The given location eccess x dimension!\n");
		else if (exc == Y_ECCESS)
			fprintf(stderr, "The given location eccess y dimension!\n");
		else if (exc == NOT_A_EVEN_NUMBER)
			fprintf(stderr, "The given output dimension is not a odd number!\n");
		return -1;
	}
	return 0;
}