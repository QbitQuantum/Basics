BlobImageProcessorYUV::SegmentList BlobImageProcessorYUV::getSegments(int y, /*const*/ Image &image) const {
#else
BlobImageProcessorYUV::SegmentList BlobImageProcessorYUV::getSegments(int y, const Image &image) const {
#endif
	SegmentList segments;
	Segment cursegment = { -1, -1 };
	int gapcount = 0;
	int x;

	for (x=0; x<image.getWidth(); x++) {
		Pixel pixel = image.getPixel(x, y);
		if (checkModels(pixel)) { // if the pixel is valid

            #ifdef ENABLE_BLUEMARKER
            if(enable_bluemarker)
            {
                // Added by Jeremy
                //Pixel *bluemarker = new Pixel(0, 0, 255);
                Pixel *bluemarker = new Pixel(29, 255, 107); // YUV for blue
                image.setPixel(x, y, *bluemarker); // Mark pixel as bright blue for a match
                delete(bluemarker);
            }
            #endif

			if (cursegment.start == -1) { // if its the first pixel in a row
				cursegment.start = x; // start a new segment
				if (debug)
					cout << "New segment starting at (" << x << "," << y << ")" << endl;
			}

			gapcount = 0; // any valid pixel resets the gap counter
		} else if (cursegment.start >= 0) { // pixel not valid, but we're in a row
			if (++gapcount > maxgapdist) { // if we've exceeded the maximum gap count
				cursegment.end = x - maxgapdist; // set the end of the segment
				if (cursegment.end - cursegment.start >= minsegmentsize) { // if the segment is large enough
					segments.push_back(cursegment); // save it
					if (debug)
						cout << "segment saved, ends at " << cursegment.end << endl;
				} else {
					if (debug)
						cout << "segment rejected due to width (" << cursegment.end - cursegment.start << ")" << endl;
				}
				cursegment.start = -1;
			}
		}
	}

	// if a segment goes off the side of the image, but is wide enough
	if (cursegment.start > 0) {
		if (image.getWidth() - cursegment.start >= minsegmentsize) {
			cursegment.end = image.getWidth()-1-gapcount;
			segments.push_back(cursegment);
			if (debug)
				cout << "Saving segment, hit edge of screen" << endl;
		} else {
			if (debug)
				cout << "Segment hit edge of screen, rejected due to width (" << cursegment.end - cursegment.start << "(" << endl;
		}
	}

	return segments;
}