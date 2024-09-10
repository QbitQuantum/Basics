void Helm::goTo( xyz location ) {
  
  xyz delta;
  float distance;
  float theta;
  
  delta.x = location.x - currentPos.x;
  delta.y = location.y - currentPos.y;
  delta.z = location.z - currentPos.z;
  
  distance = sqrt( pow(delta.x, 2) + pow(delta.y, 2) );
  theta = atanf( delta.x / delta.y ) - this->rotation;
  
  rotate( theta );
  goDistance( distance );
  
}