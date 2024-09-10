 static inline A digamma_imp_1_2(A x, double)
 {
 //
 // Now the approximation, we use the form:
 //
 // digamma(x) = (x - root) * (Y + R(x-1))
 //
 // Where root is the location of the positive root of digamma,
 // Y is a constant, and R is optimised for low nt2::absolute error
 // compared to Y.
 //
 // Maximum Deviation Found:              3.388e-010
 // At float precision, max error found:  2.008725e-008
 //
 typedef typename meta::scalar_of<A>::type sA; 
 static const A Y = splat<A>(0.99558162689208984);
 
 static const A root1 = splat<A>(1569415565.0 / 1073741824uL);
 static const A root2 = splat<A>((381566830.0 / 1073741824uL) / 1073741824uL);
 static const A root3 = splat<A>(double(0.9016312093258695918615325266959189453125e-19L));
 
 static const boost::array<sA, 6> P = {{    
     sA(0.25479851061131551L),
     sA(-0.32555031186804491L),
     sA(-0.65031853770896507L),
     sA(-0.28919126444774784L),
     sA(-0.045251321448739056L),
     sA(-0.0020713321167745952L)
   }};
 static const  boost::array<sA, 7> Q = {{
     sA(1L),
     sA(2.0767117023730469L),
     sA(1.4606242909763515L),
     sA(0.43593529692665969L),
     sA(0.054151797245674225L),
     sA(0.0021284987017821144L),
     sA(-0.55789841321675513e-6L)
   }};
   A g = x - root1;
   g -= root2;
   g -= root3; 
   x-= One<A>(); 
   A r = eval_poly<6>(x, P)/eval_poly<7>(x, Q);
   A result = fma(g, Y, g * r);
   return result;
 }