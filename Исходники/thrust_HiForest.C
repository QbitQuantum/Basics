//plane class constructor
Plane::Plane(TVector3 nT){
  
  //Use TVector3 to find an orthogonal vector and a second vector orthogonal to the first and nT
  v1 = nT.Orthogonal();  v2 = nT.Cross(v1);

  //Normalize, checking for 0 length axes
  if ((v1(0) == 0) && (v1(1) == 0) && (v1(2) == 0)){  v1(0) = 0;    v1(1) = 0;    v1(2) = 0; }
  else { mag1 = v1.Mag();   v1(0) = v1(0)/mag1;    v1(1) = v1(1)/mag1;    v1(2) = v1(2)/mag1; } 
  if ((v2(0) == 0) && (v2(1) == 0) && (v2(2) == 0)){  v2(0) = 0;    v2(1) = 0;    v2(2) = 0; } 
  else { mag2 = v2.Mag();   v2(0) = v2(0)/mag2;    v2(1) = v2(1)/mag2;    v2(2) = v2(2)/mag2; }
}//end plane constructor