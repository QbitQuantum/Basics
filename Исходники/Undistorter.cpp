UndistorterPTAM::UndistorterPTAM(const char* configFileName)
{
	valid = true;

	remapX = nullptr;
	remapY = nullptr;

	
	
	// read parameters
	std::ifstream infile(configFileName);
	assert(infile.good());


	std::string l1,l2,l3,l4;

	std::getline(infile,l1);
	std::getline(infile,l2);
	std::getline(infile,l3);
	std::getline(infile,l4);




	// l1 & l2
	if(std::sscanf(l1.c_str(), "%f %f %f %f %f", &inputCalibration[0], &inputCalibration[1], &inputCalibration[2], &inputCalibration[3], &inputCalibration[4]) == 5 &&
			std::sscanf(l2.c_str(), "%d %d", &in_width, &in_height) == 2)
	{
		printf("Input resolution: %d %d\n",in_width, in_height);
		printf("In: %f %f %f %f %f\n",
				inputCalibration[0], inputCalibration[1], inputCalibration[2], inputCalibration[3], inputCalibration[4]);
	}
	else
	{
		printf("Failed to read camera calibration (invalid format?)\nCalibration file: %s\n", configFileName);
		valid = false;
	}

	// l3
	if(l3 == "crop")
	{
		outputCalibration[0] = -1;
		printf("Out: Crop\n");
	}
	else if(l3 == "full")
	{
		outputCalibration[0] = -2;
		printf("Out: Full\n");
	}
	else if(l3 == "none")
	{
		printf("NO RECTIFICATION\n");
	}
	else if(std::sscanf(l3.c_str(), "%f %f %f %f %f", &outputCalibration[0], &outputCalibration[1], &outputCalibration[2], &outputCalibration[3], &outputCalibration[4]) == 5)
	{
		printf("Out: %f %f %f %f %f\n",
				outputCalibration[0], outputCalibration[1], outputCalibration[2], outputCalibration[3], outputCalibration[4]);
	}
	else
	{
		printf("Out: Failed to Read Output pars... not rectifying.\n");
		valid = false;
	}


	// l4
	if(std::sscanf(l4.c_str(), "%d %d", &out_width, &out_height) == 2)
	{
		printf("Output resolution: %d %d\n",out_width, out_height);
	}
	else
	{
		printf("Out: Failed to Read Output resolution... not rectifying.\n");
		valid = false;
	}




	// prep warp matrices
	if(valid)
	{
		float dist = inputCalibration[4];
		float d2t = 2.0f * tan(dist / 2.0f);

		// current camera parameters
		float fx = inputCalibration[0] * in_width;
		float fy = inputCalibration[1] * in_height;
		float cx = inputCalibration[2] * in_width - 0.5;
		float cy = inputCalibration[3] * in_height - 0.5;
		
		// scale calibration parameters to input size
		double xfactor = in_width / (1.0 * in_width);
		double yfactor = in_height / (1.0 * in_height);
		fx = fx * xfactor;
		fy = fy * yfactor;
		cx = (cx + 0.5) * xfactor - 0.5;
		cy = (cy + 0.5) * yfactor - 0.5;

		// output camera parameters
		float ofx, ofy, ocx, ocy;

		// find new camera matrix for "crop" and "full"
		if (inputCalibration[4] == 0)
		{
			ofx = inputCalibration[0] * out_width;
			ofy = inputCalibration[1] * out_height;
			ocx = (inputCalibration[2] * out_width) - 0.5;
			ocy = (inputCalibration[3] * out_height) - 0.5;
		}
		else if(outputCalibration[0] == -1)	// "crop"
		{
			// find left-most and right-most radius
			float left_radius = (cx)/fx;
			float right_radius = (in_width-1 - cx)/fx;
			float top_radius = (cy)/fy;
			float bottom_radius = (in_height-1 - cy)/fy;

			float trans_left_radius = tan(left_radius * dist)/d2t;
			float trans_right_radius = tan(right_radius * dist)/d2t;
			float trans_top_radius = tan(top_radius * dist)/d2t;
			float trans_bottom_radius = tan(bottom_radius * dist)/d2t;

			//printf("left_radius: %f -> %f\n", left_radius, trans_left_radius);
			//printf("right_radius: %f -> %f\n", right_radius, trans_right_radius);
			//printf("top_radius: %f -> %f\n", top_radius, trans_top_radius);
			//printf("bottom_radius: %f -> %f\n", bottom_radius, trans_bottom_radius);


			ofy = fy * ((top_radius + bottom_radius) / (trans_top_radius + trans_bottom_radius)) * ((float)out_height / (float)in_height);
			ocy = (trans_top_radius/top_radius) * ofy*cy/fy;

			ofx = fx * ((left_radius + right_radius) / (trans_left_radius + trans_right_radius)) * ((float)out_width / (float)in_width);
			ocx = (trans_left_radius/left_radius) * ofx*cx/fx;

			printf("new K: %f %f %f %f\n",ofx,ofy,ocx,ocy);
			printf("old K: %f %f %f %f\n",fx,fy,cx,cy);
		}
		else if(outputCalibration[0] == -2)	 // "full"
		{
			float left_radius = cx/fx;
			float right_radius = (in_width-1 - cx)/fx;
			float top_radius = cy/fy;
			float bottom_radius = (in_height-1 - cy)/fy;

			// find left-most and right-most radius
			float tl_radius = sqrt(left_radius*left_radius + top_radius*top_radius);
			float tr_radius = sqrt(right_radius*right_radius + top_radius*top_radius);
			float bl_radius = sqrt(left_radius*left_radius + bottom_radius*bottom_radius);
			float br_radius = sqrt(right_radius*right_radius + bottom_radius*bottom_radius);

			float trans_tl_radius = tan(tl_radius * dist)/d2t;
			float trans_tr_radius = tan(tr_radius * dist)/d2t;
			float trans_bl_radius = tan(bl_radius * dist)/d2t;
			float trans_br_radius = tan(br_radius * dist)/d2t;

			//printf("trans_tl_radius: %f -> %f\n", tl_radius, trans_tl_radius);
			//printf("trans_tr_radius: %f -> %f\n", tr_radius, trans_tr_radius);
			//printf("trans_bl_radius: %f -> %f\n", bl_radius, trans_bl_radius);
			//printf("trans_br_radius: %f -> %f\n", br_radius, trans_br_radius);


			float hor = std::max(br_radius,tr_radius) + std::max(bl_radius,tl_radius);
			float vert = std::max(tr_radius,tl_radius) + std::max(bl_radius,br_radius);

			float trans_hor = std::max(trans_br_radius,trans_tr_radius) + std::max(trans_bl_radius,trans_tl_radius);
			float trans_vert = std::max(trans_tr_radius,trans_tl_radius) + std::max(trans_bl_radius,trans_br_radius);

			ofy = fy * ((vert) / (trans_vert)) * ((float)out_height / (float)in_height);
			ocy = std::max(trans_tl_radius/tl_radius,trans_tr_radius/tr_radius) * ofy*cy/fy;

			ofx = fx * ((hor) / (trans_hor)) * ((float)out_width / (float)in_width);
			ocx = std::max(trans_bl_radius/bl_radius,trans_tl_radius/tl_radius) * ofx*cx/fx;

			printf("new K: %f %f %f %f\n",ofx,ofy,ocx,ocy);
			printf("old K: %f %f %f %f\n",fx,fy,cx,cy);
		}
		else
		{
			ofx = outputCalibration[0] * out_width;
			ofy = outputCalibration[1] * out_height;
			ocx = outputCalibration[2] * out_width-0.5;	// TODO: -0.5 here or not?
			ocy = outputCalibration[3] * out_height-0.5;
		}

		outputCalibration[0] = ofx / out_width;
		outputCalibration[1] = ofy / out_height;
		outputCalibration[2] = (ocx+0.5) / out_width;
		outputCalibration[3] = (ocy+0.5) / out_height;
		outputCalibration[4] = 0;

		remapX = (float*)Eigen::internal::aligned_malloc(out_width * out_height *sizeof(float));
		remapY = (float*)Eigen::internal::aligned_malloc(out_width * out_height *sizeof(float));

		for(int y=0;y<out_height;y++)
		{
			for(int x=0;x<out_width;x++)
			{
				float ix = (x - ocx) / ofx;
				float iy = (y - ocy) / ofy;

				float r = sqrt(ix*ix + iy*iy);
				float fac = (r==0 || dist==0) ? 1 : atan(r * d2t)/(dist*r);

				ix = fx*fac*ix+cx;
				iy = fy*fac*iy+cy;

				// make rounding resistant.
				if(ix == 0) ix = 0.01;
				if(iy == 0) iy = 0.01;
				if(ix == in_width-1) ix = in_width-1.01;
				if(iy == in_height-1) ix = in_height-1.01;

				if(ix > 0 && iy > 0 && ix < in_width-1 &&  iy < in_height-1)
				{
					remapX[x+y*out_width] = ix;
					remapY[x+y*out_width] = iy;
				}
				else
				{
					remapX[x+y*out_width] = -1;
					remapY[x+y*out_width] = -1;
				}
			}
		}

		printf("Prepped Warp matrices\n");
	}
	else
	{
		printf("Not Rectifying\n");
		outputCalibration[0] = inputCalibration[0];
		outputCalibration[1] = inputCalibration[1];
		outputCalibration[2] = inputCalibration[2];
		outputCalibration[3] = inputCalibration[3];
		outputCalibration[4] = inputCalibration[4];
		out_width = in_width;
		out_height = in_height;
	}

	
	originalK_ = cv::Mat(3, 3, CV_64F, cv::Scalar(0));
	originalK_.at<double>(0, 0) = inputCalibration[0];
	originalK_.at<double>(1, 1) = inputCalibration[1];
	originalK_.at<double>(2, 2) = 1;
	originalK_.at<double>(2, 0) = inputCalibration[2];
	originalK_.at<double>(2, 1) = inputCalibration[3];

	K_ = cv::Mat(3, 3, CV_64F, cv::Scalar(0));
	K_.at<double>(0, 0) = outputCalibration[0] * out_width;
	K_.at<double>(1, 1) = outputCalibration[1] * out_height;
	K_.at<double>(2, 2) = 1;
	K_.at<double>(2, 0) = outputCalibration[2] * out_width - 0.5;
	K_.at<double>(2, 1) = outputCalibration[3] * out_height - 0.5;
}