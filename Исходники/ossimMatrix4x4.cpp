void ossimMatrix4x4::setIdentity()
{
   setZero();
   theData[0][0] = 1.0;
   theData[1][1] = 1.0;
   theData[2][2] = 1.0;
   theData[3][3] = 1.0;
}