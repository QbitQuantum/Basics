// read the x and y coordinates and convert them into the internal move
// representation
void readmv(int x, int y, int *en)
{
	int ef, er;	

	ef = (int)nearbyintf(((float)x - 50) / 50.f);
	er = (int)nearbyintf(((float)y - 50) / 50.f);

	*en = ef + 10*er + 11;
}