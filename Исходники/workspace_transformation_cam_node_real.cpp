void force_feedback_pos_rate_control(void){
  
  // ****************************************************************************************************************
  // Force feedback when in rate control area
  // ****************************************************************************************************************
  
  // Variables
  Ks = MatrixXd::Zero(3,3);
  Ks(0,0) = scale[0];
  Ks(1,1) = scale[1];
  Ks(2,2) = scale[2];
 
  Eigen::Vector3d omni_force = Eigen::Vector3d::Zero();
  double R = 0.05;
  double Fmax = 3.3; // 3.3 N es la máxima força nominal
  double Kf = 60;
  double Kv = 0.5;

  // Displacement
  dm = pm_i - pm_0;
  ds = Ks * Rs.transpose() * Rm * dm;  
  
  // Omni feedback force computation
  double D = sqrt( ds(0)*ds(0) + ds(1)*ds(1) );  
  
  if (D > R)	omni_force = - Kf * (D - R) * (ds/D);
  omni_force += - Kv*vm_i; // Damping
  omni_force(2) = 0.0;     // No force in vertical axis
  omni_force = Rm.transpose() * Rs * omni_force; // To master reference frame
  
  if (omni_force(0) < -Fmax) omni_force(0) = -Fmax;
  if (omni_force(0) > Fmax)  omni_force(0) = Fmax;
  if (omni_force(1) < -Fmax) omni_force(1) = -Fmax;
  if (omni_force(1) > Fmax)  omni_force(1) = Fmax;  

  // Publish
  force.x = omni_force(0);
  force.y = omni_force(1);
  force.z = omni_force(2);
  pub_OmniForceFeedback.publish(force);
}