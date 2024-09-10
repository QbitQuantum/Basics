//---------------------------------------------------------------------------
//
// factors the total number of verices in alternating x, y, z, t directions
//
// given: constraints on the blocking entered as an array where
//   0 implies no constraint in that direction and some value n > 0 is a given
//   number of blocks in a given direction
//
void Blocking::FactorDims(int *given) { 

  int rem = tot_b; // unfactored remaining portion of tot_b
  int block_dim[DIY_MAX_DIM]; // current block size
  int max; // longest remaining direction (0, 1, 2)
  int i, j;

  // init
  for (i = 0; i < dim; i++) {
    if (given[i] == 0) {
      lat_size[i] = 1;
      block_dim[i] = data_size[i];
    }
    else {
      lat_size[i] = given[i];
      if (rem % given[i])

#ifdef MAC
	fprintf(stderr,"Unable to block the volume with given[%d] = %d "
		"dimension. Please provide different 'given' constraints and "
		"rerun.\n", i, given[i]);
#else
	fprintf(stderr,"Unable to block the volume with given[%d] = %d "
		"dimension. Please provide different 'given' constraints and "
		"rerun.\n", i, given[i]);
#endif

      assert(rem % given[i] == 0);
      rem /= given[i];
    }
  }

  // compute factorization of data dimensions into lattice dimensions
  while (1) {

    // find longest division direction
    max = 0;
    for(i = 1; i < dim; i++) {
      if (given[i] == 0 && block_dim[i] > block_dim[max])
	max = i;
    }

    // smallest factor remaining gets assigned to this direction
    for (j = 2; j <= rem; j++) {
      if (rem % j == 0) {
	lat_size[max] *= j;
	block_dim[max] /= j;
	rem /= j;
	break;
      }
    }

    if (rem == 1)
      break;

    if (j > rem)
      fprintf(stderr,"Unable to block the volume into %d blocks. "
	      "Please select a different number of blocks and rerun.\n", tot_b);
    assert(j <= rem);

  }

  // sanity check
  int prod_blocks = 1;
  for (i = 0; i < dim; i++)
    prod_blocks *= lat_size[i];
  assert(prod_blocks == tot_b);

  // block sizes
  for(i = 0; i < dim; i++)
    block_size[i] = (int)(roundf((float)data_size[i] / (float)lat_size[i]));

  // debug
//   fprintf(stderr, "block sizes = [ ");
//   for (i = 0; i < dim; i++)
//     fprintf(stderr, "%d ", block_size[i]);
//   fprintf(stderr, "]\n");

}