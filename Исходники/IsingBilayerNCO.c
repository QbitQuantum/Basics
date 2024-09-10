void GUI(void){	
  SetDefaultLineType(0);
  DefineGraphNxN_R("phi", &phi[0][0], &xdim, &ydim, NULL);
  DefineGraphNxN_R("psi", &psi[0][0], &xdim, &ydim, NULL);
  DefineGraphNxN_R("rho", &rho[0][0], &xdim, &ydim, NULL); 
  NewGraph();

  StartMenu("Ising Bilayer",1);

  SetActiveGraph(0);
  DefineGraph(contour2d_,"Visualize");

  //StartMenu("Controls",0);
  DefineInt("iterations", &iterations);
  DefineInt("repeat", &repeat);
  //DefineInt("stabilize", &stabilize);
  DefineDouble("phi_init", &r_zero[0]);
  DefineDouble("psi_init", &r_zero[1]);
  DefineDouble("Temperature", &T);
  DefineDouble("Lambda", &lambda);
  //EndMenu();

  StartMenu("Secondary Inputs",0);
  DefineInt("xdim", &xdim);
  DefineInt("ydim", &ydim);
  EndMenu();

  DefineFunction("reinitialize",&Init);

  DefineBool("Pause",&Pause);
  DefineBool("Single Step",&singlestep);
  DefineBool("Done",&done);	
  EndMenu();
}