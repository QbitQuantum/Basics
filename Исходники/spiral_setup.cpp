int mark_points(SysSBA &sba, Node& ci, vector< Point,Eigen::aligned_allocator<Point>  >& Wpts, vector<int> &Wptref, 
                vector<int> &Wptind)
{
  int ntot = 0;
  int npts = Wpts.size();
  double maxx = 2.0*ci.Kcam(0,2); // cx
  double maxy = 2.0*ci.Kcam(1,2); // cy

  if (camn == camp)
    {
      cout << ci.trans.transpose() << endl;
    }

  for (int i=0; i<npts; ++i)
    {
      Vector2d qi;
      Vector3d qw;
      qw = ci.w2n * Wpts[i]; // point in camera coords
      if (qw[2] > near && qw[2] < far)
        {
          ci.project2im(qi,Wpts[i]); // point in image coords
          if (qi[0] > 0.5 && qi[0] < maxx &&
              qi[1] > 0.5 && qi[1] < maxy)
            {
              if (camn == camp)
                {
                  cout << "pw: " << Wpts[i].transpose() << endl;
                  cout << "pc: " << qw.transpose() << endl << endl;
                }
              Wptref[i]++;
              if (Wptref[i] == 2)
                {
                  ++ntot;
                  Wptind[i] = sba.tracks.size(); // index into Wpts
                  //              cout << ntot << " " << sba.points.size() << endl;
                  sba.addPoint(Wpts[i]);
                }
            }
        }
    }  
  ++camn;
  return ntot;
}