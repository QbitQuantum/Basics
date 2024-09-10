// DataIO_OpenDx::WriteSet3D()
int DataIO_OpenDx::WriteSet3D(DataSet const& setIn, CpptrajFile& outfile) const {
  if (setIn.Ndim() != 3) {
    mprinterr("Internal Error: DataSet %s in DataFile %s has %zu dimensions, expected 3.\n",
              setIn.legend(), outfile.Filename().full(), setIn.Ndim());
    return 1;
  }
  int err = 0;
  switch ( gridWriteMode_ ) {
    case BIN_CORNER:
    case BIN_CENTER: err = WriteGrid( setIn, outfile ); break;
    case WRAP:
    case EXTENDED  : err = WriteGridWrap( setIn, outfile ); break;
  }
  // Print tail
  if (err == 0) {
    // TODO: Make this an option
    //if (mode_ == CENTER)
    //  outfile.Printf("\nobject \"density (%s) [A^-3]\" class field\n",
    //                 centerMask_.MaskString());
    //else
      outfile.Printf("\nobject \"density [A^-3]\" class field\n");
  }
  return err;
}