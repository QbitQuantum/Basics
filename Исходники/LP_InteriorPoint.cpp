bool LP_InteriorPoint::Set(const LinearProgram& lp)
{
  Matrix Aeq;
  Vector beq;
  int neq=0,nineq=0;
  for(int i=0;i<lp.A.m;i++) {
    if(lp.ConstraintType(i) == LinearProgram::Fixed) neq++;
    else {
      if(lp.HasLowerBound(lp.ConstraintType(i))) nineq++;
      if(lp.HasUpperBound(lp.ConstraintType(i))) nineq++;
    }
  }
  for(int i=0;i<lp.A.n;i++) {
    if(lp.VariableType(i) == LinearProgram::Fixed) neq++;
    else {
      if(lp.HasLowerBound(lp.VariableType(i))) nineq++;
      if(lp.HasUpperBound(lp.VariableType(i))) nineq++;
    }
  }

  if(neq == 0) {
    x0.clear();
    N.clear();
    ((LinearProgram&)solver) = lp;
    //solver.minimize is ignored by the solver
    if(!solver.minimize) solver.c.inplaceNegative();
    return true;
  }

  Aeq.resize(neq,lp.A.n);
  beq.resize(neq);
  neq=0;
  for(int i=0;i<lp.A.m;i++) {
    if(lp.ConstraintType(i)==LinearProgram::Fixed)
    {
      Vector Ai;
      lp.A.getRowRef(i,Ai);
      Aeq.copyRow(neq,Ai);
      beq(neq) = lp.p(i);
      neq++;
    }
  }
  for (int i=0;i<lp.A.n;i++) {
    if(lp.VariableType(i)==LinearProgram::Fixed)
    {
      Vector Aeqi;
      Aeq.getRowRef(i,Aeqi);
      Aeqi.setZero();
      Aeqi(i) = One;
      beq(neq) = lp.l(i);
      neq++;
    }
  }

  SVDecomposition<Real> svd;
  if(!svd.set(Aeq)) {
    if(solver.verbose>=1) cout<<"LP_InteriorPoint: Couldn't set SVD of equality constraints!!!"<<endl;
    return false;
  }
  svd.backSub(beq,x0);
  svd.getNullspace(N);

  //Set the solver to use the new variable y
  if(N.n == 0) {  //overconstrained!
    cout<<"Overconstrained!"<<endl;
    solver.Resize(0,0);
    return true;
  }

  if(nineq == 0) {
    cout<<"No inequalities!"<<endl;
    abort();
    return true;
  }

  if(solver.verbose >= 1) cout<<"LP_InteriorPoint: Decomposed the problem from "<<lp.A.n<<" to "<<N.n<<" variables"<<endl;

  solver.Resize(nineq,N.n);
  //objective
  foffset = dot(lp.c,x0);
  //c is such that c'*y = lp.c'*N*y => c = N'*lp.c
  N.mulTranspose(lp.c,solver.c);
  solver.minimize = lp.minimize;
  if(!solver.minimize) solver.c.inplaceNegative();


  //inequality constraints
  //q <= Aineq*x <= p
  //q <= Aineq*x0 + Aineq*N*y <= p
  //q - Aineq*x0 <= Aineq*N*y <= p-Aineq*x0
  //==> -Aineq*N*y <= -q + Aineq*x0
  nineq=0;
  for(int i=0;i<lp.A.m;i++) {
    if(lp.ConstraintType(i)==LinearProgram::Fixed) continue;
    if(lp.HasUpperBound(lp.ConstraintType(i))) {
      Vector Ai,sAi;
      lp.A.getRowRef(i,Ai);
      solver.A.getRowRef(nineq,sAi);
      N.mulTranspose(Ai,sAi);
      solver.p(nineq) = lp.p(i) - dot(Ai,x0);
      nineq++;
    }
    if(lp.HasLowerBound(lp.ConstraintType(i))) {
      Vector Ai,sAi;
      lp.A.getRowRef(i,Ai);
      solver.A.getRowRef(nineq,sAi);
      N.mulTranspose(Ai,sAi);
      sAi.inplaceNegative();
      solver.p(nineq) = dot(Ai,x0) - lp.q(i);
      nineq++;
    }
  }

  //transform bounds to inequality constraints
  for(int i=0;i<lp.u.n;i++) {
    if(lp.VariableType(i)==LinearProgram::Fixed) continue;
    if(lp.HasLowerBound(lp.VariableType(i))) {
      //-xi < -li
      //-ei'*N*y <= -li+ei'*x0
      Vector Ni,sAi;
      N.getRowRef(i,Ni);
      solver.A.getRowRef(nineq,sAi);
      sAi.setNegative(Ni);
      solver.p(nineq) = -lp.l(i) + x0(i);
      nineq++;
    }
    if(lp.HasUpperBound(lp.VariableType(i))) {
      //xi < ui
      //ei'*N*y <= ui-ei'*x0
      Vector Ni,sAi;
      N.getRowRef(i,Ni);
      solver.A.getRowRef(nineq,sAi);
      sAi.copy(Ni);
      solver.p(nineq) = lp.u(i) - x0(i);
      nineq++;
    }
  }
  Assert(solver.IsValid());
  return true;
}