int * PithExtractor::drawLine(int xOrigine, int yOrigine, float orientation_ORI, int width, int height, int *length) const
{
	float orientation = -orientation_ORI;	// orientation au sens de Fleur = - orientation_ORI
	int x, y, k1=0, k2=0;
	int dim = floor(sqrt(pow(width,2.0)+pow(height,2.0)));
	int *droite1, *droite2, *droite;
	float temp;

	droite1 = new int[dim];
	droite2 = new int[dim];
	droite = new int[dim];

	// 1er et 5e octant
	if ((orientation >= 0)  && (orientation < 1)) {		//entre 0 et 45		[0;45[
		// 1er octant
		temp = yOrigine;
		for(x=xOrigine; x<width; x++){
			 y= roundf(temp);
			 if(y>=height)
				 break;
			 droite1[k1] = y*width+x;
			 k1++;
			 temp += orientation;
		}

		//5e octant
		temp = yOrigine - orientation;
		for(x=xOrigine-1; x>=0; x--){
			y = roundf(temp);
			if(y<0)
				break;
			droite2[k2] = y*width+x;
			k2++;
			temp -= orientation;
		}
	}

	// 4e et 8e octant
	if ((orientation < 0) && (orientation > -1)) {		//entre 0 et -45	]0;-45[
		//8e octant
		temp = yOrigine;
		for(x=xOrigine; x<width; x++){
			y=roundf(temp);
			if(y<0)
				break;
			droite1[k1] = y*width+x;
			k1++;
			temp += orientation;
		}

		//4e octant
		temp = yOrigine-orientation;
		for(x=xOrigine-1; x>=0; x--){
			y = roundf(temp);
			if(y>=height)
				break;
			droite2[k2] = y*width+x;
			k2++;
			temp -= orientation;
		}
	}

	// 2e et 6e octant	corrigé
	if (orientation >= 1) {		//entre 45 et 90	[45;90]
		//2e octant
		temp = xOrigine;
		for(y=yOrigine; y<height; y++){
			x = roundf(temp);
			if(x>=width)
				break;
			droite1[k1] = y*width+x;
			k1++;
			temp += (1/orientation);
		}

		//6e octant
		temp=xOrigine-(1/orientation);
		for(y=yOrigine-1; y>=0; y--){
			x = roundf(temp);
			if(x<0)
				break;
			droite2[k2] = y*width+x;
			k2++;
			temp -= (1/orientation);
		}
	}

	// 3e et 7e octant	corrigé
	if (orientation <= -1) {	//entre -45 et -90		[-45;-90]
		//7e octant
		temp = xOrigine-(1/orientation);
		for (y=yOrigine-1; y>=0; y--) {
			x = roundf(temp);
			if(x>=width)
				break;
			droite1[k1] = y*width+x;
			k1++;
			temp -= 1/orientation;
		}
		//3e octant
		temp = xOrigine;
		for (y=yOrigine; y<height; y++) {
			x = roundf(temp);
			if(x<0)
				break;
			droite2[k2] = y*width+x;
			k2++;
			temp += 1/orientation;
		}
	}
	*length = k1 + k2;

	for (int i=0, j=k2-1; i<k2; i++, j--) {
		droite[i]=droite2[j];
	}
	for(int i=k2, j=0; i<k2+k1; i++, j++){
		droite[i]=droite1[j];
	}
	delete [] droite1;
	delete [] droite2;

	return droite;

}