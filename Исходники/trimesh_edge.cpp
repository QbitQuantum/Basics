int main( int argc, char **argv )
{
  if(argc<2)
  {
    printf("Usage trimesh_base <meshfilename.ply>\n");
    return -1;
  }

  MyMesh m,em,cm,full;

  if(tri::io::ImporterPLY<MyMesh>::Open(m,argv[1])!=0)
  {
    printf("Error reading file  %s\n",argv[1]);
    exit(0);
  }

  tri::UpdateFlags<MyMesh>::FaceBorderFromFF(m);
  tri::UpdateNormals<MyMesh>::PerVertexNormalized(m);
  tri::UpdateBounding<MyMesh>::Box(m);

  printf("Input mesh  vn:%i fn:%i\n",m.vn,m.fn);
  printf( "Mesh has %i vert and %i faces\n", m.vn, m.fn );
  srand(time(0));
  Plane3f slicingPlane;
  Point3f planeCenter = m.bbox.Center();

  for(int i=0;i<10;++i)
  {
    cm.Clear();
    em.Clear();
    Point3f planeDir = Point3f(-0.5f+float(rand())/RAND_MAX,-0.5f+float(rand())/RAND_MAX,-0.5f+float(rand())/RAND_MAX);
    planeDir.Normalize();
    printf("slicing dir %5.2f %5.2f %5.2f\n",planeDir[0],planeDir[1],planeDir[2]);

    slicingPlane.Init(planeCenter+planeDir*0.3f*m.bbox.Diag()*float(rand())/RAND_MAX,planeDir);

    vcg::IntersectionPlaneMesh<MyMesh, MyMesh, float>(m, slicingPlane, em );
    tri::Clean<MyMesh>::RemoveDuplicateVertex(em);
    vcg::tri::CapEdgeMesh(em,cm);

    printf("  edge mesh vn %5i en %5i fn %5i\n",em.vn,em.en,em.fn);
    printf("sliced mesh vn %5i en %5i fn %5i\n",cm.vn,cm.en,cm.fn);

    tri::Append<MyMesh,MyMesh>::Mesh(full,cm);
  }

  tri::io::ExporterPLY<MyMesh>::Save(full,"out.ply",false);

  return 0;
}