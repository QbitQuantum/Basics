void  ProjectionCamera::makeLookAtViewMatrix(Vec3f camPos ,Vec3f  center,Vec3f up,Matrix44f &_lookatMatrix)
{
  Vec3f zaxis = camPos-center;
    zaxis.normalize();
    Vec3f xaxis = up.cross( zaxis);
    xaxis.normalize();
    Vec3f  yaxis  =zaxis.cross(    xaxis);
          
	_lookatMatrix.set(xaxis.x,yaxis.x,zaxis.x,0,xaxis.y,yaxis.y,zaxis.y,0,xaxis.z,yaxis.z,zaxis.z,0,-xaxis.dot( camPos),-yaxis.dot( camPos),-zaxis.dot( camPos),1);
	
}