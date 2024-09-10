void initThread()
{
    int numInit = 10;
    double noise_factor = 0.0;

    vector<Vector3d> vertices;
    vector<double> angles;

    Vector3d start_pt(18, -50, 125);

    vertices.push_back(start_pt);
    angles.push_back(0.0);
  //push back unitx so first tangent matches start_frame
    vertices.push_back(start_pt + Vector3d::UnitX()*_rest_length);
    angles.push_back(0.0);

    Vector3d direction;
    direction(0) = 1.0;
    direction(1) = 0.0;
    direction(2) = -1.0;
    direction.normalize();
    for (int i=0; i < numInit; i++)
    {
        Vector3d noise( ((double)(rand()%10000)) / 10000.0, ((double)(rand()%10000)) / 10000.0, ((double)(rand()%10000)) / 10000.0);
        noise *= noise_factor;
        Vector3d next_Vec = vertices.back()+(direction+noise).normalized()*_rest_length;
        vertices.push_back(next_Vec);
        angles.push_back(0.0);

    //std::cout << positions[i] << std::endl << std::endl;
    }



  //change direction
    direction(0) = 1.0;
    direction(1) = 0.0;
    direction(2) = 1.0;
    direction.normalize();

    for (int i=0; i < numInit; i++)
    {
        Vector3d noise( ((double)(rand()%10000)) / 10000.0, ((double)(rand()%10000)) / 10000.0, ((double)(rand()%10000)) / 10000.0);
        noise *= noise_factor;
        Vector3d next_Vec = vertices.back()+(direction+noise).normalized()*_rest_length;
        vertices.push_back(next_Vec);
        angles.push_back(0.0);

    }


  //push back unitx so last tangent matches end_frame
    vertices.push_back(vertices.back()+Vector3d::UnitX()*_rest_length);
    angles.push_back(0.0);


    angles.resize(vertices.size());

    rotations[0] = Matrix3d::Identity();
    rotations[1] = Matrix3d::Identity();

  /*
  Vector3d tan = (_thread_pieces[1].vertex() - _thread_pieces[0].vertex()).normalized();
  Vector3d toRotAxis;
  Matrix3d rot_for_frame;
  if ( (tan -Vector3d::UnitX()).norm() < 0.01 )
  {
  rot_for_frame = Matrix3d::Identity();
  }
  else 
  {
  toRotAxis = Vector3d::UnitX().cross(tan);
  double Axisnorm = toRotAxis.norm();
  double toRotAng = asin(Axisnorm);

toRotAxis /= Axisnorm;
// std::cout << "axis: " << toRotAxis << std::endl;
// std::cout << "ang: " << toRotAng << std::endl;

rot_for_frame = (Eigen::AngleAxisd(toRotAng, toRotAxis));
}
//std::cout << "rot for frame: " << rot_for_frame << std::endl;

_start_rot = rot_for_frame*Matrix3d::Identity();

//std::cout << "start frame: " << _start_rot << std::endl;

std::cout << "energy: " << calculate_energy() << std::endl;
*/


thread = new Thread(vertices, angles, rotations[0], rotations[1]);
updateThreadPoints();
}