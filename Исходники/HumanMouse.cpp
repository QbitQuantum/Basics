extern "C" _declspec(dllexport) void __cdecl BrakeWindMouse( float xs, float ys, float xe, float ye, float gravity, float wind, float minWait, float maxWait, float targetArea )
{
  float veloX = 0.0, veloY = 0.0, windX = 0.0, windY = 0.0, veloMag = 0.0, dist = 0.0, randomDist = 0.0;
  int lastX = 0, lastY = 0, MSP = 0, W = 0, maxStep = 0, D = 0, TDist = 0;
  float sqrt2 = 0.0, sqrt3 = 0.0, sqrt5 = 0.0, PDist = 0.0;
  veloX = 0;
  veloY = 0;
  windX = 0;
  windY = 0;
  MSP = MouseSpeed;
  sqrt2 = sqrt( 2 );
  sqrt3 = sqrt( 3 );
  sqrt5 = sqrt( 5 );
  srand(time(NULL));
  TDist = Distance( rnd( xs ), rnd( ys ), rnd( xe ), rnd( ye ) );
  if ( TDist < 1 )
    TDist = 1;
  do
  {
    dist = hypot( xs - xe, ys - ye );
    wind = Min( wind, dist );
    if ( dist < 1 )
      dist = 1;
    PDist = ( dist / TDist );
    if ( PDist < 0.01 )
      PDist = 0.01;

     /*
       These constants seem smooth to me, but
       feel free to modify these settings however
       you wish.
     */
    if ( PDist >= 0.15 )                    //15% (or higher) dist to destination
    {
      D = rnd( rnd( ( rnd( dist ) * 0.3 ) )  / 5 );
      if ( D < 20 )
        D = 20;
         //D := RandomRange(15, 25);                        {Original}
    }
    else
      if ( PDist < 0.15 )
      {
        if ( ( PDist <= 0.15 ) && ( PDist >= 0.10 ) )         //10%-15%
          D = RandomRange( 8, 13 );
        else
          if ( PDist < 0.10 )                           //< 10%
            D = RandomRange( 4, 7 );
      }
    if ( D <= rnd( dist ) )
      maxStep = D;
    else
      maxStep = rnd( dist );
    if ( dist >= targetArea )
    {
      windX =  windX  / sqrt3 +  ( rand()% rnd( wind ) * 2 + 1  - wind )  / sqrt5;
      windY = windY  / sqrt3 +  ( rand()% rnd( wind ) * 2 + 1  - wind )  / sqrt5;
    }
    else
    {
      windX =  windX  / sqrt2;
      windY =  windY  / sqrt2;
    }
    veloX = veloX + windX;
    veloY = veloY + windY;
    veloX = veloX +  gravity  * ( xe - xs ) / dist;
    veloY = veloY +  gravity  * ( ye - ys ) / dist;
    if ( hypot( veloX, veloY ) > maxStep )
    {
      randomDist =  maxStep  / 2.0 + rand()% rnd( maxStep ) / 2 ;
      veloMag = sqrt( veloX * veloX + veloY * veloY );
      veloX = (  veloX  / veloMag ) * randomDist;
      veloY = (  veloY  / veloMag ) * randomDist;
    }
    lastX = rnd( xs );
    lastY = rnd( ys );
    xs = xs + veloX;
    ys = ys + veloY;
    if ( ( lastX != rnd( xs ) ) || ( lastY != rnd( ys ) ) )
      MoveMouse( rnd( xs ), rnd( ys ) );
    W = ( rand()% rnd(  100 / MSP ) )  * 6;
    if ( W < 5 )
      W = 5;
    W = rnd( W * 1.2 );
    Sleep( W );
//    lastDist = dist;
  }
  while ( ! ( hypot( xs - xe, ys - ye ) < 1 ) );
  if ( ( rnd( xe ) != rnd( xs ) ) || ( rnd( ye ) != rnd( ys ) ) )
    MoveMouse( rnd( xe ), rnd( ye ) );
  MouseSpeed = MSP;
}