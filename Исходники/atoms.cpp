Eigen::AngleAxisf createRandomAA()
{
  Eigen::Vector3f nn;
  float a = M_PI*(rand()%1000)/2000.f; //angle

  nn(0) = (rand()%1000)/1000.f;
  nn(1) = (rand()%1000)/1000.f;
  nn(2) = (rand()%1000)/1000.f;
  nn.normalize();

  //std::cout<<"rot angle\n"<<a<<"\n";
  //std::cout<<"rot axis\n"<<nn<<"\n";

  return Eigen::AngleAxisf(a,nn);
}