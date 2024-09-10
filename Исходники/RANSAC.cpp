 //define parameter computation
 virtual void compute_param(){
   Matrix2d M;
   Vector2d b, *point, param;
   list<Vector2d*>::iterator obs;
   
   M << 0.0, 0.0, 0.0, 0.0;
   b << 0.0, 0.0;
   
   //check if we have enough data in fit_set
   int ndata = (int)fit_set.size();
   if (ndata >= nDataMin) {
     //do linear least-squares fit
     for (obs = fit_set.begin(); obs != fit_set.end(); obs++) {
       point = *obs;
       M(0,0) += 1;
       M(0,1) += (*point)(0);
       M(1,0) += (*point)(0);
       M(1,1) += (*point)(0)*(*point)(0);
       b(0)   += (*point)(1);
       b(1)   += (*point)(0)*(*point)(1);
     }
     //calculate parameters
     param = M.inverse()*b;
     intercept = param(0);
     slope     = param(1);
   }
 };