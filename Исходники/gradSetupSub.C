void Strand2dFCBlockSolver::gradSetupSub(Array3D<double>& gx)
{
  // initialize coefficient array
  gx.set(0.);


  // form quadratic sub elements
  int meshOrderL=2,nElemLocalL=meshOrder-1,nSurfElemL=nSurfElem*nElemLocalL;
  Array3D<int> surfElemL(nSurfElemL,meshOrderL+1,2);
  Array3D<int> elemLocalL(nElemLocalL,meshOrderL+1,2);
  if (meshOrder == 2){
    elemLocalL(0,0,0) = 0; elemLocalL(0,0,1) = 1;
    elemLocalL(0,1,0) = 1; elemLocalL(0,1,1) = 1;
    elemLocalL(0,2,0) = 2; elemLocalL(0,2,1) = 1;
  }
  else if (meshOrder == 3){
    elemLocalL(0,0,0) = 0; elemLocalL(0,0,1) = 1;
    elemLocalL(0,1,0) = 3; elemLocalL(0,1,1) = 0;
    elemLocalL(0,2,0) = 2; elemLocalL(0,2,1) = 1;
    elemLocalL(1,0,0) = 2; elemLocalL(1,0,1) = 0;
    elemLocalL(1,1,0) = 1; elemLocalL(1,1,1) = 1;
    elemLocalL(1,2,0) = 3; elemLocalL(1,2,1) = 1;
  }
  else if (meshOrder == 4){
    elemLocalL(0,0,0) = 0; elemLocalL(0,0,1) = 1;
    elemLocalL(0,1,0) = 3; elemLocalL(0,1,1) = 0;
    elemLocalL(0,2,0) = 2; elemLocalL(0,2,1) = 1;
    elemLocalL(1,0,0) = 2; elemLocalL(1,0,1) = 0;
    elemLocalL(1,1,0) = 4; elemLocalL(1,1,1) = 0;
    elemLocalL(1,2,0) = 3; elemLocalL(1,2,1) = 1;
    elemLocalL(2,0,0) = 3; elemLocalL(2,0,1) = 0;
    elemLocalL(2,1,0) = 1; elemLocalL(2,1,1) = 1;
    elemLocalL(2,2,0) = 4; elemLocalL(2,2,1) = 1;
  }
  
  int k=0;
  for (int n=0; n<nSurfElem; n++)
    for (int i=0; i<nElemLocalL; i++){
      for (int m=0; m<meshOrderL+1; m++){
	surfElemL(k,m,0) = surfElem(n,elemLocalL(i,m,0));
	surfElemL(k,m,1) = elemLocalL(i,m,1);
      }
      k++;
    }
  if (k != nSurfElemL){
    cout << "\n***Problem forming sub-elements in initialize.C***"
	 << endl;
    exit(0);
  }
 

  // Lagrange polynomial derivatives for lower order elements
  int spacing=0; // assume equally spaced points in surface elements for now
  Array1D<double> ss(meshOrderL+1);
  solutionPoints1D(meshOrderL,
		   spacing,
		   &ss(0));

  bool test=false;
  Array2D<double> lc(meshOrderL+1,meshOrderL+1);
  lagrangePoly1D(test, // coefficients to form Lagrange polynomials
		 meshOrderL,
		 &ss(0),
		 &lc(0,0));

  // ls(i,j) = (dl_j/ds)_i (a row is all Lagrange polynomials (derivatives)
  // evaluated at a single mesh point i)
  Array2D<double> lsL(meshOrderL+1,meshOrderL+1);
  lsL.set(0.);
  int km;
  for (int i=0; i<meshOrderL+1; i++) // ith mesh point
    for (int j=0; j<meshOrderL+1; j++) // jth Lagrange polynomial
      for (int k=0; k<meshOrderL+1; k++){
	km        = max(0,k-1);
	lsL(i,j) +=((double)k)*pow(ss(i),km)*lc(j,k);
      }


  // mapping terms for lower order elements
  Array3D<double> xsL(nSurfElemL,meshOrderL+1,nStrandNode);
  Array3D<double> ysL(nSurfElemL,meshOrderL+1,nStrandNode);
  Array3D<double> jacL(nSurfElemL,meshOrderL+1,nStrandNode);
  xsL.set(0.);
  ysL.set(0.);
  int ni,nm;
  double x0,y0,nx,ny;
  for (int n=0; n<nSurfElemL; n++)
    for (int i=0; i<meshOrderL+1; i++){ // ith point in the element
      ni = surfElemL(n,i,0);
      for (int m=0; m<meshOrderL+1; m++){ // mth Lagrange poly. in mapping
	nm = surfElemL(n,m,0);
	x0 = surfX(nm,0);
	y0 = surfX(nm,1);
	nx = pointingVec(nm,0);
	ny = pointingVec(nm,1);
	for (int j=0; j<nStrandNode; j++){
	  xsL(n,i,j) += lsL(i,m)*(x0+nx*strandX(j));
	  ysL(n,i,j) += lsL(i,m)*(y0+ny*strandX(j));
	}}
      for (int j=0; j<nStrandNode; j++)
	jacL(n,i,j) = xsL(n,i,j)*yn(ni,j)-ysL(n,i,j)*xn(ni,j);
    }


  // degree at each surface node
  Array1D<int> sum(nSurfNode);
  sum.set(0);
  for (int n=0; n<nSurfElemL; n++)
    for (int i=0; i<meshOrderL+1; i++)
      sum(surfElemL(n,i,0)) += surfElemL(n,i,1);


  // use elements to form gradient coefficients
  double xnj,ynj;
  Array3D<double> a(nSurfNode,nStrandNode,2);
  a.set(0.);
  for (int n=0; n<nSurfElemL; n++)
    for (int i=0; i<meshOrderL+1; i++){ //ith point in the element
      if (surfElemL(n,i,1) == 1){ //if a contributing node
	ni = surfElemL(n,i,0);
	for (int m=0; m<meshOrderL+1; m++){ //mth Lagrange poly. in mapping
	  nm = surfElemL(n,m,0);
	  for (int j=0; j<nStrandNode; j++){ //local gradient coefficients
	    xnj       = xn(ni,j)/(jacL(n,i,j)*(double)sum(ni));
	    ynj       = yn(ni,j)/(jacL(n,i,j)*(double)sum(ni));
	    a(nm,j,0) = lsL(i,m)*ynj;
	    a(nm,j,1) =-lsL(i,m)*xnj;
	  }}
	for (int m=psp2(ni); m<psp2(ni+1); m++){ //add to coefficient array
	  nm = psp1(m);
	  for (int j=0; j<nStrandNode; j++){
	    gx(m,j,0) += a(nm,j,0);
	    gx(m,j,1) += a(nm,j,1);
	  }}
	for (int m=0; m<meshOrderL+1; m++){ //reset helper array to zero
	  nm = surfElemL(n,m,0);
	  for (int j=0; j<nStrandNode; j++){
	    a(nm,j,0) = 0.;
	    a(nm,j,1) = 0.;
	  }}}}


  // clean up
  sum.deallocate();
  a.deallocate();
  surfElemL.deallocate();
  elemLocalL.deallocate();
  xsL.deallocate();
  ysL.deallocate();
  ss.deallocate();
  lc.deallocate();
  lsL.deallocate();
}