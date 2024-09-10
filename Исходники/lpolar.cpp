/**
 * Initialize Dense Inverse Log Polar Table
 * Fill each DILP[x][y] element with N <ecc,ang,dist> values so a
 * weighted sum can be computed for reconstrucion
 */
void LPolar::initDataDILP(int ecc, int ang, int s)
{
	float base,mod,lmod,alfa,lalfa,x,y;
	float radius= (float)s/2.;
	  		
	base = exp(log(radius)/((float)ecc));  //Such that pow(base,ecc) = radius

	for(int i=0; i<s; i++)
		for(int j=0; j<s; j++)
		{
			x = i - radius;
			y = j - radius;
			//Compute mod
			mod = sqrt(x*x +y*y);
			if(mod  >= radius) mod = radius-1;
			//Compute log-mod from base using log-base conversion. Result in 0..ecc range as computed in base
			lmod = log(mod)/log(base);
			//compute angle from atan2. Result in -Pi and Pi range
			alfa = atan2(y,x);
			//take alfa to 0..ang range
			lalfa = alfa*(float)ang/(2.* M_PI) + (ang/2);
			//closest ecc to lmod is (int)lmod.
			DILP[i][j].ecc = (int)rintf(lmod);
			DILP[i][j].ang = (int)rintf(lalfa);
			
		}
		
}