//--------------------------------------------------------------
void processPoint(const String& point, Uint32& v, Uint32& vt, Uint32& vn)
{
	Uint32 occ = point.countOccurrence('/');

	switch(occ)
	{
	case 0:
		sscanf(point.getValue(), "%u", &v);
		vt = 1;
		vn = 1;
	break;
	case 1:
		sscanf(point.getValue(), "%u/%u", &v, &vt);
		vn = 1;
	break;
	case 2:
		if(point.getChar(point.find('/')+1) == '/') // find "//" pattern
		{
			sscanf(point.getValue(), "%u//%u", &v, &vn);
			vt = 1;
		}
		else
		{
			sscanf(point.getValue(), "%u/%u/%u", &v, &vt, &vn);
		}
	break;
	default:
		fprintf(stdout, "wut?\n");
	break;
	}
}