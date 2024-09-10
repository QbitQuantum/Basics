void CreateImage(const typename TImage::Pointer & image)
{
  // This function creates a 2D image consisting of a black background,
  // a large square of a non-zero pixel value, and a single "erroneous" pixel
  // near the square.
  typename TImage::IndexType corner = {{0,0,0}};

  typename TImage::SizeType size = {{20,20,20}};

  typename TImage::RegionType region(corner, size);


  image->SetRegions(region);
  image->Allocate();
  image->FillBuffer(0);
  // Make a square
  for(int r = 4; r < 10; r++){
    for(int c = 4; c < 10; c++){
    	for(int h=4;h < 10;h++){
    		typename TImage::IndexType pixelIndex = {{r,c,h}};
    		image->SetPixel(pixelIndex, 1);
    	}
      }
    }

  //  typename TImage::IndexType pixelIndex = {{102, 102}};

//  image->SetPixel(pixelIndex, 50);
}