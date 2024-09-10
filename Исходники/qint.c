long double
__qint(double  uhi,double  ulo )
{
ldquad	result;

#include "msg.h"

	if ( uhi != uhi )
	{
		result.q.hi = uhi;
		result.q.lo = ulo;

		return ( result.ld );
	}

	if ( uhi >= 0.0 )
	{
		if ( uhi < twop52.d )
		{
			/* binary point occurs in uhi; truncate uhi to an integer
			*/

			result.q.hi = __trunc(uhi);

			result.q.lo = 0.0;

			if ( result.q.hi < uhi )
				return ( result.ld );

			/* must adjust result by one if ulo < 0.0 */

			if ( ulo < 0.0 )
			{
				result.q.hi -= 1.0;

				return ( result.ld );
			}

			return ( result.ld );
		}
		else if ( fabs(ulo) < twop52.d )
		{
			/* binary point occurs in ulo; truncate ulo to an integer
			*/

			result.q.hi = uhi;

			result.q.lo = __trunc(ulo);

			if ( result.q.lo > ulo )
			{
				result.q.lo -= 1.0;
			}

			return ( result.ld );
		}

		/* arg is an integer */

		result.q.hi = uhi;
		result.q.lo = ulo;

		return ( result.ld );
	}
	else
	{
		if ( fabs(uhi) < twop52.d )
		{
			/* binary point occurs in uhi; truncate uhi to an integer
			*/

			result.q.hi = __trunc(uhi);

			result.q.lo = 0.0;

			if ( result.q.hi > uhi )
				return ( result.ld );

			/* must adjust result by one if ulo > 0.0 */

			if ( ulo > 0.0 )
			{
				result.q.hi += 1.0;

				return ( result.ld );
			}

			return ( result.ld );
		}
		else if ( fabs(ulo) < twop52.d )
		{
			/* binary point occurs in ulo; truncate ulo to an integer
			*/

			result.q.hi = uhi;

			result.q.lo = __trunc(ulo);

			if ( result.q.lo < ulo )
			{
				result.q.lo += 1.0;
			}

			return ( result.ld );
		}

		/* arg is an integer */

		result.q.hi = uhi;
		result.q.lo = ulo;

		return ( result.ld );
	}

}