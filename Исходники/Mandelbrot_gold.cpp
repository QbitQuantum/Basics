void RunMandelbrotDSGold1(uchar4 *dst, const int imageW, const int imageH, const int crunch, const double xOff, const double yOff, 
						  const double xJParam, const double yJParam, const double scale, const uchar4 colors, const int frame, 
						  const int animationFrame, const bool isJulia)
{
    for (int iy = 0; iy < imageH; iy++)
        for (int ix = 0; ix < imageW; ix++) {
		    // Get the current pixel color
 		    int pixel = imageW * iy + ix;
		    uchar4 pixelColor = dst[pixel];
		    int count = 0;
    		
		    // Search for pixels out of tolerance surrounding the current pixel
		    if (ix > 0)
			    count += CheckColors(pixelColor, dst[pixel - 1]);
		    if (ix + 1 < imageW)
			    count += CheckColors(pixelColor, dst[pixel + 1]);
		    if (iy > 0)
			    count += CheckColors(pixelColor, dst[pixel - imageW]);
		    if (iy + 1 < imageH)
			    count += CheckColors(pixelColor, dst[pixel + imageW]);
		    if (count) {
			    // Calculate the location
				const double xPos = (double)ix * scale + xOff;
				const double yPos = (double)iy * scale + yOff;
				dfloat dsx, dsy, djx, djy ;
				dsdeq(dsx, xPos);
				dsdeq(dsy, yPos);
				dsdeq(djx, xJParam) ;
				dsdeq(djy, yJParam);

			    // Calculate the Mandelbrot index for the current location
			    int m = CalcMandelbrotDS(dsx, dsy, djx, djy, crunch, isJulia);
                m = m > 0 ? crunch - m : 0;
    	        
			    // Convert the Madelbrot index into a color
			    uchar4 color;
			    if (m) {
				    m += animationFrame;
				    color.x = m * colors.x;
				    color.y = m * colors.y;
				    color.z = m * colors.z;
			    } else {
				    color.x = 0;
				    color.y = 0;
				    color.z = 0;
			    }
    			
			    // Output the pixel
			    int frame1 = frame + 1;
			    int frame2 = frame1 / 2;
			    dst[pixel].x = (pixelColor.x * frame + color.x + frame2) / frame1;
			    dst[pixel].y = (pixelColor.y * frame + color.y + frame2) / frame1;
			    dst[pixel].z = (pixelColor.z * frame + color.z + frame2) / frame1;
		    }
        }
} // RunMandelbrotDSGold1