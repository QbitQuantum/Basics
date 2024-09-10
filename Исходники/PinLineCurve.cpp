vector<Pin*> PinLineCurve::GetLinePins( Point3 start, Point3 end )
{
	vector<Pin*> rtn;
	Vector3 v = end-start;
	int numSteps = v.getLength()/.55;
	v.normalize();
	v = .6f * v;
	Point3 c = start;
	rtn.push_back(new Pin(c));
	for (int i = 0;i<numSteps;i++)
	{
		rtn.push_back(new Pin(c+v));
		c = c+v;
	}

	/*Vector3 v2 = end-c;
	float rest = v2.getLength();

	if (rest!=0)
	{
		rtn.push_back(new Pin(c));
	}*/
	return rtn;
}