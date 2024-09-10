float __tgammaf_r( float x, int* sgngamf)
{
float p, q, z, nz;
int i, direction, negative;

#ifdef NANS
if( isnan(x) )
	return(x);
#endif
#ifdef INFINITIES
#ifdef NANS
if( x == INFINITYF )
	return(x);
if( x == -INFINITYF )
	return(NANF);
#else
if( !isfinite(x) )
	return(x);
#endif
#endif

*sgngamf = 1;
negative = 0;
nz = 0.0;
if( x < 0.0 )
	{
	negative = 1;
	q = -x;
	p = floorf(q);
	if( p == q )
		{
gsing:
		_SET_ERRNO(EDOM);
		mtherr( "tgammaf", SING );
#ifdef INFINITIES
		return (INFINITYF);
#else
		return (MAXNUMF);
#endif
			}
	i = p;
	if( (i & 1) == 0 )
		*sgngamf = -1;
	nz = q - p;
	if( nz > 0.5 )
		{
		p += 1.0;
		nz = q - p;
		}
	nz = q * sinf( PIF * nz );
	if( nz == 0.0 )
		{
		_SET_ERRNO(ERANGE);
		mtherr( "tgamma", OVERFLOW );
#ifdef INFINITIES
		return( *sgngamf * INFINITYF);
#else
		return( *sgngamf * MAXNUMF);
#endif
		}
	if( nz < 0 )
		nz = -nz;
	x = q;
	}
if( x >= 10.0 )
	{
	z = stirf(x);
	}
if( x < 2.0 )
	direction = 1;
else
	direction = 0;
z = 1.0;
while( x >= 3.0 )
	{
	x -= 1.0;
	z *= x;
	}
/*
while( x < 0.0 )
	{
	if( x > -1.E-4 )
		goto Small;
	z *=x;
	x += 1.0;
	}
*/
while( x < 2.0 )
	{
	if( x < 1.e-4 )
		goto Small;
	z *=x;
	x += 1.0;
	}

if( direction )
	z = 1.0/z;

if( x == 2.0 )
	return(z);

x -= 2.0;
p = z * polevlf( x, P, 7 );

gdone:

if( negative )
	{
	p = *sgngamf * PIF/(nz * p );
	}
return(p);

Small:
if( x == 0.0 )
	{
	goto gsing;
	}
else
	{
	p = z / ((1.0 + 0.5772156649015329 * x) * x);
	goto gdone;
	}
}