/*
*逆矩阵
*/
MatrixXd inverseS(MatrixXd & m1)
{
	if(m1.rows()==m1.cols())
	{
		try
		{
			MatrixXd m=m1.inverse();
			return m;
		}catch(std::exception e)
		{
			MatrixXd m(1,1);
			m(0,0)=-1;
			return m;
		}
	}else
	{
		MatrixXd m(1,1);
		m(0,0)=-1;
		return m;
	}
}