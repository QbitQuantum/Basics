/*Draws an outline of a rectangle of the given color
  with a given width and height at (r,c)
*/
void drawHollowRect(int r, int c, int width, int height, u16 color){
	int w;
	int h;
	//draw the rectangle
	for(h = 0; h < height; h++){
		for(w = 0; w < width; w++){
			//set the pixel only if the current pixel is on the outer edges
			//i.e. on the first or last row, or the first or last column
			if((h == 0 || h == (height - 1)) || (w == 0 || w == (width - 1))){
				setPixel(h + r, w + c, color);
			}
		}
	}
}