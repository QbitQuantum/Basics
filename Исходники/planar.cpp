// Algorithm:
// plane equation: P*N + c = 0
// we find point rays in 3D from image points and camera parameters
// then we fit c by minimizing average L2 distance between rotated and translated object points
// and points found by crossing point rays with plane. We use the fact that center of mass
// of object points and fitted points should coincide.
void findPlanarObjectPose(const vector<Point3f>& _object_points, const Mat& image_points, const Point3f& normal,
                const Mat& intrinsic_matrix, const Mat& distortion_coeffs, double& alpha, double& C, vector<Point3f>& object_points_crf)
{
    vector<Point2f> _rays;
    undistortPoints(image_points, _rays, intrinsic_matrix, distortion_coeffs);

    // filter out rays that are parallel to the plane
    vector<Point3f> rays;
    vector<Point3f> object_points;
    for(size_t i = 0; i < _rays.size(); i++)
    {
        Point3f ray(_rays[i].x, _rays[i].y, 1.0f);
        double proj = ray.dot(normal);
        if(fabs(proj) > std::numeric_limits<double>::epsilon())
        {
            rays.push_back(ray*(1.0/ray.dot(normal)));
            object_points.push_back(_object_points[i]);
        }
    }

    Point3f pc = massCenter(rays);
    Point3f p0c = massCenter(object_points);
    
    vector<Point3f> drays;
    drays.resize(rays.size());
    for(size_t i = 0; i < rays.size(); i++)
    {
        drays[i] = rays[i] - pc;
        object_points[i] -= p0c;
    }

    double s1 = 0.0, s2 = 0.0, s3 = 0.0;
    for(size_t i = 0; i < rays.size(); i++)
    {
        Point3f vprod = crossProduct(drays[i], object_points[i]);
        s1 += vprod.dot(normal);
        s2 += drays[i].dot(object_points[i]);
        s3 += drays[i].dot(drays[i]);
    }
    
    alpha = atan2(s1, s2);
    C = (s2*cos(alpha) + s1*sin(alpha))/s3;
    
//    printf("alpha = %f, C = %f\n", alpha, C);
    
    object_points_crf.resize(rays.size());
    for(size_t i = 0; i < rays.size(); i++)
    {
        object_points_crf[i] = rays[i]*C;
    }
}