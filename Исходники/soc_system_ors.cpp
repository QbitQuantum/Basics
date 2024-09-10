void soc::SocSystem_Ors::getMF(arr& M,arr& F){
  if(!WS->pseudoDynamic){
    if(WS->Qlin.N) NIY;
    ors->clearForces();
    ors->gravityToForces();
    //ors->frictionToForces(1.1);
    ors->equationOfMotion(M,F,WS->v_act);
    //M.setId();  F = .1;
    //Minv *= .2;//1e-1;
  }else{
    uint n=qDim();
    M.setId(n);
    F.resize(n); F.setZero();
  }
}