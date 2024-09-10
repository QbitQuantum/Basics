pcl::PointCloud<pcl::PointNormal>::Ptr
meshToFaceCloud (const pcl::PolygonMesh &mesh)
{
  pcl::PointCloud<pcl::PointNormal>::Ptr cloud (new pcl::PointCloud<pcl::PointNormal>);
  pcl::PointCloud<pcl::PointXYZ> vertices;
  pcl::fromPCLPointCloud2 (mesh.cloud, vertices);

  for (size_t i = 0; i < mesh.polygons.size (); ++i)
  {
    if (mesh.polygons[i].vertices.size () != 3)
    {
      PCL_ERROR ("Found a polygon of size %d\n", mesh.polygons[i].vertices.size ());
      continue;
    }
    Eigen::Vector3f v0 = vertices.at (mesh.polygons[i].vertices[0]).getVector3fMap ();
    Eigen::Vector3f v1 = vertices.at (mesh.polygons[i].vertices[1]).getVector3fMap ();
    Eigen::Vector3f v2 = vertices.at (mesh.polygons[i].vertices[2]).getVector3fMap ();
    float area = ((v1 - v0).cross (v2 - v0)).norm () / 2. * 1E4;
    Eigen::Vector3f normal = ((v1 - v0).cross (v2 - v0));
    normal.normalize ();
    pcl::PointNormal p_new;
    p_new.getVector3fMap () = (v0 + v1 + v2)/3.;
    p_new.normal_x = normal (0);
    p_new.normal_y = normal (1);
    p_new.normal_z = normal (2);
    cloud->points.push_back (p_new);
  }
  cloud->height = 1;
  cloud->width = cloud->size ();
  return (cloud);
}