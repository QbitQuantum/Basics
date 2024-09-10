void DomainSurface::makeTri(  Point3f *depth3d , Mat& nbuf,
	Vector4f  intrinRGB)
{
	float T = 0;
	int  near[1000];
	float nearval[1000];
	int ind = 0;

	rline = 0;


	//imshow("label", nbuf);
	//cvWaitKey(-1);

	pairlist.clear();

	vector<float>  list;
//	float *normalData_out = depth->GetData(MEMORYDEVICE_CPU);

	int h = nbuf.rows;
	int w = nbuf.cols;

	Mat buf = Mat(h, w, CV_8SC3);

	buf.setTo(Scalar(-127, -127, -127));


	int ks = 1;


	float vmin = 10000;
	float vmax = -1;
	//find the neighborhood relationship
	for ( int i = 0 ; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			int kc = -1;


			for (int kj = -ks; kj <= ks; kj++)
				for (int ki = -ks; ki <= ks; ki++)
				{
					if (i + ki < 0 || i + ki >= w)
						continue;

					if (j + kj < 0 || j + kj >= h)
						continue;


					int ikx = (kj + j)*w + (i + ki);
					Vec3b c= nbuf.at<Vec3b>(kj + j, i + ki);

					if (kc <= 0)
						kc = c.val[2];

					if (c.val[2] != kc)
					{
						addpair(kc, c.val[2]);
					}

				}


			int idx = ( j)*w + (i  );
			Point3f val = depth3d[idx] ;
			Vec3b belong = nbuf.at<Vec3b>( j, i );
			int cd = belong.val[2];

		 float error =	abs(val.dot(normaldbuf[cd]) + dbuf[cd]);

			//check the error between the belong surface and closest surface

		 int rval, bval, gval;
		 rval = bval = gval = -127;

		 if (error < vmin)
			 vmin = error;
		 if (error > vmax  && error < 100)
		 {
			 vmax = error;
		 }


		 if ( error < 3 )
			 rval =( ((int)(255 * error / 3)) % 255)-127;
		 else if (error < 10)
		 {
			 rval = 127;
			 bval = (((int)(255 * (error-3) / 10)) % 255)-127;

		 }
		 else if ( error < 50)
		 {
			 rval = 127;
			 bval = 127;
			 gval= (((int)(255 * (error-10) / 50)) % 255)-127 ;

		 }


		//	int bval = ((int)(255*error/20  ))%255;

		//291,151

		// if (i == 291 && j == 151)
		//	 cout << "here" << endl;

			buf.at<Vec3b>(j, i) = Vec3b(rval, bval, gval);


		}



	cout << "min error: " << vmin << endl;

	cout << "max error: " << vmax << endl;


	for (int i = 0; i < ndface; i++)
	{

		for each (pair<int,int> var in pairlist)
		{
			int nline = -1;
			if (var.first == i)
			nline=	findLine(i, var.second);
			else if (var.second == i)
			nline=	findLine(i, var.first);

			drawline(buf, nline, intrinRGB);

		}


	//	cv::imshow("", buf);
	//	cvWaitKey(0);

	}