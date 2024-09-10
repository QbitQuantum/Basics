// returns false if it fails
bool ImageSmith::morph(Image &source, Image &dest, KeyPoints keys, bool is_b, ofstream & o, int j)
{
	Image tempSource;
	Image tempDest  ;
	int width  = source.getWidth ();
	int height = source.getHeight();

	tempSource.setHeight(height);
	tempSource.setWidth (width );
	tempSource.setMax   (255);

	tempDest  .setHeight(height);
	tempDest  .setWidth (width );
	tempDest  .setMax   (255);
	vector <int>     result;
	result.reserve(height * width);
	tuple  <int,int> tup;
	tuple  <int,int> w_tup;

	keys.makeDiff(j);

	for(int r = 0; r < height; r++)
	{
		for(int c = 0; c < width; c++)
		{
			// if it's a keypoint add the the source pixel to the output vector
			if( keys.isKeyPoint(c, r, j))
			{
				tup = keys.getKeySource(c, r, j);

				// if's are to handle a pixel coming from outside the image
				if      (get<0>(tup) < 0 || get<0>(tup) >= width )
				{
					result.push_back(0);
				}
				else if (get<1>(tup) < 0 || get<1>(tup) >= height)
				{
					result.push_back(0);
				}
				else
					result.push_back(source.getPixel(tup));
			}

			else 
			{
				w_tup = keys.getWeight(c, r, j);

				if      (get<0>(w_tup) < 0 || get<0>(w_tup) >= width )
					result.push_back(0);
				else if (get<1>(w_tup) < 0 || get<1>(w_tup) >= height)
					result.push_back(0);
				else
					result.push_back(source.getPixel(w_tup));
			}
		}
	}

	tempSource.setPix(result);
	result.clear();
	result.reserve(height * width);

	keys.makeDiffDest(j);

	for(int r = 0; r < height; r++)
	{
		for(int c = 0; c < width; c++)
		{
			if(keys.isKeyPoint(c, r, j))
			{
				tup = keys.getKeyDest(c, r, j);

				if      (get<0>(tup) < 0 || get<0>(tup) >= width )
					result.push_back(0);
				else if (get<1>(tup) < 0 || get<1>(tup) >= height)
					result.push_back(0);
				else
					result.push_back(dest.getPixel(tup));
			}

			else 
			{
				w_tup = keys.getWeight(c, r, j);
				if      (get<0>(w_tup) < 0 || get<0>(w_tup) >= width )
					result.push_back(0);
				else if (get<1>(w_tup) < 0 || get<1>(w_tup) >= height)
					result.push_back(0);
				else
					result.push_back(dest.getPixel(w_tup));
			}
		}
	}

	tempDest.setPix(result);
	result.clear();

	interpolate(tempSource, tempDest, j + 1, false, o);	

	return true;
}