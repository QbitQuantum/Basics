void ProtHelpObject::BuildMesh()
{
   if(meshBuilt)
      return;
   int nverts = 7;
   int nfaces = 8;
   mesh.setNumVerts(nverts);
   mesh.setNumFaces(nfaces);

   float d = 5.0f;
   float ds = 0.866f * d;
   float h = 2.0f * 0.866f * 5.0f;

   mesh.setVert(0, Point3(0.0f, 0.0f, 0.0f ));
   mesh.setVert(1, Point3(  -d,  -ds, -h ));
   mesh.setVert(2, Point3(   d,  -ds, -h ));
   mesh.setVert(3, Point3(0.0f,   ds, -h ));
   mesh.setVert(4, Point3(  -d,  -ds,  h ));
   mesh.setVert(5, Point3(   d,  -ds,  h ));
   mesh.setVert(6, Point3(0.0f,   ds,  h ));
   mesh.faces[0].setVerts(0, 1, 2);
   mesh.faces[0].setEdgeVisFlags(1,1,1);
   mesh.faces[1].setVerts(0, 2, 3);
   mesh.faces[1].setEdgeVisFlags(1,1,1);
   mesh.faces[2].setVerts(0, 3, 1);
   mesh.faces[2].setEdgeVisFlags(1,1,1);
   mesh.faces[3].setVerts(3, 2, 1);
   mesh.faces[3].setEdgeVisFlags(1,1,1);
   mesh.faces[4].setVerts(0, 5, 4);
   mesh.faces[4].setEdgeVisFlags(1,1,1);
   mesh.faces[5].setVerts(0, 6, 5);
   mesh.faces[5].setEdgeVisFlags(1,1,1);
   mesh.faces[6].setVerts(0, 4, 6);
   mesh.faces[6].setEdgeVisFlags(1,1,1);
   mesh.faces[7].setVerts(4, 5, 6);
   mesh.faces[7].setEdgeVisFlags(1,1,1);
#if 1
   // whoops- rotate 90 about x to get it facing the right way
   Matrix3 mat;
   mat.IdentityMatrix();
   mat.RotateX(DegToRad(90.0));
   for (int i=0; i<nverts; i++)
      mesh.getVert(i) = mat*mesh.getVert(i);
#endif
// mesh.buildNormals();
   meshBuilt = 1;
}