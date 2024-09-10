  // computes FEM matrices for one 12-dof beam element
  void beamMatrix(double L, const Poly &EIx, const Poly &EIy, const Poly &EA, 
		  const Poly &GJ, const Poly &rhoA, const Poly &rhoJ,
		  const Poly &Px, const Poly &Py, const Poly &FzfromPz,
		  Matrix &K, Matrix &M, Matrix &Ndist, Matrix &Nconst, Vector &F){
    
    //using namespace boost::numeric::ublas;
    
    // initialize
    F.setZero();
    K.setZero();
    M.setZero();
    Ndist.setZero();
    Nconst.setZero();

    int i;
    
    // ------- bending (x-dir) ---------------
    const int ns = 4; // number of shape functions
    
    // define the shape functions    
    Poly f[ns] = {
		  Poly(4, 2.0, -3.0, 0.0, 1.0),
		  Poly(4, 1.0*L, -2.0*L, 1.0*L, 0.0*L),
		  Poly(4, -2.0, 3.0, 0.0, 0.0),
		  Poly(4, 1.0*L, -1.0*L, 0.0*L, 0.0*L)
    };
    
    Poly fp[ns];
    Poly fpp[ns];
    
    for (i = 0; i < ns; i++) {
      fp[i] = f[i].differentiate();
      fpp[i] = fp[i].differentiate();
    }
    
    
    // stiffness matrix
    Matrix KbendX(ns, ns);
    matrixAssembly(EIx, ns, fpp, 1.0/pow(L,3), KbendX);
   
    // inertia matrix
    Matrix Mbend(ns, ns);
    matrixAssembly(rhoA, ns, f, L, Mbend);
    
    // incremental stiffness matrix from distributed loads
    Matrix Nbend_dist(ns, ns);
    matrixAssembly(-FzfromPz, ns, fp, 1.0/L, Nbend_dist); // compression loads positive
    
    // incremental stiffness matrix from constant loads    
    Matrix Nbend_const(ns, ns);
    Poly one(1, 1.0);
    matrixAssembly(one, ns, fp, 1.0/L, Nbend_const);

    // distributed applied loads    
    Vector FbendX(ns);
    vectorAssembly(Px, ns, f, L, FbendX);
    
    // put into global matrix
    std::vector<int> idx = {0, 1, 6, 7};
    //idx(0) = 0; idx(1) = 1; idx(2) = 6; idx(3) = 7;

    for (int ii=0; ii<ns; ii++) {
      F(idx[ii]) = FbendX(ii);
      for (int jj=0; jj<ns; jj++) {
	K(idx[ii], idx[jj]) = KbendX(ii,jj);
	M(idx[ii], idx[jj]) = Mbend(ii,jj);
	Ndist(idx[ii], idx[jj]) = Nbend_dist(ii,jj);
	Nconst(idx[ii], idx[jj]) = Nbend_const(ii,jj);
      }
    }
    //project(K, idx, idx) = KbendX;
    //project(M, idx, idx) = Mbend;
    //project(Ndist, idx, idx) = Nbend_dist;
    //project(Nconst, idx, idx) = Nbend_const;
    //project(F, idx) = FbendX;
    
    
    // ---------- bending (y-dir) ---------------
    
    // stiffness matrix
    Matrix KbendY(ns, ns);
    matrixAssembly(EIy, ns, fpp, 1.0/pow(L,3), KbendY);

    
    // distributed applied loads
    Vector FbendY(ns);
    vectorAssembly(Py, ns, f, L, FbendY);

    // put into global matrix (mass and incremental stiffness are same in x an y)
    idx = {2, 3, 8, 9};
    //idx(0) = 2; idx(1) = 3; idx(2) = 8; idx(3) = 9;
    
    for (int ii=0; ii<ns; ii++) {
      F(idx[ii]) = FbendY(ii);
      for (int jj=0; jj<ns; jj++) {
	K(idx[ii], idx[jj]) = KbendY(ii,jj);
	M(idx[ii], idx[jj]) = Mbend(ii,jj);
	Ndist(idx[ii], idx[jj]) = Nbend_dist(ii,jj);
	Nconst(idx[ii], idx[jj]) = Nbend_const(ii,jj);
      }
    }
    //project(K, idx, idx) = KbendY;
    //project(M, idx, idx) = Mbend;
    //project(Ndist, idx, idx) = Nbend_dist;
    //project(Nconst, idx, idx) = Nbend_const;
    //project(F, idx) = FbendY;
    
    
    // ----------- axial ----------------
    const int nsz = 2; // number of shape functions
    
    Poly fz[nsz] = {
		    Poly(2, -1.0, 1.0),
		    Poly(2, 1.0, 0.0)
    };
    
    // derivatives of the shape function
    Poly fzp [nsz];
    Poly fzpp [nsz];
    
    for (i = 0; i < nsz; i++) {
      fzp[i] = fz[i].differentiate();
      fzpp[i] = fzp[i].differentiate();
    }
    
    // stiffness matrix
    Matrix Kaxial(nsz, nsz);
    matrixAssembly(EA, nsz, fzp, 1.0/L, Kaxial);

    
    // inertia matrix
    Matrix Maxial(nsz, nsz);
    matrixAssembly(rhoA, nsz, fz, L, Maxial);
    
    // axial loads already given (work equivalent approach not appropriate for distributed axial loads)
    Vector Faxial(nsz);
    Faxial(0) = FzfromPz.eval(0.0);
    Faxial(1) = FzfromPz.eval(1.0);
    
    // put into global matrix
    std::vector<int> idx_z = {4, 10};
    //idx_z(0) = 4; idx_z(1) = 10;
    
    for (int ii=0; ii<nsz; ii++) {
      F(idx_z[ii]) = Faxial(ii);
      for (int jj=0; jj<nsz; jj++) {
	K(idx_z[ii], idx_z[jj]) = Kaxial(ii,jj);
	M(idx_z[ii], idx_z[jj]) = Maxial(ii,jj);
      }
    }
    //project(K, idx_z, idx_z) = Kaxial;
    //project(M, idx_z, idx_z) = Maxial;
    //project(F, idx_z) = Faxial;
    
    // --------- torsion -------------
    // same shape functions as axial
    
    // stiffness matrix
    Matrix Ktorsion(nsz, nsz);
    matrixAssembly(GJ, nsz, fzp, 1.0/L, Ktorsion);

    // inertia matrix
    Matrix Mtorsion(nsz, nsz);
    matrixAssembly(rhoJ, nsz, fz, L, Mtorsion);
    
    // put into global matrix
    idx_z = {5, 11};
    //idx_z(0) = 5; idx_z(1) = 11;
    
    for (int ii=0; ii<nsz; ii++) {
      for (int jj=0; jj<nsz; jj++) {
	K(idx_z[ii], idx_z[jj]) = Ktorsion(ii,jj);
	M(idx_z[ii], idx_z[jj]) = Mtorsion(ii,jj);
      }
    }
    //project(K, idx_z, idx_z) = Ktorsion;
    //project(M, idx_z, idx_z) = Mtorsion;
    
  }