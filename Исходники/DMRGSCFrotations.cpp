void CheMPS2::DMRGSCFrotations::rotate( const FourIndex * ORIG_VMAT, FourIndex * NEW_VMAT, DMRGSCFintegrals * ROT_TEI, const char space1, const char space2, const char space3, const char space4, DMRGSCFindices * idx, DMRGSCFunitary * umat, double * mem1, double * mem2, const int mem_size, const string filename ){

   /* Matrix elements ( 1 2 | 3 4 ) */

   assert(( space1 == 'O' ) || ( space1 == 'A' ) || ( space1 == 'V' ) || ( space1 == 'C' ) || ( space1 == 'F' ));
   assert(( space2 == 'O' ) || ( space2 == 'A' ) || ( space2 == 'V' ) || ( space2 == 'C' ) || ( space2 == 'F' ));
   assert(( space3 == 'O' ) || ( space3 == 'A' ) || ( space3 == 'V' ) || ( space3 == 'C' ) || ( space3 == 'F' ));
   assert(( space4 == 'O' ) || ( space4 == 'A' ) || ( space4 == 'V' ) || ( space4 == 'C' ) || ( space4 == 'F' ));

   const int num_irreps = idx->getNirreps();
   const bool equal12 = ( space1 == space2 );
   const bool equal34 = ( space3 == space4 );
   const bool eightfold = (( space1 == space3 ) && ( space2 == space4 ));

   for ( int irrep1 = 0; irrep1 < num_irreps; irrep1++ ){
      for ( int irrep2 = (( equal12 ) ? irrep1 : 0 ); irrep2 < num_irreps; irrep2++ ){ // irrep2 >= irrep1 if space1 == space2
         const int product_symm = Irreps::directProd( irrep1, irrep2 );
         for ( int irrep3 = (( eightfold ) ? irrep1 : 0 ); irrep3 < num_irreps; irrep3++ ){
            const int irrep4 = Irreps::directProd( product_symm, irrep3 );
            if ( irrep4 >= (( equal34 ) ? irrep3 : 0 ) ){ // irrep4 >= irrep3 if space3 == space4

               const int NEW1 = dimension( idx, irrep1, space1 );
               const int NEW2 = dimension( idx, irrep2, space2 );
               const int NEW3 = dimension( idx, irrep3, space3 );
               const int NEW4 = dimension( idx, irrep4, space4 );

               if (( NEW1 > 0 ) && ( NEW2 > 0 ) && ( NEW3 > 0 ) && ( NEW4 > 0 )){

                  const int ORIG1 = idx->getNORB( irrep1 );
                  const int ORIG2 = idx->getNORB( irrep2 );
                  const int ORIG3 = idx->getNORB( irrep3 );
                  const int ORIG4 = idx->getNORB( irrep4 );

                  double * umat1 = umat->getBlock( irrep1 ) + jump( idx, irrep1, space1 );
                  double * umat2 = umat->getBlock( irrep2 ) + jump( idx, irrep2, space2 );
                  double * umat3 = umat->getBlock( irrep3 ) + jump( idx, irrep3, space3 );
                  double * umat4 = umat->getBlock( irrep4 ) + jump( idx, irrep4, space4 );

                  const int block_size1 = mem_size / ( ORIG1 * ORIG2 ); // Floor of amount of times orig( first  ) fits in mem_size
                  const int block_size2 = mem_size / ( ORIG3 * ORIG4 ); // Floor of amount of times orig( second ) fits in mem_size
                  assert( block_size1 > 0 );
                  assert( block_size2 > 0 );

                  const bool pack_first  = (( equal12 ) && ( irrep1 == irrep2 ));
                  const bool pack_second = (( equal34 ) && ( irrep3 == irrep4 ));
                  const int   first_size = (( pack_first  ) ? (  NEW1 * (  NEW1 + 1 )) / 2 :  NEW1 * NEW2  );
                  const int  second_size = (( pack_second ) ? ( ORIG3 * ( ORIG3 + 1 )) / 2 : ORIG3 * ORIG4 );

                  const bool io_free = (( block_size1 >= second_size ) && ( block_size2 >= first_size ));
                  hid_t file_id, dspc_id, dset_id;

                  if ( io_free == false ){
                     assert( filename.compare( "edmistonruedenberg" ) != 0 );
                     open_file( &file_id, &dspc_id, &dset_id, first_size, second_size, filename );
                  }

                  // First half transformation
                  int start = 0;
                  while ( start < second_size ){
                     const int stop = min( start + block_size1, second_size );
                     const int size = stop - start;
                     fetch( mem1, ORIG_VMAT, irrep1, irrep2, irrep3, irrep4, idx, start, stop, pack_second );
                     blockwise_first(  mem1, mem2, ORIG1, ORIG2, size, umat1, NEW1, ORIG1 );
                     blockwise_second( mem2, mem1, NEW1,  ORIG2, size, umat2, NEW2, ORIG2 );
                     if ( pack_first ){
                        package_first( mem1, mem2, NEW1, first_size, size );
                        double * temp = mem1;
                        mem1 = mem2;
                        mem2 = temp;
                     }
                     if ( io_free == false ){ write_file( dspc_id, dset_id, mem1, start, size, first_size ); }
                     start += size;
                  }
                  assert( start == second_size );

                  // Do the second half transformation
                  start = 0;
                  while ( start < first_size ){
                     const int stop = min( start + block_size2, first_size );
                     const int size = stop - start;
                     if ( io_free == false ){ read_file( dspc_id, dset_id, mem1, start, size, second_size ); }
                     if ( pack_second ){
                        unpackage_second( mem1, mem2, size, ORIG3 );
                        double * temp = mem1;
                        mem1 = mem2;
                        mem2 = temp;
                     }
                     blockwise_fourth( mem1, mem2, size, ORIG3, ORIG4, umat4, NEW4, ORIG4 );
                     blockwise_third(  mem2, mem1, size, ORIG3, NEW4,  umat3, NEW3, ORIG3 );
                     write( mem1, NEW_VMAT, ROT_TEI, space1, space2, space3, space4, irrep1, irrep2, irrep3, irrep4, idx, start, stop, pack_first );
                     start += size;
                  }
                  assert( start == first_size );
                  if ( io_free == false ){ close_file( file_id, dspc_id, dset_id ); }
               }
            }
         }
      }
   }

}