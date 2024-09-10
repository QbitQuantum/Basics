	/*

	void point3d2Mat(const Point3d& src, Mat& dest)
	{
	dest.create(3,1,CV_64F);
	dest.at<double>(0,0)=src.x;
	dest.at<double>(1,0)=src.y;
	dest.at<double>(2,0)=src.z;
	}

	void setXYZ(Mat& in, double&x, double&y, double&z)
	{
	x=in.at<double>(0,0);
	y=in.at<double>(1,0);
	z=in.at<double>(2,0);

	//	cout<<format("set XYZ: %.04f %.04f %.04f\n",x,y,z);
	}

	void lookatBF(const Point3d& from, const Point3d& to, Mat& destR)
	{
	double x,y,z;

	Mat fromMat;
	Mat toMat;
	point3d2Mat(from,fromMat);
	point3d2Mat(to,toMat);

	Mat fromtoMat;
	add(toMat,fromMat,fromtoMat,Mat(),CV_64F);
	double ndiv = 1.0/norm(fromtoMat);
	fromtoMat*=ndiv;

	setXYZ(fromtoMat,x,y,z);
	destR = Mat::eye(3,3,CV_64F);
	double yaw   =-z/abs(z)*asin(y/sqrt(y*y+z*z))/CV_PI*180.0;

	rotYaw(destR,destR,yaw);

	Mat RfromtoMat = destR*fromtoMat;

	setXYZ(RfromtoMat,x,y,z);
	double pitch =z/abs(z)*asin(x/sqrt(x*x+z*z))/CV_PI*180.0;

	rotPitch(destR,destR,pitch);
	}
	*/
	void lookat(const Point3d& from, const Point3d& to, Mat& destR)
	{
		Mat destMat = Mat(Point3d(0.0, 0.0, 1.0));
		Mat srcMat = Mat(from + to);
		srcMat = srcMat / norm(srcMat);

		Mat rotaxis = srcMat.cross(destMat);
		double angle = acos(srcMat.dot(destMat));
		//normalize cross product and multiply rotation angle
		rotaxis = rotaxis / norm(rotaxis)*angle;
		Rodrigues(rotaxis, destR);
	}