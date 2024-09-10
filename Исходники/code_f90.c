void Use_F90()
{ 
  WriteElm 	    = F90_WriteElm;
  WriteSymbol 	    = F90_WriteSymbol;  
  WriteAssign 	    = F90_WriteAssign;
  WriteComment 	    = F90_WriteComment;
  DeclareConstant   = F90_DeclareConstant;
  Declare           = F90_Declare;
  ExternDeclare     = F90_ExternDeclare;
  GlobalDeclare     = F90_GlobalDeclare;
  InitDeclare       = F90_InitDeclare;

  FunctionStart     = F90_FunctionStart;
  FunctionPrototipe = F90_FunctionPrototipe;
  FunctionBegin     = F90_FunctionBegin;
  FunctionEnd       = F90_FunctionEnd;

  OpenFile( &param_headerFile,   rootFileName, "_Parameters.f90", "Parameter Module File" );
  /*  mz_rs_20050117+ */
  OpenFile( &initFile, rootFileName, "_Initialize.f90", "Initialization File" );
  /*  mz_rs_20050117- */
  /* mz_rs_20050518+ no driver file if driver = none */
  if( strcmp( driver, "none" ) != 0 )
    OpenFile( &driverFile, rootFileName, "_Main.f90", "Main Program File" );
  /* mz_rs_20050518- */
  OpenFile( &integratorFile, rootFileName, "_Integrator.f90", 
                   "Numerical Integrator (Time-Stepping) File" );
  OpenFile( &linalgFile, rootFileName, "_LinearAlgebra.f90", 
                   "Linear Algebra Data and Routines File" );
  OpenFile( &functionFile, rootFileName, "_Function.f90", 
                   "The ODE Function of Chemical Model File" );
  OpenFile( &jacobianFile, rootFileName, "_Jacobian.f90", 
                   "The ODE Jacobian of Chemical Model File" );
  OpenFile( &rateFile, rootFileName, "_Rates.f90", 
                   "The Reaction Rates File" );
  if ( useStochastic )
    OpenFile( &stochasticFile, rootFileName, "_Stochastic.f90", 
                   "The Stochastic Chemical Model File" );
  if ( useStoicmat ) {
     OpenFile( &stoichiomFile, rootFileName, "_Stoichiom.f90", 
                   "The Stoichiometric Chemical Model File" );
     OpenFile( &sparse_stoicmFile, rootFileName, "_StoichiomSP.f90", 
                   "Sparse Stoichiometric Data Structures File" );
  }		   
  OpenFile( &utilFile, rootFileName, "_Util.f90", 
                   "Auxiliary Routines File" );
  /* OpenFile( &sparse_dataFile, rootFileName, "_Sparse.f90",
                       "Sparse Data Module File" );*/
  OpenFile( &global_dataFile, rootFileName, "_Global.f90", "Global Data Module File" );
  if ( useJacSparse ) {
     OpenFile( &sparse_jacFile, rootFileName, "_JacobianSP.f90",
         "Sparse Jacobian Data Structures File" );  
  }
  if ( useHessian ) {
     OpenFile( &hessianFile, rootFileName, "_Hessian.f90", "Hessian File" );
     OpenFile( &sparse_hessFile, rootFileName, "_HessianSP.f90",
         "Sparse Hessian Data Structures File" );
  }     
  OpenFile( &mapFile, rootFileName, ".map", 
                   "Map File with Human-Readable Information" );
  OpenFile( &monitorFile, rootFileName, "_Monitor.f90", 
                   "Utility Data Module File" );
} 