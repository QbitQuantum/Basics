double dnormv (double *in, int size, int norm)
{
	double sum = 0;
	double res = 0;
	int counter = 0;

	switch (norm)
	{
		case 0:
			res = INFINITY;
			break;
		case 1:  /*Addition of all elements*/
			for (counter=0; counter < size; counter++)
			{
				sum += in[counter];
			}
			res = sum;
			break;
		case 2: /*Square root of addition of squares of all elements*/
			for (counter=0; counter < size; counter++)
			{
				sum += in[counter]*in[counter];
			}
			res = sqrt(sum);
			break;
		case 3: /*Cube root of addition of cubes of all elements*/
			for (counter=0; counter < size; counter++)
			{
				sum += pow(in[counter],3);
			}
			res = cbrt(sum);
			break;
		default : /*Nth root of addition of all elements raised to n*/
			for (counter=0; counter < size; counter++)
			{
				sum += pow(in[counter],norm);
			}
			res = pow(sum, 1./norm);
			break;
	}

	return res;
}