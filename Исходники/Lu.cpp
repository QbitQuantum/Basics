int Lu::objpose(MatrixXf P, MatrixXf Qp)
{
  int n = P.cols();
  int i;
 // move the origin to the center of P
// std::cout<<"P\n"<<P<<std::endl; 
  
  Vector3f pbar=Vector3f::Zero();
 // std::cout<<"pbar\n"<<pbar<<std::endl;
    
  for (i = 0; i<n;i++){
 // std::cout<<"Pcol\n"<<P.col(i)<<std::endl; 
      pbar=pbar+P.col(i);
   }
 //std::cout<<"pbar\n"<<pbar; 
  pbar= pbar/n;
  
 // std::cout<<"move the origin to the center of P"<<std::endl;
 //std::cout<<"P\n"<<P;
 //std::cout<<"pbar\n"<<pbar<<std::endl; 
  
  for (i = 0; i<n;i++){
     P.col(i) = P.col(i)-pbar;
  }
 
 //std::cout<<"P\n"<<P<<std::endl; 
  MatrixXf Q;

  Q=MatrixXf::Zero(3,n);
  
for (i = 0 ;i<n;i++){

  Q(0,i)=Qp(0,i);
    Q(1,i)=Qp(1,i);
      Q(2,i)=1;
}

//std::cout<<"Q\n"<<Q<<std::endl; 
//create matrix F with 0's
//Matrix3f maux;

//for (i=0;i<n;i++ ){
//  F.push_back(Matrix3f::Zero(3,3));
//}

 
RowVector3f V;
V= RowVector3f::Zero();
std::vector<Matrix3f > F;
Matrix3f F_aux;
 
 for (i = 0 ;i<n;i++){
    V[0] = Q(0,i)/Q(2,i);
    V[1] = Q(1,i)/Q(2,i);
    V[2] = Q(2,i)/Q(2,i);
   //std::cout<<"V\n"<<V<<std::endl; 
   
   Matrix3f F_aux;
   F_aux=(V.transpose()*V)/V.dot(V);
   
   //std::cout<<"F_aux\n"<<F_aux<<std::endl; 
 //  F_aux = (V*V.transpose())/(V.transpose()*V);
   F.push_back(F_aux);
}

 //compute the matrix factor required to compute t  
 Matrix3f F_sum=Matrix3f::Zero(3,3);
 
  for (i = 0 ;i< n;i++){
    F_sum=F_sum + F[i];
  }
    
  //std::cout<<"F_sum\n"<<F_sum<<std::endl;
  
  Matrix3f tFactor = (Matrix3f::Identity()-F_sum/n);
  tFactor=tFactor.inverse()/n;
  
 //std::cout<<"tfactor\n"<<tFactor<<std::endl;
  
  MatrixXf Ri_;
  MatrixXf ti_;
  MatrixXf Qi_;
  double old_err;
  
   // compute initial pose estimate
  abskernel(P, Q, F, tFactor);
  //Lu::abskernel(MatrixXf P, MatrixXf Q, std::vector<Matrix3f > F, MatrixXf G)
   
   
  Ri_=GetRi();
  ti_=Getti();
  Qi_=GetQout();
   int it = 1;
     
  old_err=Geterr();

  
  /*std::cout<<"Ri_\n"<<Ri_<<std::endl;
  std::cout<<"ti_\n"<<ti_<<std::endl;
  std::cout<<"Qi_\n"<<Qi_<<std::endl;
 std::cout<<"old_err\n"<<old_err<<std::endl;*/
  
   //std::cout<<"old_err\n"<<old_err<<std::endl;

// compute next pose estimate
   abskernel(P, Qi_, F, tFactor);
   Ri_=GetRi();
   ti_=Getti();
   Qi_=GetQout();
   
   double new_err=Geterr();

   it = it + 1; 
   
   /*std::cout<<"Ri_2\n"<<Ri_<<std::endl;
  std::cout<<"ti_2\n"<<ti_<<std::endl;
  std::cout<<"Qi_2\n"<<Qi_<<std::endl;
 std::cout<<"new_err\n"<<new_err<<std::endl;*/
  //std::cout<<"new_err\n"<<new_err<<std::endl;
 
  double val=(old_err-new_err)/old_err;
    val=sqrt(val*val);
  /* std::cout<<"val\n"<<val<<std::endl;
   std::cout<<"TOL\n"<<TOL<<std::endl;
   std::cout<<"EPSILON\n"<<EPSILON<<std::endl;
   std::cout<<"MAX_ITER\n"<<MAX_ITER<<std::endl;*/
   while ((val > TOL) && (new_err > EPSILON)  && (it<MAX_ITER)){

    old_err = new_err;
   //std::cout<<"old_err\n"<<old_err<<std::endl;
    // compute the optimal estimate of R
    abskernel(P, Qi_, F, tFactor);
    Ri_=GetRi();
    ti_=Getti();
    Qi_=GetQout();
    new_err=Geterr();
    it = it + 1;
  }
   
   
   R = Ri;
   t = ti_;
   obj_err = sqrt(new_err/n);
   
  //double img_err = sqrt(img_err/n);
   t = t - Ri*pbar;

  
   return 0;

}