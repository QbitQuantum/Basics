int main( int argc, char** argv )
{
  using namespace Z3i;
  Statistic<double> stats;
  unsigned int nbtries = ( argc > 1 ) ? atoi( argv[ 1 ] ) : 100;
  unsigned int nbpoints = ( argc > 2 ) ? atoi( argv[ 2 ] ) : 100;
  unsigned int diameter = ( argc > 3 ) ? atoi( argv[ 3 ] ) : 100;
  std::cout << "# Usage: " << argv[0] << " <nbtries> <nbpoints> <diameter>." << std::endl;
  std::cout << "# Test class COBANaivePlaneComputer. Points are randomly chosen in [-diameter,diameter]^3." << std::endl;
  std::cout << "# Integer nbtries nbpoints diameter time/plane(ms) E(comp) V(comp)" << std::endl;
  
 // Max diameter is ~20 for int32_t, ~500 for int64_t, any with BigInteger.
  trace.beginBlock ( "Testing class COBANaivePlaneComputer" );
  bool res = true 
    && checkPlanes<COBANaivePlaneComputer<Z3, DGtal::BigInteger> >( nbtries, diameter, nbpoints, stats );
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  long t = trace.endBlock();
  stats.terminate();
  std::cout << "BigInteger" << " " << stats.samples()
            << " " << nbpoints
            << " " << diameter 
            << " " << ( (double) t / (double) stats.samples() )
            << " " << stats.mean()
            << " " << stats.variance()
            << std::endl;
  return res ? 0 : 1;
}