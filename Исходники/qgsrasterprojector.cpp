void ProjectorData::calcCP( int row, int col, const QgsCoordinateTransform &ct )
{
  double myDestX, myDestY;
  destPointOnCPMatrix( row, col, &myDestX, &myDestY );
  QgsPointXY myDestPoint( myDestX, myDestY );
  try
  {
    if ( ct.isValid() )
    {
      mCPMatrix[row][col] = ct.transform( myDestPoint );
      mCPLegalMatrix[row][col] = true;
    }
    else
    {
      mCPLegalMatrix[row][col] = false;
    }
  }
  catch ( QgsCsException &e )
  {
    Q_UNUSED( e );
    // Caught an error in transform
    mCPLegalMatrix[row][col] = false;
  }
}