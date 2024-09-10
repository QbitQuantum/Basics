/*
Place a row representing a binary number on the matrix
b - value to convert to binary representation
r, c - row/col in matrix
d - digits (columns) to use for binary number
co - color value
br - brightness value
*/
void LedMatrixClass::placeBinary(int b, int r, int c, int p)
{
	int rtmp, gtmp, btmp;

	for (int i = 0; i < p; ++i) // only need 'p' LSB from number
	{
		if (b & (0x01 << i))
			setPixel(r, c + p - 1 - i);
		else
			clearPixel(r, c + p - 1 - i);
	}

	return;
}