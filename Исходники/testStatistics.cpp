/**
 * Example of a test. To be completed.
 *
 */
bool testStatistics()
{
  unsigned int nbok = 0;
  unsigned int nb = 3;
  
  trace.beginBlock ( "Testing Statistics ..." );

  Statistic<double> stat;
  
  for(unsigned int k=0; k < 1000; k++)
    stat.addValue((double)k);
  
  stat.terminate();
  
  trace.info() << "Mean value = "<<stat.mean()  << std::endl;
  nbok += (stat.mean()==499.5) ? 1 : 0; 
  trace.info() << "Variance value = "<<stat.variance()<<std::endl;
  trace.info() << "Max value = "<<stat.max()<<std::endl;
  nbok += (stat.max()==999) ? 1 : 0; 
  trace.info() << "Min value = "<<stat.min()<<std::endl;
  nbok += (stat.min()==0)  ? 1 : 0; 
 
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}