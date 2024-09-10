bet_parameters adjust_initial_mesh(const volume<float> & image, Mesh& m, const double & rad = 0., const double xpara=0.,  const double ypara=0.,  const double zpara=0.)
{
  bet_parameters bp;
  double xdim = image.xdim();
  double ydim = image.ydim();
  double zdim = image.zdim();
  double t2, t98, t;

  //computing t2 && t98
  //  cout<<"computing robust min && max begins"<<endl;

  bp.min = image.min();
  bp.max = image.max();

  t2 = image.robustmin();
  t98 = image.robustmax();
  //t2=32.;
  //t98=16121.;
  
  //  cout<<"computing robust min && max ends"<<endl;
  
  t = t2 + .1*(t98 - t2);
  bp.t98 = t98;
  bp.t2 = t2;
  bp.t = t;
  //  cout<<"t2 "<<t2<<" t98 "<<t98<<" t "<<t<<endl;
  
  //  cout<<"computing center && radius begins"<<endl;
  
  //finds the COG
  Pt center(0, 0, 0);
  double counter = 0;
  if (xpara == 0. & ypara==0. & zpara==0.)
    {
      double tmp = t - t2;
      for (int k=0; k<image.zsize(); k++)
	for (int j=0; j<image.ysize(); j++)
	  for (int i=0; i<image.xsize(); i++)
	    {
	      double c = image(i, j, k ) - t2;
	      if (c > tmp)
		{
		  c = min(c, t98 - t2);   
		  counter+=c;
		  center +=  Pt(c*i*xdim, c*j*ydim, c*k*zdim);
		}
	    }
      center=Pt(center.X/counter, center.Y/counter, center.Z/counter);
      //cout<<counter<<endl;
      //  cout<<"cog "<<center.X<<" "<<center.Y<<" "<<center.Z<<endl;
    }
  else center=Pt(xpara, ypara, zpara);
  
  bp.cog = center;

  if (rad == 0.)
    {
      double radius=0;
      counter=0;
      double scale=xdim*ydim*zdim;
      for (int k=0; k<image.zsize(); k++)
	for (int j=0; j<image.ysize(); j++)
	  for (int i=0; i<image.xsize(); i++)
	    {
	      double c = image(i, j, k);
	      if (c > t)
		{
		  counter+=1;
		}
	    }
      radius = pow (.75 * counter*scale/M_PI, 1.0/3.0);
      //      cout<<radius<<endl;
      bp.radius = radius;
    } 
  else (bp.radius = rad);

  m.translation(center.X, center.Y, center.Z);
  m.rescale (bp.radius/2, center);

  //  cout<<"computing center && radius ends"<<endl;

  //computing tm
  //  cout<<"computing tm begins"<<endl;
  vector<double> vm;
  for (int k=0; k<image.zsize(); k++)
    for (int j=0; j<image.ysize(); j++)
      for (int i=0; i<image.xsize(); i++)
	{
	  double d = image.value(i, j, k);
	  Pt p(i*xdim, j*ydim, k*zdim);
	  if (d > t2 && d < t98 && ((p - center)|(p - center)) < bp.radius * bp.radius)
	    vm.push_back(d);
	}

  int med = (int) floor(vm.size()/2.);
  //  cout<<"before sort"<<endl;
  nth_element(vm.begin(), vm.begin() + med - 1, vm.end());
  //partial_sort(vm.begin(), vm.begin() + med + 1, vm.end());
  //double tm = vm[med];
  double tm=(*max_element(vm.begin(), vm.begin() + med));
  //  cout<<"tm "<<tm<<endl;
  bp.tm = tm;
  //  cout<<"computing tm ends"<<endl;
  
  return bp;
}