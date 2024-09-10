int physics_run(real t)
{
  // Run communications
  comms.run();

  msg_stack.push("F_rho");
  
  F_rho = -V_dot_Grad(v, rho) - rho*Div(v);

  msg_stack.pop(); msg_stack.push("F_p");

  F_p = -V_dot_Grad(v, p) - gamma*p*Div(v);
  
  msg_stack.pop(); msg_stack.push("F_v");
  
  F_v = -V_dot_Grad(v, v) + ((Curl(B)^B) - Grad(p))/rho;

  if(include_viscos) {
    F_v.x += viscos * Laplacian(F_v.x);
    F_v.y += viscos * Laplacian(F_v.y);
    F_v.z += viscos * Laplacian(F_v.z);
  }
  
  msg_stack.pop(); msg_stack.push("F_B");
  
  F_B = Curl(v^B);

  // boundary conditions

  apply_boundary(F_rho, "density");
  apply_boundary(F_p, "pressure");
  F_v.to_covariant();
  apply_boundary(F_v, "v");
  F_B.to_contravariant();
  apply_boundary(F_B, "B");

  msg_stack.pop(); msg_stack.push("DivB");
  
  divB = Div(B); // Just for diagnostic
  bndry_inner_zero(divB);
  bndry_sol_zero(divB);

  return 0;
}