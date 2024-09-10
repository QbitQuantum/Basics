void DXApp::HandleMouseMove(bool bMouseDown, int X, int Y)
{
    if(bMouseDown)
    {
        NxVec3 Temp;
        Temp = Cam.location;
        Temp.y = 0;
        Temp.normalize();
        Temp = Temp.cross(NxVec3(0.0f, 1.0f, 0.0f));
        NxQuat(((float)(Y-OldMY))/20.0f, Temp).rotate(Cam.ViewDir);

        Temp = NxVec3(0.0f, 1.0f, 0.0f);
        NxQuat(((float)(X-OldMX))/20.0f, Temp).rotate(Cam.ViewDir);
    }
    OldMX = X;
    OldMY = Y;
}