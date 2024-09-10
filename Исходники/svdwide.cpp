// Like Y = x' * X, where X is genotypes, x is a matrix
MatrixXd SVDWideOnline::prod2(const MatrixXd& x)
{
   unsigned int actual_block_size = stop[0] - start[0] + 1;

   verbose && STDOUT << timestamp()
      << "Matrix operation " << nops << std::endl;

   dat.read_snp_block(start[0], stop[0], false, false);
   verbose && STDOUT << timestamp() << "Reading block " <<
      0 << " (" << start[0] << ", " << stop[0]
      << ")"  << std::endl;

   MatrixXd Y(x.cols(), p);
   Y.middleCols(start[0], actual_block_size) =
      x.transpose() * dat.X.leftCols(actual_block_size);

   for(unsigned int k = 1 ; k < nblocks ; k++)
   {
      verbose && STDOUT << timestamp() << "Reading block " <<
	 k << " (" << start[k] << ", " << stop[k] << ")"  << std::endl;
      actual_block_size = stop[k] - start[k] + 1;
      dat.read_snp_block(start[k], stop[k], false, false);
      //TODO: Kahan summation better here?
      Y.middleCols(start[k], actual_block_size) =
	 x.transpose() * dat.X.leftCols(actual_block_size);
   }
   nops++;
   return Y;
}