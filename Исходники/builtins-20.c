void test2l(long double x, long double y)
{
  if (-tanl(x-y) != tanl(y-x))
    link_error ();

  if (-sinl(x-y) != sinl(y-x))
    link_error ();

  if (cosl(-x*y) != cosl(x*y))
    link_error ();

  if (cosl(x*-y) != cosl(x*y))
    link_error ();

  if (cosl(-x/y) != cosl(x/y))
    link_error ();

  if (cosl(x/-y) != cosl(x/y))
    link_error ();

  if (cosl(-fabsl(tanl(x/-y))) != cosl(tanl(x/y)))
    link_error ();

  if (cosl(y<10 ? -x : y) != cosl(y<10 ? x : y))
    link_error ();

  if (cosl(y<10 ? x : -y) != cosl(y<10 ? x : y))
    link_error ();

  if (cosl(y<10 ? -fabsl(x) : tanl(x<20 ? -x : -fabsl(y)))
      != cosl(y<10 ? x : tanl(x<20 ? x : y)))
    link_error ();

  if (cosl((y*=3, -x)) != cosl((y*=3,x)))
    link_error ();

  if (cosl((y*=2, -fabsl(tanl(x/-y)))) != cosl((y*=2,tanl(x/y))))
    link_error ();

  if (cosl(copysignl(x,y)) != cosl(x))
    link_error ();

  if (cosl(copysignl(-fabsl(x),y*=2)) != cosl((y*=2,x)))
    link_error ();

  if (hypotl (x, 0) != fabsl(x))
    link_error ();

  if (hypotl (0, x) != fabsl(x))
    link_error ();

  if (hypotl (x, x) != fabsl(x) * __builtin_sqrtl(2))
    link_error ();

  if (hypotl (-x, y) != hypotl (x, y))
    link_error ();

  if (hypotl (x, -y) != hypotl (x, y))
    link_error ();

  if (hypotl (-x, -y) != hypotl (x, y))
    link_error ();

  if (hypotl (fabsl(x), y) != hypotl (x, y))
    link_error ();

  if (hypotl (x, fabsl(y)) != hypotl (x, y))
    link_error ();

  if (hypotl (fabsl(x), fabsl(y)) != hypotl (x, y))
    link_error ();

  if (hypotl (-fabsl(-x), -fabsl(fabsl(fabsl(-y)))) != hypotl (x, y))
    link_error ();

  if (hypotl (-x, 0) != fabsl(x))
    link_error ();

  if (hypotl (-x, x) != fabsl(x) * __builtin_sqrtl(2))
    link_error ();

  if (hypotl (purel(x), -purel(x)) != fabsl(purel(x)) * __builtin_sqrtl(2))
    link_error ();

  if (hypotl (tanl(-x), tanl(-fabsl(y))) != hypotl (tanl(x), tanl(y)))
    link_error ();

  if (fminl (fmaxl(x,y),y) != y)
    link_error ();

  if (fminl (fmaxl(y,x),y) != y)
    link_error ();

  if (fminl (x,fmaxl(x,y)) != x)
    link_error ();
  
  if (fminl (x,fmaxl(y,x)) != x)
    link_error ();
  
  if (fmaxl (fminl(x,y),y) != y)
    link_error ();

  if (fmaxl (fminl(y,x),y) != y)
    link_error ();

  if (fmaxl (x,fminl(x,y)) != x)
    link_error ();
  
  if (fmaxl (x,fminl(y,x)) != x)
    link_error ();

  if ((__complex__ long double) x != -(__complex__ long double) (-x))
    link_error ();

  if (x+(x-y)*1i != -(-x+(y-x)*1i))
    link_error ();

  if (x+(x-y)*1i != -(-x-(x-y)*1i))
    link_error ();

  if (ccosl(tanl(x)+sinl(y)*1i) != ccosl(-tanl(-x)+-sinl(-y)*1i))
    link_error ();

  if (ccosl(tanl(x)+sinl(x-y)*1i) != ccosl(-tanl(-x)-sinl(y-x)*1i))
    link_error ();

  if (-5+x*1i != -~(5+x*1i))
    link_error ();

  if (tanl(x)+tanl(y)*1i != -~(tanl(-x)+tanl(y)*1i))
    link_error ();
}