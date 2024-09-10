bool intersectWithCylinder(float radius, float m_x, float m_z, cv::Point2f pixel,const cv::Mat &P, const cv::Mat projector_position, cv::Point3f& S, float& out_y, float& out_phi, float &hit_angle){


 // get one point that projects on the given pixel:
 cv::Point3f point_on_ray;

 project3D(pixel, P, 1, point_on_ray);

 cv::Point3f center(projector_position.at<double>(0),projector_position.at<double>(1),projector_position.at<double>(2));



 bool intersects_with_cylinder = intersect(center, point_on_ray, m_x,m_z, radius, S);

 if (!intersects_with_cylinder) return false;


 // HACK!
 if (S.z > 0) return false;

 out_y = S.y;
 out_phi = atan2(S.x-m_x,-(S.z-m_z))/M_PI*180;

 // compute angle between (projector, S) and (Center,S)
 Eigen::Vector3f PS;
 PS.x() = projector_position.at<double>(0)-S.x;
 PS.y() = projector_position.at<double>(1)-S.y;
 PS.z() = projector_position.at<double>(2)-S.z;
 PS.normalize();

 Eigen::Vector3f MS;
 MS.x() = S.x-m_x;
 MS.y() = 0;
 MS.z() = S.z-m_z;
 MS.normalize();



 hit_angle = acos(PS.dot(MS))/M_PI*180;




 return true;
}