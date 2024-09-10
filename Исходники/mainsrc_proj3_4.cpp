void DrawManipulator(void)
{

    // color
    RGBR_f colorRed(1, 0, 0, 1);
    RGBR_f colorGreen(0, 1, 0, 1);
    RGBR_f colorBlue(0, 0, 1, 1);
    RGBR_f colorWhite(1,1,1,1);
    RGBR_f colorMagenta(1.0f,0.3f,1.0f, 1.0f);
    RGBR_f colorGrey(0.2f,0.2f,0.2f, 1.0f);

    // a, y and z axis
    STVector3 xaxis = STVector3::eX;
    STVector3 yaxis = STVector3::eY;
    STVector3 zaxis = STVector3::eZ;

    // camera basis
    STVector3 up = pScene->GetCamera()->Up();
    STVector3 right = pScene->GetCamera()->Right();
    STVector3 dir = pScene->GetCamera()->LookAt();
    STVector3 front;
    front = front.Cross(right, xaxis);
    front.Normalize();

    // camera plane
    float colx[4] = {1, 0, 0, 1};
    float coly[4] = {0, 1, 0, 1};
    float colz[4] = {0, 0, 1, 1};
    float colall[4] = {1, 1, 1, 1};

    float fct = 0.05f;
    float fct2 = 0.83f;

    STMatrix4 curModelMatrix;
    curModelMatrix.EncodeI();

    //------------------------------------------------------------------------------
    // TO DO: Proj3_4 OpenGL
    // Update the matrix transformation for the manipulator geometry
    // Update curModelMatrix
    //------------------------------------------------------------------------------
    curModelMatrix.EncodeS(0.1, 0.1, 0.1);
    //-------------------------------------------------------------------------------

    // screen projection
    ViewProjectionScreenSpace(curModelMatrix);

    STVector3 origin(0,0,0);
    curModelMatrix.GetT(&origin.x, &origin.y, &origin.z);

    if(pScene->CurrentManipMode() == LOCAL) {
        xaxis.Transform(curModelMatrix);
        yaxis.Transform(curModelMatrix);
        zaxis.Transform(curModelMatrix);
        xaxis.Normalize();
        yaxis.Normalize();
        zaxis.Normalize();
    }


    // Rotations
    if((pScene->CurrentManipGeometryState() == AXIS_ALL) || 
        (pScene->CurrentManipGeometryState() == AXIS_ROTATIONALL)) {


        STVector3 X_UP;
        STVector3 X_RIGHT;
        STVector3 X_FRONT;
        STVector3 X_UP_sc;
        STVector3 X_RIGHT_sc;
        STVector3 X_FRONT_sc;


        STVector3 planenorm(pScene->GetCamera()->Position() - origin);
        planenorm.Normalize();
        STVector4 camplane = vector4(planenorm,0);
        
        // duplicate
        X_RIGHT   =   right    * ScreenFactor();
        X_UP      =   up       * ScreenFactor();
        if(pScene->CurrentManipMotion() == ROTATE_DUPLICATE)
            DrawCircle(origin, colorWhite, X_RIGHT, X_UP);
        else
            DrawCircle(origin, colorGrey, X_RIGHT, X_UP);


        // screen rot
        X_UP_sc    =  up * 1.2f       * ScreenFactor();
        X_RIGHT_sc =  right * 1.2f    * ScreenFactor();
        if(pScene->CurrentManipMotion() == ROTATE_SCREEN) 
            DrawCircle(origin, colorWhite, X_UP_sc, X_RIGHT_sc);
        else 
            DrawCircle(origin, colorMagenta, X_UP_sc, X_RIGHT_sc);


        // x rot
        right.Cross(dir, xaxis);
        right.Normalize();
        front.Cross(right, xaxis);
        front.Normalize();
        X_RIGHT   =   right    * ScreenFactor();
        X_FRONT   =   front    * ScreenFactor();
        if(pScene->CurrentManipMotion() == ROTATE_Y)
            DrawCircleHalf(origin, colorWhite, X_RIGHT, X_FRONT, camplane);
        else
            DrawCircleHalf(origin, colorRed, X_RIGHT, X_FRONT, camplane);


        // y rot
        right.Cross(dir, yaxis);
        right.Normalize();
        front.Cross(right, yaxis);
        front.Normalize();
        X_RIGHT   =   right    * ScreenFactor();
        X_FRONT   =   front    * ScreenFactor();
        if(pScene->CurrentManipMotion() == ROTATE_Y)
            DrawCircleHalf(origin, colorWhite, X_RIGHT, X_FRONT, camplane);
        else
            DrawCircleHalf(origin, colorGreen, X_RIGHT, X_FRONT, camplane);

        // z rot
        right.Cross(dir, zaxis);
        right.Normalize();
        front.Cross(right, zaxis);
        front.Normalize();
        X_RIGHT   =   right    * ScreenFactor();
        X_FRONT   =   front    * ScreenFactor();
        if(pScene->CurrentManipMotion() == ROTATE_Z)
            DrawCircleHalf(origin, colorWhite, X_RIGHT, X_FRONT, camplane);
        else
            DrawCircleHalf(origin, colorBlue, X_RIGHT, X_FRONT, camplane);
    }


    // cam
    if ((pScene->CurrentManipMotion() !=  MANIP_NONE) && ((pScene->CurrentManipMotion() != ROTATE_DUPLICATE)))
        DrawCam(origin, gblXVert*ScreenFactor(), gblYVert *ScreenFactor(), -Ng2);



    // draw translation manupulator
    //-----------------------------------------------
 
    // Translations
    if((pScene->CurrentManipGeometryState() == AXIS_ALL) ||
        (pScene->CurrentManipGeometryState() == AXIS_TRANSXYZ)) {

        DrawQuadrant(origin, 0.5f*ScreenFactor(), (pScene->CurrentManipMotion() == TRANS_XZ), xaxis, zaxis);
        DrawQuadrant(origin, 0.5f*ScreenFactor(), (pScene->CurrentManipMotion() == TRANS_XY), xaxis, yaxis);
        DrawQuadrant(origin, 0.5f*ScreenFactor(), (pScene->CurrentManipMotion() == TRANS_YZ), yaxis, zaxis);

        xaxis *= ScreenFactor();
        yaxis *= ScreenFactor();
        zaxis *= ScreenFactor();


        if(pScene->CurrentManipMotion() == TRANS_X)
            DrawAxis(origin, colorRed, xaxis, yaxis, zaxis, fct, fct2, colall);
        else
            DrawAxis(origin, colorRed, xaxis, yaxis, zaxis, fct, fct2, colx);


        // y axis
        if(pScene->CurrentManipMotion() == TRANS_Y) 
            DrawAxis(origin, colorGreen, yaxis, xaxis, zaxis, fct, fct2, colall);
        else
            DrawAxis(origin, colorGreen, yaxis, xaxis, zaxis, fct, fct2, coly);

    
        // z axis
        if(pScene->CurrentManipMotion() == TRANS_Z) 
            DrawAxis(origin, colorBlue, zaxis, xaxis, yaxis, fct, fct2, colall);
        else
            DrawAxis(origin, colorBlue, zaxis, xaxis, yaxis, fct, fct2, colz);
    }


}