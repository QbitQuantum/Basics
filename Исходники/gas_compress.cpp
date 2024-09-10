int physics_run(real t)
{
  //output.write("Running %e\n", t);
  // Run communications
  comms.run();

  // Density
  
  F_N = -V_dot_Grad(V, N) - N*Div(V);
 
  //output.write("N ");
 
  // Velocity 
  
  F_V = -V_dot_Grad(V, V) - Grad(P)/N + g;

  if(sub_initial) {
    F_V += Grad(P0)/N0 - g;
  }

  //output.write("V ");

  if(include_viscosity) {
    // Add viscosity
    
    F_V.y += nu*Laplacian(V.y);
    F_V.z += nu*Laplacian(V.z);

    //output.write("nu ");
  }
  
  // Pressure

  F_P = -V_dot_Grad(V, P) - gamma_ratio*P*Div(V);

  //output.write("P\n");

  // Set boundary conditions
  apply_boundary(F_N, "density");
  apply_boundary(F_P, "pressure");
  F_V.to_contravariant();
  apply_boundary(F_V, "v");

  //output.write("finished\n");

  return 0;
}