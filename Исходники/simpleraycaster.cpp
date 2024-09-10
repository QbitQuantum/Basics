bool SimpleRayCaster::intersectRayTriangle(const Eigen::Vector3f ray,
        const Eigen::Vector3f a, const Eigen::Vector3f b, const Eigen::Vector3f c,
        Eigen::Vector3f& isec)
{

    /* As discribed by:
     * http://geomalgorithms.com/a06-_intersect-2.html#intersect_RayTriangle%28%29 */

    const Eigen::Vector3f p(0,0,0);
    const Eigen::Vector3f u = b - a;
    const Eigen::Vector3f v = c - a;
    const Eigen::Vector3f n = u.cross(v);
    const float n_dot_ray = n.dot(ray);

    if (std::fabs(n_dot_ray) < 1e-9) {
        return false;
    }


    const float r = n.dot(a-p) / n_dot_ray;

    if (r < 0) {
        return false;
    }

    // the ray intersection point
    isec = ray * r;

    const Eigen::Vector3f w = p + r * ray - a;
    const float denominator = u.dot(v) * u.dot(v) - u.dot(u) * v.dot(v);
    const float s_numerator = u.dot(v) * w.dot(v) - v.dot(v) * w.dot(u);
    const float s = s_numerator / denominator;
    if (s < 0 || s > 1) {
        return false;
    }

    const float t_numerator = u.dot(v) * w.dot(u) - u.dot(u) * w.dot(v);
    const float t = t_numerator / denominator;
    if (t < 0 || s+t > 1) {
        return false;
    }

    return true;
}