double IIRNotch::processSample(double input){
  bool v = false;
  
  Eigen::Vector3d x_temp ( input , x(0),  x(1) );
  Eigen::Vector3d y_temp (      0, y(0),  y(1) );
  if(v)  std::cout << input << "\n";
  if(v)  std::cout << x_temp.transpose() << " x_temp\n";
  if(v)  std::cout << y_temp.transpose() << " y_temp\n";
  if(v)  std::cout << b.transpose() << " b\n";
  if(v)  std::cout << a.transpose() << " a\n";
  
  if(v){  
    Eigen::Vector3d bit =  x_temp.cross(b);
    std::cout << bit.transpose() << " bit\n";  
  }
  
  
  double output =  (x_temp.dot(b)) -  (y_temp.dot(a));
  double temp_x = x(0);
  x << input , temp_x  ;
  double temp_y = y(0);
  y <<  output, temp_y ; 
  
  if(v)  std::cout << x.transpose() << " x\n";
  if(v)  std::cout << y.transpose() << " y\n\n";
  
  return output;
}