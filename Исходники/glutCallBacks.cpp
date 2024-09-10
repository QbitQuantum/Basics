static void MotionCallback(int x, int y)
{
    int dx = gMouseX - x;
    int dy = gMouseY - y;

    gDir.normalize();		//カメラの視線ベクトルを正規化
    gViewY.cross(gDir, NxVec3(0,1,0));	//

    if( gMouseButton[0] && gMouseButton[1] ) {
        //Zoom: Left + Center Buttons Drag
        gEye -= gDir * 0.5f * dy;
    } else {
        if( gMouseButton[0] ) {
            //Rotate: Left Button Drag
            NxQuat qx(NxPiF32 * dx * 10/ 180.0f, NxVec3(0,1,0));
            qx.rotate(gDir);
            NxQuat qy(NxPiF32 * dy * 10/ 180.0f, gViewY);
            qy.rotate(gDir);
        } else if( gMouseButton[1] ) {
            //Move: Center Button Drag
            gEye += 0.1f * (gViewY * dx - NxVec3(0, 1, 0) * dy);
        }
    }
    gMouseX = x;
    gMouseY = y;
    glutPostRedisplay();
}