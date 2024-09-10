 function erf_x_over_x ()
     {
     if ($1 == 0)
         return mu;
     else
         return erf($1)/$1;
     }