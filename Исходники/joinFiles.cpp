int main( int argc, char** argv )
{
  //// User's choice
  if ( argc == 1 )
    {
      std::cout << "Usage: " << argv[0] << "<output> <inputFile1> <inputFile2> ..." << std::endl;
      std::cout << "       - computes the difference of results between the" << std::endl;
      std::cout << "         CPU version of the estimator and the GPU version" << std::endl;
      std::cout << "         GPU file : positions are between [0;size]." << std::endl;
      std::cout << "         CPU file : positions are between [0;2*size]" << std::endl;
      std::cout << "                                       or [-size;size]." << std::endl;
      std::cout << "         Error type : 1 is l_1, 2 is l_2, 3 is l_\\infty." << std::endl;
      std::cout << "Example:" << std::endl;
      std::cout << argv[ 0 ] << " file1.txt file2.txt 64 3" << std::endl;
      return 0;
    }
  std::string fileOutput = argc > 1 ? std::string( argv[ 1 ] ) : "file1.txt";
  std::string fileInput = argc > 2 ? std::string( argv[ 2 ] ) : "file2.txt";
  convertCPUtoKhalimsky predicateCPU;
  std::vector< std::pair<Position*, Curvatures*> > v_export;
  std::vector< std::pair<Position*, Value> > v_temp;
  loadFile2( fileInput, v_temp, predicateCPU );
  writeVector(v_temp, v_export, 0 );
  deleteVector2( v_temp );

  for(int i = 3; i < argc; ++i)
  {
    fileInput = std::string( argv[ i ] );
    loadFile2( fileInput, v_temp, predicateCPU );
    writeVector(v_temp, v_export, i-2);
    deleteVector2( v_temp );
  }

  writeFile( fileOutput, v_export );
  deleteVector( v_export );

  return 0;
}