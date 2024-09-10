void find_rects(vector<vector<Point> > &Refined_contours, vector<vector<Point2f> > &possible_rect)
{
	vector<Point2f> refined_points;
	vector<Point>  approxCurve;
	approxCurve.clear();
	possible_rect.clear();
	 for (size_t i=0; i<Refined_contours.size(); i++)
	    {
	         double eps = Refined_contours[i].size() * 0.05;
	        approxPolyDP(Refined_contours[i], approxCurve, eps, true);
	        if (approxCurve.size() != 4)
	            continue;

	        if (!isContourConvex(approxCurve))
	            continue;

	        float minDist = std::numeric_limits<float>::max();
	        for (int i = 0; i < 4; i++)
	        {
	            Point side = approxCurve[i] - approxCurve[(i+1)%4];
	            float squaredSideLength = side.dot(side);
	            minDist = std::min(minDist, squaredSideLength);
	        }
	        if (minDist < m_minContourLengthAllowed)
	            continue;
	        for(int i=0;i<4;i++)
	          refined_points.push_back(Point2f(approxCurve[i].x,approxCurve[i].y));

	        Point v1 = refined_points[1] - refined_points[0];
	        Point v2 = refined_points[2] - refined_points[0];

	        double o = (v1.x * v2.y) - (v1.y * v2.x);
	        //cout<<"Double"<<o<<endl;
	        if (o < 0.0)		 //if the third point is in the left side, then sort in anti-clockwise order
	            std::swap(refined_points[1], refined_points[3]);

	        if(Distance(refined_points[0],refined_points[3])>Distance(refined_points[0],refined_points[1]))
	         {
	               rotate(refined_points.begin(),refined_points.begin()+3,refined_points.end());
	                     //cout<<"distance"<<endl;
	         }
            //scales.push_back(Distance(refined_points[0],refined_points[3])/Distance(refined_points[0],refined_points[4]));
	        possible_rect.push_back(refined_points);
	        refined_points.clear();

	    }
}