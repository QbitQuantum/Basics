/*=====================app_main===========================*/
int app_main()
{
	int i = 0;
	void *capturebuffer0;
	void *displaybuffer;
	int counter = 0;
	int ret = 0;
	struct v4l2_format capture_fmt;
	struct v4l2_format display_fmt;
	int capture_chroma_offset, display_chroma_offset;
	int capture_size;
	int capture_fd, display_fd;
	char outputname[15];
	char stdname[15];
	int capture_numbuffers = MAX_BUFFER, display_numbuffers = MAX_BUFFER;

	for (i = 0; i < MAX_BUFFER; i++) {
		capture_buff_info[i].start = NULL;
		display_buff_info[i].start = NULL;
	}

	/* STEP1:
	 * Initialization section
	 * Initialize capture and display devices. 
	 * Here one capture channel is opened 
	 * Display channel is opened with the same standard that is detected at
	 * capture channel. same output name as input
	 * */

	/* open capture channel 0 */
	ret = initCapture(&capture_fd, &capture_numbuffers, &capture_fmt);
	if (ret < 0) {
		printf("Error in opening capture device for channel 0\n");
		return ret;
	}

	printf(" Capture initialized\n");
	/* open display channel */
	if (display_enable) {
		ret = initDisplay(&display_fd, &display_numbuffers, &display_fmt);
		if (ret < 0) {
			printf("Error in opening display device\n");
			return ret;
		}
		printf(" Display initialized\n");
		/* run section
		 * STEP2:
		 * Here display and capture channels are started for streaming. After 
		 * this capture device will start capture frames into enqueued 
		 * buffers and display device will start displaying buffers from 
		 * the qneueued buffers */

		/* start display */
		ret = startDisplay(&display_fd);
		if (ret < 0) {
			printf("Error in starting display\n");
			return ret;
		}
		printf(" display started \n");
	}
	/* start capturing for channel 0 */
	ret = startCapture(&capture_fd);
	if (ret < 0) {
		printf("Error in starting capturing for channel 0\n");
		return ret;
	}

	printf(" capture started \n");

	/* calculate the offset from where chroma data will be stored for 
	 * both capture and display */
	capture_chroma_offset = kernel_buf_size/2;
	//display_chroma_offset = display_fmt.fmt.pix.sizeimage / 2;
	display_chroma_offset = kernel_buf_size/2;
	capture_size = capture_fmt.fmt.pix.width * capture_fmt.fmt.pix.height;

	/* One buffer is dequeued from display and capture channels.
	 * Capture buffer will be copied to display buffer.
	 * All two buffers are put back to respective channels.
	 * This sequence is repeated in loop.
	 * After completion of this loop, channels are stopped.
	 * */
	printf("Going into loopback\n");

#if 0
	sleep(10);
#else
	while (1) {
		/* get capturing buffer for channel 0 */
		capturebuffer0 = getCaptureBuffer(&capture_fd);
		if (NULL == capturebuffer0) {
			printf("Error in get capture buffer for channel 0\n");
			return ret;
		}

		/* get display buffer */
		if (display_enable) {
			displaybuffer = getDisplayBuffer(&display_fd);
			if (NULL == displaybuffer) {
				printf("Error in get display buffer\n");
				return ret;
			}

			/* Copy Luma data from capture buffer to display buffer */
			memcpy(displaybuffer, capturebuffer0, capture_size);
			/* Copy chroma data from capture buffer to display buffer
			 * from the appropriate offsets in capture buffer and 
			 * display buffer */
			memcpy(displaybuffer + display_chroma_offset,
				capturebuffer0 + capture_chroma_offset,
				capture_size);

			/* put output buffer into display queue */
			ret = putDisplayBuffer(&display_fd, display_numbuffers,
					       displaybuffer);
			if (ret < 0) {
				printf("Error in put display buffer\n");
				return ret;
			}
		}
		if (save_frame && counter == 100) {
			fwrite(capturebuffer0, 1, capture_size,
				file_fp);
			fwrite(capturebuffer0 + capture_chroma_offset,
				1, capture_size,
				file_fp); 
			fclose(file_fp);
		}

		/* put buffers in capture channels */
		ret = putCaptureBuffer(&capture_fd, capture_numbuffers,
				       capturebuffer0);
		if (ret < 0) {
			printf("Error in put capture buffer for channel 0\n");
			return ret;
		}
		counter++;


		if (print_fn)
			printf("time:%lu    frame:%u\n", (unsigned long)time(NULL), counter);

		if (stress_test && counter >= MAXLOOPCOUNT)
			break;
	}
#endif

	printf("After sleep, stop capture/display\n");
	/* stop display */
	if (display_enable) {
		ret = stopDisplay(&display_fd);
		if (ret < 0) {
			printf("Error in stopping display\n");
			return ret;
		}
	}
	/* stop capturing for channel 0 */
	ret = stopCapture(&capture_fd);
	if (ret < 0) {
		printf("Error in stopping capturing for channel 0\n");
		return ret;
	}

	/* close capture channel 0 */
	ret = releaseCapture(&capture_fd, capture_numbuffers);
	if (ret < 0) {
		printf("Error in closing capture device\n");
		return ret;
	}
	/* Free section
	 * Here channels for capture and display are close.
	 * */
	/* open display channel */
	if (display_enable) {
		ret = releaseDisplay(&display_fd, display_numbuffers);
		if (ret < 0) {
			printf("Error in closing display device\n");
			return ret;
		}
	}
	return ret;
}