void Node::detect3DLines(const cv::Mat& gray_uchar, const cv::Mat& depth_float, double line2d_len_thres, 
                      const cv::Mat& K,double ratio_of_collinear_pts, double line_3d_len_thres_m, double depth_scaling, string algorithm)
{
//	MyTimer tm; tm.start();	
	
	vector<FrameLine> allLines; // 2d and 3d lines
	if(algorithm == "LSD") { // using LSD, 100+ ms
		IplImage pImg = gray_uchar;
		ntuple_list  lsdOut;	
		lsdOut = callLsd(&pImg);// use LSD method
		int dim = lsdOut->dim;
		double a,b,c,d;
		allLines.reserve(lsdOut->size);
		for(int i=0; i<lsdOut->size; i++) {// store LSD output to lineSegments 
			a = lsdOut->values[i*dim];
			b = lsdOut->values[i*dim+1];
			c = lsdOut->values[i*dim+2];
			d = lsdOut->values[i*dim+3];
			if ( sqrt((a-c)*(a-c)+(b-d)*(b-d)) > line2d_len_thres) {
				allLines.push_back(FrameLine(cv::Point2d(a,b), cv::Point2d(c,d)));
			}
		}	
		
	}
    
	if(algorithm == "EDLINES") { // using EDlines, 15 ms
		int n;
		LS* ls = callEDLines(gray_uchar, &n);
		allLines.reserve(n);
		for(int i=0; i<n; i++) {// store output to lineSegments 
			if ((ls[i].sx-ls[i].ex)*(ls[i].sx-ls[i].ex) +(ls[i].sy-ls[i].ey)*(ls[i].sy-ls[i].ey) 
				> line2d_len_thres*line2d_len_thres) {
				allLines.push_back(FrameLine(cv::Point2d(ls[i].sx,ls[i].sy), cv::Point2d(ls[i].ex,ls[i].ey)));
			}
		}
	}

	Eigen::Matrix3d eK;
	for(int i=0; i<3; ++i)
		for(int j=0; j<3; ++j)
			eK(i,j) = K.at<double>(i,j);
	Eigen::Matrix3d Kinv = eK.inverse();	
 

 	
 	int depth_CVMatDepth = depth_float.depth();
  	#pragma omp parallel for
	for(int i=0; i<allLines.size(); ++i)	{ // 20 -30 ms
		double len = cv::norm(allLines[i].p - allLines[i].q);		
		// iterate through a line
		double numSmp = min(max(len/sysPara.line_sample_interval, (double)sysPara.line_sample_min_num), (double)sysPara.line_sample_max_num);  // smaller numSmp for fast speed, larger numSmp should be more accurate	
   		vector<cv::Point3d> pts3d; pts3d.reserve(numSmp);
		for(int j=0; j<=numSmp; ++j) {
			// use nearest neighbor to querry depth value
			// assuming position (0,0) is the top-left corner of image, then the
			// top-left pixel's center would be (0.5,0.5)
			cv::Point2d pt = allLines[i].p * (1-j/numSmp) + allLines[i].q * (j/numSmp);
			if(pt.x<0 || pt.y<0 || pt.x >= depth_float.cols || pt.y >= depth_float.rows ) continue;
			int row, col; // nearest pixel for pt
			if((floor(pt.x) == pt.x) && (floor(pt.y) == pt.y)) {// boundary issue
				col = max(int(pt.x-1),0);
				row = max(int(pt.y-1),0);
			} else {
				col = int(pt.x);
				row = int(pt.y);
			}
			double zval = -1;
			double depval;
			if(depth_CVMatDepth == CV_32F) 
				depval = depth_float.at<float>(row,col);
			else if (depth_CVMatDepth == CV_64F) 
				depval = depth_float.at<double>(row,col);
			else {
				cerr<<"Node::extractLineDepth: depth image matrix type is not float/double\n";
				exit(0);	
			}	
			if(depval < EPS || isnan((float)depval)) { // no depth info

			} else {
				zval = depval/depth_scaling; // in meter, z-value
			}

			if (zval > 0 ) {
				Eigen::Vector3d ept(pt.x, pt.y, 1);
				Eigen::Vector3d xy3d = Kinv * ept;
				xy3d = xy3d/xy3d(2);
				pts3d.push_back(cv::Point3d(xy3d(0)*zval, xy3d(1)*zval, zval));								
			}
		}
		if (pts3d.size() < max(10.0, numSmp *ratio_of_collinear_pts))
			continue;

		RandomLine3d tmpLine;		
		vector<RandomPoint3d> rndpts3d;
		rndpts3d.reserve(pts3d.size());
		// compute uncertainty of 3d points
		for(int j=0; j<pts3d.size();++j) {
			rndpts3d.push_back(compPt3dCov(pts3d[j], K, asynch_time_diff_sec_));
		}
		// using ransac to extract a 3d line from 3d pts
		tmpLine = extract3dline_mahdist(rndpts3d);
		
		if(tmpLine.pts.size()/numSmp > ratio_of_collinear_pts	&&
			cv::norm(tmpLine.A - tmpLine.B) > line_3d_len_thres_m) {
				allLines[i].haveDepth = true;
				allLines[i].line3d = tmpLine;
				
		}		
	}	

//// prepare for compute msld line descriptors
	cv::Mat xGradImg, yGradImg;
	int ddepth = CV_64F;	
	cv::Sobel(gray_uchar, xGradImg, ddepth, 1, 0, 5); // Gradient X
	cv::Sobel(gray_uchar, yGradImg, ddepth, 0, 1, 5); // Gradient Y
	double	*xG, *yG;
	if(xGradImg.isContinuous() && yGradImg.isContinuous()) {
		xG = (double*) xGradImg.data;
		yG = (double*) yGradImg.data;
	} else { 
		xG = new double[xGradImg.rows*xGradImg.cols];
 		yG = new double[yGradImg.rows*yGradImg.cols];
 		int idx = 0;
    	for(int i=0; i<xGradImg.rows; ++i) {
    		for(int j=0; j<xGradImg.cols; ++j) {
    			xG[idx] = xGradImg.at<double>(i,j);
    			yG[idx] = yGradImg.at<double>(i,j);
    			++idx;
    		}
    	}
	}

	lines.reserve(allLines.size());
	// NOTE this for-loop mustnot be parallized
	for(int i=0; i<allLines.size(); ++i) {
		if(allLines[i].haveDepth) { 
			lines.push_back(allLines[i]);
			lines.back().lid = lines.size()-1;
			lines.back().complineEq2d();				
			lines.back().r = lines.back().getGradient(&xGradImg, &yGradImg);
		}
	}
	

	#pragma omp parallel for
	for(int i=0; i<lines.size(); ++i) {		// 60 ms, 0.6ms/line
		computeMSLD(lines[i], xG, yG, gray_uchar.cols, gray_uchar.rows); // 0.1 ms/line
		MLEstimateLine3d(lines[i].line3d, sysPara.line3d_mle_iter_num);
		vector<RandomPoint3d> ().swap(lines[i].line3d.pts); // swap with a empty vector effectively free up the memory, clear() doesn't.
	}
//	tm.end(); cout<<"detect 3d lines "<<tm.time_ms<<" ms\n";

	if(!xGradImg.isContinuous() || !yGradImg.isContinuous()) { // dynamic allocation
		delete[] xG; 
		delete[] yG;
	}

}