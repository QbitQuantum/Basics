void GUI(){
  DefineGraphNxN_R("rho",&rho[0][0],&Xdim,&Ydim,&rhoreq);
#ifdef DEBUG
  DefineGraphNxN_R("bb",&bb[0][0],&Xdim,&Ydim,&noreq);
  DefineGraphNxN_R("b1",&b1[0][0],&Xdim,&Ydim,&noreq);
  DefineGraphNxN_R("b3",&b3[0][0],&Xdim,&Ydim,&noreq);
  DefineGraphNxN_R("b5",&b5[0][0],&Xdim,&Ydim,&noreq);
  DefineGraphNxN_R("b6",&b6[0][0],&Xdim,&Ydim,&noreq);
#endif
  DefineGraphNxN_RxR("u",&u[0][0][0],&Xdim,&Ydim,&ureq);

  StartMenu("Lattice Boltzmann",1);
  DefineDouble("1/tau",&omega);
  DefineInt("Measurement freq.",&FrequencyMeasure);
  StartMenu("Reinitialize",0);
  DefineDouble("Amplitude",&Amp2);
  DefineDouble("Width",&Width);
  DefineFunction("reinitialize",&init);
  DefineFunction("Particle init",&initParticle);
  EndMenu();
  DefineDouble("Velocity amplitude",&Amp);
  StartMenu("Particle",0);
  DefineDouble("R",&R);
  DefineDouble("M",&M);
  DefineDouble("Ux",&Ux);
  DefineDouble("Uy",&Uy);
  DefineDouble("Cx",&Cx);
  DefineDouble("Cy",&Cy);
  DefineDouble("Mx",&Mx);
  DefineDouble("My",&My);
  EndMenu();
  DefineGraph(contour2d_,"Density&Vector plots");
  DefineInt("Repeat",&Repeat);
  DefineBool("Pause",&Pause);
  DefineBool("Single Step",&sstep);
  DefineBool("Done",&done);
  EndMenu();
}