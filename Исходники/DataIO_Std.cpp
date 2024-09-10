// DataIO_Std::WriteSet2D()
int DataIO_Std::WriteSet2D( DataSet const& setIn, CpptrajFile& file ) {
  if (setIn.Ndim() != 2) {
    mprinterr("Internal Error: DataSet %s in DataFile %s has %zu dimensions, expected 2.\n",
              setIn.legend(), file.Filename().full(), setIn.Ndim());
    return 1;
  }
  DataSet_2D const& set = static_cast<DataSet_2D const&>( setIn );
  int xcol_width = 8;
  int xcol_precision = 3;
  Dimension const& Xdim = static_cast<Dimension const&>(set.Dim(0));
  Dimension const& Ydim = static_cast<Dimension const&>(set.Dim(1));
  if (Xdim.Step() == 1.0) xcol_precision = 0;
  
  DataSet::SizeArray positions(2);
  TextFormat ycoord_fmt(XcolFmt()), xcoord_fmt(XcolFmt());
  if (square2d_) {
    // Print XY values in a grid:
    // x0y0 x1y0 x2y0
    // x0y1 x1y1 x2y1
    // x0y2 x1y2 x2y2
    // If file has header, top-left value will be '#<Xlabel>-<Ylabel>',
    // followed by X coordinate values.
    if (writeHeader_) {
      ycoord_fmt.SetCoordFormat( set.Nrows(), Ydim.Min(), Ydim.Step(), xcol_width, xcol_precision );
      std::string header;
      if (Xdim.Label().empty() && Ydim.Label().empty())
        header = "#Frame";
      else
        header = "#" + Xdim.Label() + "-" + Ydim.Label();
      WriteNameToBuffer( file, header, xcol_width, true );
      xcoord_fmt.SetCoordFormat( set.Ncols(), Xdim.Min(), Xdim.Step(),
                                 set.Format().ColumnWidth(), xcol_precision );
      for (size_t ix = 0; ix < set.Ncols(); ix++)
        file.Printf( xcoord_fmt.fmt(), set.Coord(0, ix) );
      file.Printf("\n");
    }
    for (positions[1] = 0; positions[1] < set.Nrows(); positions[1]++) {
      if (writeHeader_)
        file.Printf( ycoord_fmt.fmt(), set.Coord(1, positions[1]) );
      for (positions[0] = 0; positions[0] < set.Ncols(); positions[0]++)
        set.WriteBuffer( file, positions );
      file.Printf("\n");
    }
  } else {
    // Print X Y Values
    // x y val(x,y)
    if (writeHeader_)
      file.Printf("#%s %s %s\n", Xdim.Label().c_str(), 
                  Ydim.Label().c_str(), set.legend());
    if (XcolPrecSet()) {
      xcoord_fmt = TextFormat(XcolFmt(), XcolWidth(), XcolPrec());
      ycoord_fmt = xcoord_fmt;
    } else {
      xcoord_fmt.SetCoordFormat( set.Ncols(), Xdim.Min(), Xdim.Step(), 8, 3 );
      ycoord_fmt.SetCoordFormat( set.Nrows(), Ydim.Min(), Ydim.Step(), 8, 3 );
    }
    std::string xy_fmt = xcoord_fmt.Fmt() + " " + ycoord_fmt.Fmt() + " ";
    for (positions[1] = 0; positions[1] < set.Nrows(); ++positions[1]) {
      for (positions[0] = 0; positions[0] < set.Ncols(); ++positions[0]) {
        file.Printf( xy_fmt.c_str(), set.Coord(0, positions[0]), set.Coord(1, positions[1]) );
        set.WriteBuffer( file, positions );
        file.Printf("\n");
      }
    }
  }
  return 0;
}