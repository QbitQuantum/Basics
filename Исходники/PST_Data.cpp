double PST_Edge::closest_on_line( const CubitVector& B2, 
                                  const CubitVector& M2 )
{
  CubitVector B1 = start_coord();
  CubitVector M1 = direction();
  
  if( M1.length_squared() < RESABS_SQR )
    return 0.0;
  
  if( M2.length_squared() < RESABS_SQR )
    return closest_on_line( B2 );
  
  CubitVector cross = M2 * M1;
  if( cross.length_squared() < CUBIT_RESABS ) //parallel
    return 0.0;
  
  CubitVector N = M2 * cross;
  double      D = -( N % B2 );
  return -( N % B1 + D ) / ( N % M1 );
}