void Conversion(BMP & imageIn, BMP & imageOut, letterData data [])
{
  
  //RGB color declaration of green and red
  /***************/
  RGBApixel red;
  red.Red = 255;
  red.Green = 0;
  red.Blue = 0;
  /**************/
  RGBApixel green;
  green.Red = 0;
  green.Green = 255;
  green.Blue = 0;
  /*************/

  // declaration of variables to count
  //amount of lines and letters in the image
  int letterCount = 0;
  int lineCount = 0;

  //Declares the height and width of image
  int width = imageIn.TellWidth();
  int height = imageIn.TellHeight();
  

  imageOut.SetSize(width, height);

  //boolean 2d-array to verify if a pixel has
  // been visited or not
  bool visited[width][height];

  //inistializes the array setting all values equal
  //to false
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      visited[j][i] = false;

  //x and y high and low values of a pixel
  float xlow = 0;
  float xhigh = width;

  float ylow = 0;
  float yhigh = height;

  // Declares a value for the top of a line an
  // bottom of a line
  int lineBottom = 0;
  int lineTop = 0;

  queue Q;

  //int numHoles = -1;

  //int pixelCount = 0;

  float ratio = 0;

  vector<int>holes;
  vector<float>AR;
  vector<float>area;
  vector<int>gPixel;
  queue GQ;

  float greenPixel;

  // Nested loops to loop over every pixel in the image
  for (int j = 0; j < height; j++){// Start for1
    for (int k = 0; k < width; k++){// Start for 2
      if (visited[k][j] == true)
	continue;
      //Checks to see if the pixel is black
      if (imageIn(k, j)->Red >= 20){
	visited[k][j] = true;
	continue;
      }
      greenPixel = 0;  
      letterCount++;

      float q1 = 0;
      float q2 = 0;
      float q3 = 0;
      float q4 = 0;


      xlow = k;
      ylow = j;
      xhigh = k;
      yhigh = j;

      Q.insert(new point(k, j));

      int currentTop = ylow;
      int currentBottom = yhigh;

      visited[k][j] = true;

      //data[letterCount].area = (xhigh - xlow) * (yhigh - ylow);

      while(!Q.isEmpty()){// Start while
	//gets point value of a pixel
	greenPixel++;
	point p = Q.del();
	int x = p.getx();
	int y = p.gety();
	//cout << x << ' ' << y << endl;
	int w = ((xhigh - xlow) / 2) + xlow;
	int h = ((yhigh - ylow) / 2) + xlow;
	//cout << w << ' ' << h << endl;
	if ( x <= w && x >= xlow ){
	  if ( y <= h && y >= ylow )
	    q1++;
	  if ( y >= h && y <= yhigh )
	    q3++;
	}
	if ( x >= w && x <= xhigh ){
	  if ( y <= h && y >= ylow )
	    q2++;
	  if ( y >= h && y <= yhigh )
	    q4++;
	}


	GQ.insert(new point(x, y));

	imageOut.SetPixel(x, y, green);

	if(x < xlow)
	  xlow = x;
	if(y < ylow)
	  ylow = y;
	if (x > xhigh)
	  xhigh = x;
	if (y > yhigh)
	  yhigh = y;

	//finds the neighbors of a pixel by
	// finding the pixels around it that are black
	for (int l = y - 1; l <= y + 1; l++){// Start for3
	  for (int m = x - 1; m <= x + 1; m++){// Start for 4
	    if (visited[m][l] == false){// Start if1
	      visited [m][l] = true;
	      if (imageIn(m, l)->Red == 0)
		Q.insert(new point(m, l));
	    }// End if1
	  }// End for4
	}// End for 3
      }// End whil

      //draws bounding boxes around each letter
      for (int i = xlow - 1; i <= xhigh + 1; i++){
	imageOut.SetPixel(i, ylow - 1, red);
	imageOut.SetPixel(i, yhigh + 1, red);
      }

      for (int j = ylow - 1; j <= yhigh + 1; j++){
	imageOut.SetPixel(xlow - 1, j, red);
	imageOut.SetPixel(xhigh + 1, j, red);
      }

      //finds the number of lines in the image
      if (currentTop > lineBottom){
	lineCount++;
	lineTop = currentTop;
	lineBottom = currentBottom;
      }

      //cout << xhigh - xlow << ' ' << yhigh - ylow << endl;


      int numHoles = findPic (imageOut, xlow, ylow, xhigh - xlow, yhigh - ylow, data, letterCount);
      data[letterCount].holes = numHoles;
      data[letterCount].gPixelCount = greenPixel;

      data[letterCount].ratio = (xhigh - xlow)/(yhigh - ylow);

      data[letterCount].quad1 = q1;
      data[letterCount].quad2 = q2;
      data[letterCount].quad3 = q3;
      data[letterCount].quad4 = q4;

      data[letterCount].area = (xhigh - xlow) * (yhigh - ylow);
      cout << data[letterCount].area << endl;

      /*** for the vector *******/
      holes.push_back(numHoles);

      AR.push_back(ratio);
      gPixel.push_back(greenPixel);

      /****** Finished **********/

      //cout << data[k - k + 1].pixelCount << endl;

      //cout << data[letterCount].quad1 << ' ' << data[letterCount].quad2 << ' ' << data[letterCount].quad3 << 
      //' ' << data[letterCount].quad4 << ' ' << endl;

    }// End for2
  }// End for1

  //cout << "Letter Count: " << letterCount << endl;
  //cout << "Line Count: " << lineCount << endl;
  //cout << numHoles << endl;
  print(letterCount, data);
  // cout << greenPixel << endl;
  //percent(letterCount, area, GQ, xhigh - xlow, yhigh - ylow);
}