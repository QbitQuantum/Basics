double NHitSeedFinder::fitTrack(SimpleTrack3D& track, vector<double>& chi2_hit)
{
  if(using_vertex == true)
  {
    track.hits.push_back(SimpleHit3D(0.,0., 0.,0., 0.,0., 0, 0));
  }
  
  chi2_hit.clear();
  chi2_hit.resize(track.hits.size(), 0.);
  
  MatrixXf y = MatrixXf::Zero(track.hits.size(), 1);
  for(unsigned int i=0;i<track.hits.size();i++)
  {
    y(i, 0) = ( pow(track.hits[i].x,2) + pow(track.hits[i].y,2) );
    if((using_vertex==true ) && (i == (track.hits.size() - 1))){y(i, 0) /= vertex_sigma_xy;}
    else{y(i, 0) /= layer_xy_resolution[track.hits[i].layer];}
  }
  
  MatrixXf X = MatrixXf::Zero(track.hits.size(), 3);
  for(unsigned int i=0;i<track.hits.size();i++)
  {
    X(i, 0) = track.hits[i].x;
    X(i, 1) = track.hits[i].y;
    X(i, 2) = -1.;
    if((using_vertex==true ) && (i == (track.hits.size() - 1)))
    {
      X(i, 0) /= vertex_sigma_xy;
      X(i, 1) /= vertex_sigma_xy;
      X(i, 2) /= vertex_sigma_xy;
    }
    else
    {
      X(i, 0) /= layer_xy_resolution[track.hits[i].layer];
      X(i, 1) /= layer_xy_resolution[track.hits[i].layer];
      X(i, 2) /= layer_xy_resolution[track.hits[i].layer];
    }
  }
  
  MatrixXf Xt = X.transpose();
  
  MatrixXf prod = Xt*X;
  MatrixXf inv = prod.fullPivLu().inverse();
  
  MatrixXf beta = inv*Xt*y;
  
  float cx = beta(0,0)*0.5;
  float cy = beta(1,0)*0.5;
  float r = sqrt(cx*cx + cy*cy - beta(2,0));
  
  float phi = atan2(cy, cx);
  float d = sqrt(cx*cx + cy*cy) - r;
  float k = 1./r;
  
  MatrixXf diff = y - (X*beta);
  MatrixXf chi2 = (diff.transpose())*diff;
  
  float dx = d*cos(phi);
  float dy = d*sin(phi);
  
  MatrixXf y2 = MatrixXf::Zero(track.hits.size(), 1);
  for(unsigned int i=0;i<track.hits.size();i++)
  {
    y2(i,0) = track.hits[i].z;
    if((using_vertex==true ) && (i == (track.hits.size() - 1))){y2(i, 0) /= vertex_sigma_z;}
    else{y2(i, 0) /= layer_z_resolution[track.hits[i].layer];}
  }
  
  MatrixXf X2 = MatrixXf::Zero(track.hits.size(), 2);
  for(unsigned int i=0;i<track.hits.size();i++)
  {
    float D = sqrt( pow(dx - track.hits[i].x, 2) + pow(dy - track.hits[i].y,2));
    float s = 0.0;
    
    if(0.5*k*D > 0.1)
    {
      float v = 0.5*k*D;
      if(v >= 0.999999){v = 0.999999;}
      s = 2.*asin(v)/k;
    }
    else
    {
      float temp1 = k*D*0.5;temp1*=temp1;
      float temp2 = D*0.5;
      s += 2.*temp2;
      temp2*=temp1;
      s += temp2/3.;
      temp2*=temp1;
      s += (3./20.)*temp2;
      temp2*=temp1;
      s += (5./56.)*temp2;
    }
    
    X2(i,0) = s;  
    X2(i,1) = 1.0;
    
    if((using_vertex==true ) && (i == (track.hits.size() - 1)))
    {
      X2(i, 0) /= vertex_sigma_z;
      X2(i, 1) /= vertex_sigma_z;
    }
    else
    {
      X2(i, 0) /= layer_z_resolution[track.hits[i].layer];
      X2(i, 1) /= layer_z_resolution[track.hits[i].layer];
    }
  }
  
  MatrixXf Xt2 = X2.transpose();
  MatrixXf prod2 = Xt2*X2;
  MatrixXf inv2 = prod2.fullPivLu().inverse();
  MatrixXf beta2 = inv2*Xt2*y2;
  
  MatrixXf diff2 = y2 - (X2*beta2);
  MatrixXf chi2_z = (diff2.transpose())*diff2;
  
  float z0 = beta2(1,0);
  float dzdl = beta2(0,0)/sqrt(1. + beta2(0,0)*beta2(0,0));
  
  track.phi = phi;
  track.d = d;
  track.kappa = k;
  track.dzdl = dzdl;
  track.z0 = z0;
  
  if(track.kappa!=0.)
  {
    r=1./track.kappa;
  }
  else
  {
    r=1.0e10;
  }
  
  cx = (track.d+r)*cos(track.phi);
  cy = (track.d+r)*sin(track.phi);
  
  float chi2_tot = 0.;
  for(unsigned int h=0;h<track.hits.size();h++)
  {
    float dx1 = track.hits[h].x - cx;
    float dy1 = track.hits[h].y - cy;
    
    float dx2 = track.hits[h].x + cx;
    float dy2 = track.hits[h].y + cy;
    
    float xydiff1 = sqrt(dx1*dx1 + dy1*dy1) - r;
    float xydiff2 = sqrt(dx2*dx2 + dy2*dy2) - r;
    float xydiff = xydiff2;
    if(fabs(xydiff1) < fabs(xydiff2)){ xydiff = xydiff1; }
    
    float ls_xy = layer_xy_resolution[track.hits[h].layer];
    if((using_vertex == true) && (h == (track.hits.size() - 1)))
    {
      ls_xy = vertex_sigma_xy;
    }
    
    chi2_hit[h] = 0.;
    chi2_hit[h] += xydiff*xydiff/(ls_xy*ls_xy);
    chi2_hit[h] += diff2(h,0)*diff2(h,0);
    
    chi2_tot += chi2_hit[h];
  }
  
  unsigned int deg_of_freedom = 2*track.hits.size() - 5;
  
  if(using_vertex == true)
  {
    track.hits.pop_back();
    chi2_hit.pop_back();
  }
    
  return (chi2_tot)/((double)(deg_of_freedom));
}