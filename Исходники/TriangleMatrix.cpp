void TriangleMatrix::Write2D( CpptrajFile& outfile, int xIn, int yIn ) {
  size_t x = (size_t)xIn;
  size_t y = (size_t)yIn;
  if ( xIn==yIn || xIn < 0 || yIn < 0 || x >= nrows_ || y >= nrows_ ) 
    outfile.Printf(data_format_, 0.0);
  else {
    size_t index = calcIndex(x, y);
    outfile.Printf(data_format_, elements_[index]);
  }
}