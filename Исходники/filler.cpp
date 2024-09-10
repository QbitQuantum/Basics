animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) 
{
	gradientColorPicker gradientFill(fadeColor1, fadeColor2, radius, x, y);

	return filler::fill<Queue>(img, x, y, gradientFill, tolerance, frameFreq);
}