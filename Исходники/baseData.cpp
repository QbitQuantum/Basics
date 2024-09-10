xyMultimap_t baseXYData::GetDNL(bool arithMean, double *En, std::vector<double> *Evect)
{
	xyMultimap_t map;
	int i=0;
	double  E=0 //expected value
			,ysum = getYsum()
			,xmax = GetMaxX()
			,x=0,y=0;

	if(arithMean) E = getArithmeticMean();
	else if(En) E=*En;
	else if (Evect==0 ) E = ( ysum / (xmax+1) );            //default
	else if (Evect->size() != m_data.size() ) return map;   //must be same size

	Rewind();
	while( GetNextXY(x, y) )
	{
		if(!arithMean && Evect==0) y = y / E - 1;
		else if(arithMean) y -= E;
		else if(Evect) y -= (*Evect)[i++];

		if(Evect){
			y /= (*Evect)[i-1];
		} else{
			y /= E;
		}

		map.insert(pair<double, double>(x,y));

	}
	return map;
}