 void run() { 
  triqs::mc_tools::random_generator RNG("mt19937", 23432);
  for (size_t i =0; i< 100; ++i) { 
   std::cerr<<" ------------------------------------------------"<<std::endl;
   std::cerr <<" i = "<< i << " size = "<< D.size() << std::endl; 
   // choose a move
   size_t s = D.size();
   size_t i0,j0,i1,j1;
   det_old = D.determinant();
   detratio=1;
   double x,y,x1,y1; 
   bool do_something = true;

   switch(RNG(( i>10 ? 4 : 1))) {
    case 0 :
     std::cerr  << " insert1" << std::endl;
     x = RNG(10.0), y = RNG(10.0);
     std::cerr  << " x,y = "<< x << "  "<< y << std::endl; 
     detratio = D.try_insert(RNG(s),RNG(s), x,y); 
     break;
    case 1 : 
     std::cerr  << " remove1" << std::endl;
     if (s>0) detratio = D.try_remove(RNG(s),RNG(s));
     break;
    case 2:
     std::cerr  << " Insert2" << std::endl;
     x = RNG(10.0); x1 = RNG(10.0); 
     y = RNG(10.0); y1 = RNG(10.0); 
     i0 = RNG(s); i1 = RNG(s+1);
     j0 = RNG(s); j1 = RNG(s+1);
     if ((i0 !=i1)&& (j0!=j1))  
     {
      detratio = D.try_insert2(i0,i1,j0,j1, x,x1,y,y1);
     }
     else do_something = false;

     break;
    case 3:
     std::cerr  << " Remove2" << std::endl;
     if (D.size()>=2) {
      i0 = RNG(s); i1 = RNG(s);
      j0 = RNG(s); j1 = RNG(s);
      if ((i0 !=i1)&& (j0!=j1))  {
       detratio = D.try_remove2(i0,i1,j0,j1);
      }
      else do_something = false;
     }
     break;
    default :
     TRIQS_RUNTIME_ERROR <<" TEST INTERNAL ERROR" ;
   };

   if (do_something) { 
    if (std::abs(detratio*det_old)> PRECISION)  {
     D.complete_operation();
     if (D.size() >0) check();
    }
    else { std::cerr  << " reject  since new det is = " << std::abs(detratio*det_old)<<std::endl;}
   }
  }
 }