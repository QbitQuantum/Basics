Mat *Mat::pinv()
{
	Mat *Ans = new Mat(wid, len);
	Mat *TransJ = new Mat(wid, len);

	TransJ->Copy2(trans());
	
	Mat *temp = new Mat(wid, wid);

	temp->Copy2(dot(TransJ));

	temp->Copy2(temp->inv());

	Ans->Copy2(TransJ->dot(temp));

	delete TransJ;
	delete temp;

	
	return Ans;


}