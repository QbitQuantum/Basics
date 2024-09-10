GLThread::GLThread() {
/*
	vector<Vector3d> directions;
	directions.push_back(Vector3d::UnitX());
	Vector3d next;
	
	next << 1.0 , 0.0 , -1.0;
	directions.push_back(next.normalized());

	next << 1.0 , 0.0 , 0.0;
	directions.push_back(next.normalized());


	next << 1.0 , 0.0 , 1.0;
	directions.push_back(next.normalized());
	
	next << 1.0 , -1.0 , 0.0;
	directions.push_back(next.normalized());


	next << 1.0 , 0.0 , 0.0;
	directions.push_back(next.normalized());
	

	next << 1.0 , 1.0 , 0.0;
	directions.push_back(next.normalized());


	directions.push_back(Vector3d::UnitX());

  vector<Vector3d> vertices;
  vector<double> angles;

	vertices.push_back(Vector3d::Zero());
	angles.push_back(0);
	for (int i=0; i < directions.size(); i++)
	{
		vertices.push_back(vertices.back()+_rest_length*directions[i]);
		angles.push_back(0);
	}
	*/

	
  int numInit = 3;
  double noise_factor = 0.0;

  vector<Vector3d> vertices;
  vector<double> angles;

  vertices.push_back(Vector3d::Zero());
  angles.push_back(0.0);
  //push back unitx so first tangent matches start_frame
  vertices.push_back(Vector3d::UnitX()*DEFAULT_REST_LENGTH);
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
      Vector3d next_Vec = vertices.back()+(direction+noise).normalized()*DEFAULT_REST_LENGTH;
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
      Vector3d next_Vec = vertices.back()+(direction+noise).normalized()*DEFAULT_REST_LENGTH;
      vertices.push_back(next_Vec);
      angles.push_back(0.0);

    }

  //push back unitx so last tangent matches end_frame
  vertices.push_back(vertices.back()+Vector3d::UnitX()*DEFAULT_REST_LENGTH);
  angles.push_back(0.0);


  angles.resize(vertices.size());

	

  rotations[0] = Matrix3d::Identity();
  rotations[1] = Matrix3d::Identity();


  _thread = new Thread(vertices, angles, rotations[0], rotations[1]);

#ifdef ISOTROPIC
  to_set_bend = _thread->get_bend_coeff();
#else
  to_set_B = _thread->get_bend_matrix();
#endif
  to_set_twist = _thread->get_twist_coeff();
  to_set_grav = _thread->get_grav_coeff();


#ifdef ISOTROPIC
    _thread->set_coeffs_normalized(to_set_bend, to_set_twist, to_set_grav);
#else
    _thread->set_coeffs_normalized(to_set_B, to_set_twist, to_set_grav);
#endif
	_thread->minimize_energy();

  InitContour();
}