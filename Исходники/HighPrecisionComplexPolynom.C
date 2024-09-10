//
//  Find a root of a complex polynomial by Laguerre iteration.
//
//  The polynomial is                                    Poly
//  The order is                                         Maxpow
//
//  The precision:                                       Digit
cln::cl_N HighPrecisionComplexPolynom::Lasolv(cln::cl_N* Poly, int Maxpow, cln::cl_N root, int itemax) {
   int  pow, ite;
   
   root = complex(ZERO,ZERO);
   
   cln::cl_F angl, small = As(cln::cl_F)(expt(cln::cl_float(0.1,clnDIGIT),DIGIT/2));

   cln::cl_N dif1[Maxpow], dif2[Maxpow-1];
   cln::cl_N val0, val, val1, val2, denp, denm, las1, las2, sqrv;
   //   cln::cl_N root;
    for(pow = 0; pow < Maxpow; pow++)
    dif1[pow] = (pow+1)*Poly[pow+1];

    for(pow = 0; pow < Maxpow-1; pow++)
    dif2[pow] = (pow+1)*dif1[pow+1];

// The maximal allowed number of iterations is set here;
// this can be chosen larger, but 100 usually suffices

//   root = As(cln::cl_N)(complex(ZERO,ZERO));
   val0 = EvalPoly(Poly,Maxpow,root);

// Iteration

    for(ite = 0; ite < itemax; ite++)
     { 
       val = val0;
       val1 = EvalPoly(dif1,Maxpow-1,root);
       val2 = EvalPoly(dif2,Maxpow-2,root);

       sqrv = (Maxpow-1)*((Maxpow-1)*val1*val1-Maxpow*val0*val2);
       angl = HALF*cln::cl_float(phase(sqrv),clnDIGIT);
       sqrv = sqrt(abs(sqrv))*complex(cos(angl),sin(angl));
       denp = val1+sqrv;
       denm = val1-sqrv;

        if(denp == complex(ZERO,ZERO))
        root = root-Maxpow*val0/denm;

        else
         {  if(denm == complex(ZERO,ZERO))
            root = root-Maxpow*val0/denp;

            else
             { las1 = -Maxpow*val0/denp;
               las2 = -Maxpow*val0/denm;

                if(realpart(las1*conjugate(las1)) <
                   realpart(las2*conjugate(las2)))
                root = root+las1;

                else
                root = root+las2; } }

//  Look whether the root is good enough

       val0 = EvalPoly(Poly,Maxpow,root);

        if(abs(val0) == ZERO || (abs(val0) < small) && abs(val0/val) > 0.7) {
            if(LogLevel>4) { 
	       printf("Laguerre iterations: %d\n", ite);
               printf("root = %f +i* %f\n", double_approx(realpart(root)), double_approx(imagpart(root)));
               printf("value at root: %f +i* %f\n", double_approx(realpart(val0)), double_approx(imagpart(val0))); 
	    }

           break; 
	} 
    }

    if(ite >= itemax) {
      printf("Laguerre iteration did not converge\n");
      exit(5);
    }

   return root;

}