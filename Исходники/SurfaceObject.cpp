/**
 * Retrieves the normal of the terrain at the specified location.
 *
 * @param x the x coordinate to check
 * @param y the y coordinate to check
 * @param normal the location at which to store the normal
 * instead of triangle mesh height
 */
void SurfaceObject::GetNormal(float x, float y, osg::Vec3& normal)
{
      float z = GetHeight(x, y);

      osg::Vec3 v1(0.1f, 0.0f, GetHeight(x + 0.1f, y) - z);
      osg::Vec3 v2(0.0f, 0.1f, GetHeight(x, y + 0.1f) - z );

      normal = v1 ^ v2;

      normal.normalize();

      /*   if (normal.x() != 0 ||  normal.y() != 0 || normal.z() != 1 )
   	std::cout<<"NORM "<<"("<<normal.x()<<",\t"<<normal.y()<<",\t"<<normal.z()<<")"<<std::endl;
*/
}