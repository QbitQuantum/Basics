TEST (PCL, Matrix4Affine3Transform)
{
  float rot_x = 2.8827f;
  float rot_y = -0.31190f;
  float rot_z = -0.93058f;
  Eigen::Affine3f affine;
  pcl::getTransformation (0, 0, 0, rot_x, rot_y, rot_z, affine);

  EXPECT_NEAR (affine (0, 0),  0.56854731f, 1e-4); EXPECT_NEAR (affine (0, 1), -0.82217032f, 1e-4); EXPECT_NEAR (affine (0, 2), -0.028107658f, 1e-4);
  EXPECT_NEAR (affine (1, 0), -0.76327348f, 1e-4); EXPECT_NEAR (affine (1, 1), -0.51445758f, 1e-4); EXPECT_NEAR (affine (1, 2), -0.39082864f, 1e-4);
  EXPECT_NEAR (affine (2, 0),  0.30686751f, 1e-4); EXPECT_NEAR (affine (2, 1),  0.24365838f, 1e-4); EXPECT_NEAR (affine (2, 2), -0.920034f, 1e-4);

  // Approximative!!! Uses SVD internally! See http://eigen.tuxfamily.org/dox/Transform_8h_source.html
  Eigen::Matrix3f rotation = affine.rotation ();

  EXPECT_NEAR (rotation (0, 0),  0.56854731f, 1e-4); EXPECT_NEAR (rotation (0, 1), -0.82217032f, 1e-4); EXPECT_NEAR (rotation (0, 2), -0.028107658f, 1e-4);
  EXPECT_NEAR (rotation (1, 0), -0.76327348f, 1e-4); EXPECT_NEAR (rotation (1, 1), -0.51445758f, 1e-4); EXPECT_NEAR (rotation (1, 2), -0.39082864f, 1e-4);
  EXPECT_NEAR (rotation (2, 0),  0.30686751f, 1e-4); EXPECT_NEAR (rotation (2, 1),  0.24365838f, 1e-4); EXPECT_NEAR (rotation (2, 2), -0.920034f, 1e-4);

  float trans_x, trans_y, trans_z;
  pcl::getTransformation (0.1f, 0.2f, 0.3f, rot_x, rot_y, rot_z, affine);
  pcl::getTranslationAndEulerAngles (affine, trans_x, trans_y, trans_z, rot_x, rot_y, rot_z);
  EXPECT_FLOAT_EQ (trans_x, 0.1f);
  EXPECT_FLOAT_EQ (trans_y, 0.2f);
  EXPECT_FLOAT_EQ (trans_z, 0.3f);
  EXPECT_FLOAT_EQ (rot_x, 2.8827f);
  EXPECT_FLOAT_EQ (rot_y, -0.31190f);
  EXPECT_FLOAT_EQ (rot_z, -0.93058f);

  Eigen::Matrix4f transformation (Eigen::Matrix4f::Identity ());
  transformation.block<3, 3> (0, 0) = affine.rotation ();
  transformation.block<3, 1> (0, 3) = affine.translation ();

  PointXYZ p (1.f, 2.f, 3.f);
  Eigen::Vector3f v3 = p.getVector3fMap ();
  Eigen::Vector4f v4 = p.getVector4fMap ();

  Eigen::Vector3f v3t (affine * v3);
  Eigen::Vector4f v4t (transformation * v4);

  PointXYZ pt = pcl::transformPoint (p, affine);

  EXPECT_NEAR (pt.x, v3t.x (), 1e-4); EXPECT_NEAR (pt.x, v4t.x (), 1e-4);
  EXPECT_NEAR (pt.y, v3t.y (), 1e-4); EXPECT_NEAR (pt.y, v4t.y (), 1e-4);
  EXPECT_NEAR (pt.z, v3t.z (), 1e-4); EXPECT_NEAR (pt.z, v4t.z (), 1e-4);

  PointNormal pn;
  pn.getVector3fMap () = p.getVector3fMap ();
  pn.getNormalVector3fMap () = Eigen::Vector3f (0.60f, 0.48f, 0.64f);
  Eigen::Vector3f n3 = pn.getNormalVector3fMap ();
  Eigen::Vector4f n4 = pn.getNormalVector4fMap ();

  Eigen::Vector3f n3t (affine.rotation() * n3);
  Eigen::Vector4f n4t (transformation * n4);

  PointNormal pnt = pcl::transformPointWithNormal (pn, affine);

  EXPECT_NEAR (pnt.x, v3t.x (), 1e-4); EXPECT_NEAR (pnt.x, v4t.x (), 1e-4);
  EXPECT_NEAR (pnt.y, v3t.y (), 1e-4); EXPECT_NEAR (pnt.y, v4t.y (), 1e-4);
  EXPECT_NEAR (pnt.z, v3t.z (), 1e-4); EXPECT_NEAR (pnt.z, v4t.z (), 1e-4);
  EXPECT_NEAR (pnt.normal_x, n3t.x (), 1e-4); EXPECT_NEAR (pnt.normal_x, n4t.x (), 1e-4);
  EXPECT_NEAR (pnt.normal_y, n3t.y (), 1e-4); EXPECT_NEAR (pnt.normal_y, n4t.y (), 1e-4);
  EXPECT_NEAR (pnt.normal_z, n3t.z (), 1e-4); EXPECT_NEAR (pnt.normal_z, n4t.z (), 1e-4);

  PointCloud<PointXYZ> c, ct;
  c.push_back (p);
  pcl::transformPointCloud (c, ct, affine);
  EXPECT_FLOAT_EQ (pt.x, ct[0].x); 
  EXPECT_FLOAT_EQ (pt.y, ct[0].y); 
  EXPECT_FLOAT_EQ (pt.z, ct[0].z); 

  pcl::transformPointCloud (c, ct, transformation);
  EXPECT_FLOAT_EQ (pt.x, ct[0].x); 
  EXPECT_FLOAT_EQ (pt.y, ct[0].y); 
  EXPECT_FLOAT_EQ (pt.z, ct[0].z); 

  affine = transformation;

  std::vector<int> indices (1); indices[0] = 0;

  pcl::transformPointCloud (c, indices, ct, affine);
  EXPECT_FLOAT_EQ (pt.x, ct[0].x); 
  EXPECT_FLOAT_EQ (pt.y, ct[0].y); 
  EXPECT_FLOAT_EQ (pt.z, ct[0].z); 

  pcl::transformPointCloud (c, indices, ct, transformation);
  EXPECT_FLOAT_EQ (pt.x, ct[0].x); 
  EXPECT_FLOAT_EQ (pt.y, ct[0].y); 
  EXPECT_FLOAT_EQ (pt.z, ct[0].z); 
}