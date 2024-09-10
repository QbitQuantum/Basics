void BaseMesh::CreateViewPlane(float EyeDist, UINT slices, MatrixController &MC)
{
    Matrix4 Perspective = MC.Perspective, PInverse;

    PInverse = Perspective.Inverse();

    Vec3f PerspectiveCoord(0.0f, 0.0f, EyeDist);
    PerspectiveCoord = Perspective.TransformPoint(PerspectiveCoord);    //get the top-left coord in persp. space

    PerspectiveCoord.x = 1.0f;
    PerspectiveCoord.y = -1.0f;
    PerspectiveCoord = PInverse.TransformPoint(PerspectiveCoord);        //get the bottom-right coord in persp. space

    CreatePlane(2.0f, slices, slices);    //create the X-Y plane

    Matrix4 Scale = Matrix4::Scaling(Vec3f(PerspectiveCoord.x, PerspectiveCoord.y, 1.0f));    //scale it appropriately,
    Matrix4 Translate = Matrix4::Translation(Vec3f(0.0f,0.0f,PerspectiveCoord.z));            //translate it away from the eye,

    Matrix4 VInverse = MC.View.Inverse();    //we need to transform our mesh and we want to fact the view and world transforms in
    Matrix4 WInverse = MC.World.Inverse();

    //
    // Translate and scale, then go into object space by multiplying through the inverse of view/world.
    //
    ApplyMatrix(Translate * Scale * VInverse * WInverse);
}