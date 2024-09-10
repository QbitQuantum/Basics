void BoatDetector::houghline(IplImage* edgeImage, IplImage* image, IplImage* lineImage) {

	//validation
	int points = 50; // points per row
	int rows = 3; // number of rows
	int ver_dist = 10; // vertical distance between points
	int hor_dist = image->width / points; // horizontal distance between points

	cvCopy(edgeImage, lineImage);

	CvSeq* hough_lines = 0;

	CvScalar line_color = cvScalar(120);

	hough_lines = cvHoughLines2( edgeImage, hough_storage, CV_HOUGH_STANDARD, 1, CV_PI/180, 100, 0, 0 );


	if(hough_lines->total == 0) {
		return;
	}

	bool find = false;

	CvPoint pt1, pt2;
	float* line;
	float theta;
	float rho;
	double a, b, x0, y0;
	for( int i = 0; i < min(hough_lines->total, 100); i++ )
	{
		line = (float*)cvGetSeqElem(hough_lines, i);
		theta = line[1];
		if(theta < 1.50 || theta > 1.60) {
			continue;
		}
		rho = line[0];

		a = cos(theta);
		b = sin(theta);
		x0 = a*rho;
		y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));		

		cvLine( lineImage, pt1, pt2, line_color, 2, CV_AA, 0 );
		find = true;
	}
	if(!find) {
		return;
	}

	bool run = true;
	int search_limit = lineImage->height - (ver_dist * rows);
	int line_step = lineImage->widthStep/sizeof(char);
	int img_step = image->widthStep/sizeof(char);
	int max_left, max_right;
	int tmp_limit;
	double count;
	while(run) {
		max_left = 0;
		max_right = 0;
		for(int i = ver_dist * rows; i < search_limit; i++) {
			if(((uchar)lineImage->imageData[i*line_step+3]) == line_color.val[0]) {
				if(i > max_left) {
					max_left = i;
				}
			}
			if(((uchar)lineImage->imageData[i*line_step + (lineImage->width-3)]) == line_color.val[0]) {
				if(i > max_right) {
					max_right = i;
				}
			}		
		}
		if(max_left == 0 || max_right == 0) {
			run = false;
			continue;
		}

		tmp_limit = (max_left + max_right) / 2;

		//limit validation
		count = 0;
		if(abs(max_left - max_right) < 10) {

			for(int i = tmp_limit - (ver_dist * rows), k = 0, t = rows*2; k < rows; i+=ver_dist, k++, t-=2) {
				for(int j = hor_dist; j < image->width; j+=hor_dist) {
					if(abs(image->imageData[i*img_step + j] -
						image->imageData[(i+t*ver_dist)*img_step + j] ) > 10 )
					{
						count++;
					}
				}
			}
		}
		if((count / (points * rows)) > 0.9 ) {

			sea_limit = tmp_limit;

			/*
			IplImage* ao = cvCloneImage(image);
			for(int i = tmp_limit - (ver_dist * rows), k = 0, t = rows*2; k < rows; i+=ver_dist, k++, t-=2) {
				for(int j = hor_dist; j < image->width; j+=hor_dist) {
					if(abs(image->imageData[i*img_step + j] -
							image->imageData[(i+t*ver_dist)*img_step + j] ) > 10 )
					{
						cvLine(ao, cvPoint(j,i), cvPoint(j,i), CV_RGB(0,0,0), 3);
						cvLine(ao, cvPoint(j,i+t*ver_dist), cvPoint(j,i+t*ver_dist), CV_RGB(255,255,255), 3);
					}
				}
			}

			cvShowImage("ao",ao);
			cvWaitKey(0);
			*/

			run = false;
		}
		else {
			search_limit = max(max_left, max_right);
		}
	}
}