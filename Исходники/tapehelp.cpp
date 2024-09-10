void TapeHelpObject::BuildMesh()
{
    if(meshBuilt)
        return;
    int nverts = 5;
    int nfaces = 6;
    mesh.setNumVerts(nverts);
    mesh.setNumFaces(nfaces);

    float d =  5.0f;
    float h = 10.0f;

    mesh.setVert(0, Point3(  -d, -d, 0.0f ));
    mesh.setVert(1, Point3(   d, -d, 0.0f ));
    mesh.setVert(2, Point3(   d,  d, 0.0f ));
    mesh.setVert(3, Point3(  -d,  d, 0.0f ));
    mesh.setVert(4, Point3(0.0f,0.0f, -h  ));
    mesh.faces[0].setVerts(0, 3, 1);
    mesh.faces[0].setEdgeVisFlags(1,1,0);
    mesh.faces[1].setVerts(3, 2, 1);
    mesh.faces[1].setEdgeVisFlags(1,1,0);
    mesh.faces[2].setVerts(0, 1, 4);
    mesh.faces[2].setEdgeVisFlags(1,1,1);
    mesh.faces[3].setVerts(1, 2, 4);
    mesh.faces[3].setEdgeVisFlags(1,1,1);
    mesh.faces[4].setVerts(2, 3, 4);
    mesh.faces[4].setEdgeVisFlags(1,1,1);
    mesh.faces[5].setVerts(3, 0, 4);
    mesh.faces[5].setEdgeVisFlags(1,1,1);
#if 0
    // whoops- rotate 180 about x to get it facing the right way
    Matrix3 mat;
    mat.IdentityMatrix();
    mat.RotateX(DegToRad(180.0));
    for (int i=0; i<nverts; i++)
        mesh.getVert(i) = mat*mesh.getVert(i);
#endif
    mesh.buildNormals();
    mesh.EnableEdgeList(1);
    meshBuilt = 1;
}