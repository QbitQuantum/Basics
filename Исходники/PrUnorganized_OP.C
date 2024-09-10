//-----------------------------------------------------------------------------
void PrUnorganized_OP::scanRawData(std::istream& is, 
				   int num_cells,
				   double noise)
//-----------------------------------------------------------------------------
{
  int numpnts;
  is >> numpnts;
  is >> nInt_;
  uv_.resize(numpnts);
  double *points = new double[3*numpnts];
  int i;
  double x,y,z;
  unsigned int seed = 1;
  srand(seed);
  double random;
  //Alter interior points by up to noise in either direction
  // thus xnew will be between x-noise and x+noise.

  for(i=0; i<nInt_; i++)
  {
    is >> x >> y >> z;
    random = static_cast<double>(rand())/RAND_MAX; // random is a number between 0 and 1
    points[3*i] = x + (2.0 * random - 1.0) * noise;
    random = static_cast<double>(rand())/RAND_MAX; // random is a number between 0 and 1
    points[3*i+1] = y + (2.0 * random - 1.0) * noise;
    random = static_cast<double>(rand())/RAND_MAX; // random is a number between 0 and 1
    points[3*i+2] = z + (2.0 * random - 1.0) * noise;
    uv_[i].x() = 0.0;
    uv_[i].y() = 0.0;
  }
  for(i=nInt_; i<numpnts; i++)
  {
    is >> x >> y >> z;
    points[3*i] = x;
    points[3*i+1] = y;
    points[3*i+2] = z;
    uv_[i].x() = 0.0;
    uv_[i].y() = 0.0;
  }
  cellstruct_.setNumCells(num_cells);
  cellstruct_.attach(numpnts,points);
  delete points;
}