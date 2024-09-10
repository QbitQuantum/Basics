 bool done (const Daisy& daisy, const Scope&, Treelog&) const
 { 
   return daisy.time ().month () == month
     && daisy.time ().mday () == day 
     && daisy.time ().hour () == hour; 
 }