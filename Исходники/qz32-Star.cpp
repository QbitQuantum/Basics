void MyOwnStar(int x0, int y0)
{
	double deltPiece = 2.0 / pieces, k = 0, angle = 0, x, y;
	StarPoint(angle, x, y);
	moveto(x * 100 + x0, y * 100 + y0);
	for(k += deltPiece; k <= 2; angle = k * pi, k += deltPiece)
	{
		StarPoint(angle, x, y);
		lineto(x * 100 + x0, y * 100 + y0);
	}
}