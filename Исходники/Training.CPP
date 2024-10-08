void Train::warpMatrix(Size sz,
                       double yaw,
                       double pitch,
                       double roll,
                       double scale,
                       double fovy,
                       Mat &M,
                       vector<Point2f>* corners)
{
	double st=sin(deg2Rad(roll));
	double ct=cos(deg2Rad(roll));
	double sp=sin(deg2Rad(pitch));
	double cp=cos(deg2Rad(pitch));
	double sg=sin(deg2Rad(yaw));
	double cg=cos(deg2Rad(yaw));
    
	double halfFovy=fovy*0.5;
	double d=hypot(sz.width,sz.height);
	double sideLength=scale*d/cos(deg2Rad(halfFovy));
	double h=d/(2.0*sin(deg2Rad(halfFovy)));
	double n=h-(d/2.0);
	double f=h+(d/2.0);
    
    
	Mat F=Mat(4,4,CV_64FC1);
	Mat Rroll=Mat::eye(4,4,CV_64FC1);
	Mat Rpitch=Mat::eye(4,4,CV_64FC1);
	Mat Ryaw=Mat::eye(4,4,CV_64FC1);
    
	Mat T=Mat::eye(4,4,CV_64FC1);
	Mat P=Mat::zeros(4,4,CV_64FC1);
    
    
	Rroll.at<double>(0,0)=Rroll.at<double>(1,1)=ct;
	Rroll.at<double>(0,1)=-st;Rroll.at<double>(1,0)=st;
    
	Rpitch.at<double>(1,1)=Rpitch.at<double>(2,2)=cp;
	Rpitch.at<double>(1,2)=-sp;Rpitch.at<double>(2,1)=sp;
    
	Ryaw.at<double>(0,0)=Ryaw.at<double>(2,2)=cg;
	Ryaw.at<double>(0,2)=sg;Ryaw.at<double>(2,0)=sg;
    
    
	T.at<double>(2,3)=-h;
    
	P.at<double>(0,0)=P.at<double>(1,1)=1.0/tan(deg2Rad(halfFovy));
	P.at<double>(2,2)=-(f+n)/(f-n);
	P.at<double>(2,3)=-(2.0*f*n)/(f-n);
	P.at<double>(3,2)=-1.0;
    
	F=P*T*Rpitch*Rroll*Ryaw;
    
	double ptsIn [4*3];
	double ptsOut[4*3];
	double halfW=sz.width/2, halfH=sz.height/2;
	ptsIn[0]=-halfW;ptsIn[ 1]= halfH;
	ptsIn[3]= halfW;ptsIn[ 4]= halfH;
	ptsIn[6]= halfW;ptsIn[ 7]=-halfH;
	ptsIn[9]=-halfW;ptsIn[10]=-halfH;
	ptsIn[2]=ptsIn[5]=ptsIn[8]=ptsIn[11]=0;
	Mat ptsInMat(1,4,CV_64FC3,ptsIn);Mat ptsOutMat(1,4,CV_64FC3,ptsOut);
	perspectiveTransform(ptsInMat,ptsOutMat,F);
    
	Point2f ptsInPt2f[4];Point2f ptsOutPt2f[4];
	for(int i=0;i<4;i++)
	{
		Point2f ptIn(ptsIn[i*3+0],ptsIn[i*3+1]);
		Point2f ptOut(ptsOut[i*3+0],ptsOut[i*3+1]);
		ptsInPt2f[i]=ptIn+Point2f(halfW,halfH);
		ptsOutPt2f[i]=(ptOut+Point2f(1,1))*(sideLength*0.5);
	}
	M=getPerspectiveTransform(ptsInPt2f,ptsOutPt2f);
    
	if(corners!=NULL)
	{
		corners->clear();
		corners->push_back(ptsOutPt2f[0]);
		corners->push_back(ptsOutPt2f[1]);
		corners->push_back(ptsOutPt2f[2]);
		corners->push_back(ptsOutPt2f[3]);
	}
}