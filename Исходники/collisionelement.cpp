/*
=============
  SetPointList
  Точки необходимо задавать обходя по часовой стрелке
=============
*/
void CollisionElementPolygon::SetPointList( const PointList &setPoints ) {
  if( setPoints.size() < 3 ) {
    __log.PrintInfo( Filelevel_ERROR, "CollisionElementPolygon::SetPointList => not enough points" );
    return;
  }
  this->pointsSource = setPoints;
  this->pointsResult.clear();
  this->pointsResult.resize( setPoints.size() + 1 );

  //copy src to result
  int num = 0;
  PointList::iterator iter, iterEnd = this->pointsSource.end();
  for( iter = this->pointsSource.begin(); iter != iterEnd; ++iter, ++num ) {
    this->pointsResult[ num ] = *iter;
  }
  this->pointsResult[ this->pointsResult.size() - 1 ] = this->pointsSource[ 0 ];

  Vec2 radiusVector( Vec2Null );
  Vec2 edge0, edge1, edge2;
  num = 0;
  iterEnd = this->pointsResult.end();
  for( iter = this->pointsResult.begin(); iter != iterEnd; ++iter, ++num ) {
    Point *point = &( *iter );
    radiusVector.Set( max( fabs( point->x ), radiusVector.x ), max( fabs( point->y ), radiusVector.y ) );
    if( num > 1 ) {
      //нормальзовать не нужно т.к. нужно не значение, а только знак
      edge0 = this->pointsResult[ num - 1 ] - this->pointsResult[ num - 2 ];
      edge1 = this->pointsResult[ num ] - this->pointsResult[ num - 2 ];
      edge1.Rotate90CW();
      float sign = edge0.Dot( edge1 );
      if( sign > 0 ) {
        __log.PrintInfo( Filelevel_ERROR, "CollisionElementPolygon::SetPointList => points[%d] is not clockwise", num );
        this->pointsResult.clear();
        this->pointsSource.clear();
        return;
      }
    }
  }//for
  this->_rect->radius2 = Square( radiusVector.Length() );

  //формирования списка разделающих осей
  Vec2 axis;
  Vec2 tmpVec2;
  iterEnd = this->pointsResult.end();
  iter = this->pointsResult.begin();
  num = 1;
  for( ++iter; iter != iterEnd; ++iter, ++num ) {
    tmpVec2 = this->pointsResult[ num ] - this->pointsResult[ num - 1 ];
    axis.Set( tmpVec2.x, tmpVec2.y );
    axis.Rotate90CW();
    if( axis.x < 0 ) {
      axis *= -1.0f;
    } else if( axis.y < 0.0f ) {
      axis *= -1.0f;
    }
    axis.Normalize();
    if( !this->_IsAxisExists( axis ) ) {
      this->axes.push_back( axis );
    }
  }//foreach pointsSource
}//SetPointList