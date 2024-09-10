void IsometricCubeWidget::getMXMY(int x, int y, int &mx, int &my, QChar face)
{
    Face *actFace;
    switch(face.toLatin1())
    {
    case 'U':
        actFace = faceU;
        break;
    case 'D':
        actFace = faceD;
        break;
    case 'L':
        actFace = faceL;
        break;
    case 'R':
        actFace = faceR;
        break;
    case 'F':
        actFace = faceF;
        break;
    case 'B':
        actFace = faceB;
        break;
    }

    switch(actFace->getO())
    {
    case 0:
        mx = x;
        my = y;
        break;
    case 1:
        mx = y;
        my = 2-x;
        break;
    case 2:
        mx = 2-x;
        my = 2-y;
        break;
    case 3:
        mx = 2-y;
        my = x;
        break;
    }

    mx = mx + actFace->getC()*3;
}