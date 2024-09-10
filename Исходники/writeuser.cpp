void WriteNeutralFormat (const Mesh & mesh,
			 const string & filename)
{
  cout << "write neutral, new" << endl;
  int np = mesh.GetNP();
  int ne = mesh.GetNE();
  int nse = mesh.GetNSE();
  int nseg = mesh.GetNSeg();
  int i, j;

  int inverttets = mparam.inverttets;
  int invertsurf = mparam.inverttrigs;

  ofstream outfile (filename.c_str());

  outfile.precision(6);
  outfile.setf (ios::fixed, ios::floatfield);
  outfile.setf (ios::showpoint);

  outfile << np << "\n";

  for (i = 1; i <= np; i++)
    {
      const Point3d & p = mesh.Point(i);

      outfile.width(10);
      outfile << p.X() << " ";
      outfile.width(9);
      outfile << p.Y() << " ";
      if (mesh.GetDimension() == 3)
	{
	  outfile.width(9);
	  outfile << p.Z();
	  }
      outfile << "\n";
    }

  if (mesh.GetDimension() == 3)
    {
      outfile << ne << "\n";
      for (i = 1; i <= ne; i++)
	{
	  Element el = mesh.VolumeElement(i);
	  if (inverttets)
	    el.Invert();
	  outfile.width(4);
	  outfile << el.GetIndex() << "  ";
	  for (j = 1; j <= el.GetNP(); j++)
	    {
	      outfile << " ";
	      outfile.width(8);
	      outfile << el.PNum(j);
	    }
	  outfile << "\n";
	}
    }

  outfile << nse << "\n";
  for (i = 1; i <= nse; i++)
    {
      Element2d el = mesh.SurfaceElement(i);
      if (invertsurf)
	el.Invert();
      outfile.width(4);
      outfile << mesh.GetFaceDescriptor (el.GetIndex()).BCProperty() << "    ";
      for (j = 1; j <= el.GetNP(); j++)
	{
	  outfile << " ";
	  outfile.width(8);
	  outfile << el.PNum(j);
	}
      outfile << "\n";
    }


  if (mesh.GetDimension() == 2)
    {
      outfile << nseg << "\n";
      for (i = 1; i <= nseg; i++)
	{
	  const Segment & seg = mesh.LineSegment(i);
	  outfile.width(4);
	  outfile << seg.si << "    ";

	  outfile << " ";
	  outfile.width(8);
	  outfile << seg[0];
	  outfile << " ";
	  outfile.width(8);
	  outfile << seg[1];

	  outfile << "\n";
	}
    }
}