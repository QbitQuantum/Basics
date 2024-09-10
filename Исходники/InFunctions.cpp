void Chained_LQ(cVec& x,double &y,Vec s)
	{
	int n = x.size();
	y=0.0;
	s.setZero();
	double temp;

for (auto i=0;i<n-1;i++)
    {temp=pow(x(i),2)+pow(x(i+1),2)-1;
    if (0<temp)
        {y=y+temp;
	s.segment(i,2)=s.segment(i,2)+2*x.segment(i,2);}
    
    y=y-x(i)-x(i+1);
	s(i)=s(i)-1;
	s(i+1)=s(i+1)-1;
   // s(i:i+1)=s(i:i+1)+[-1 -1]';
	}
}