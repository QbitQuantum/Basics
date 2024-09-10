void Mesher::check_feature()
{
    auto contour = get_contour();
    const auto normals = get_normals(contour);

    // Find the largest cone and the normals that enclose
    // the largest angle as n0, n1.
    float theta = 1;
    Vec3f n0, n1;
    for (auto ni : normals)
    {
        for (auto nj : normals)
        {
            float dot = ni.dot(nj);
            if (dot < theta)
            {
                theta = dot;
                n0 = ni;
                n1 = nj;
            }
        }
    }

    // If there isn't a feature in this fan, then return immediately.
    if (theta > 0.9)
        return;

    // Decide whether this is a corner or edge feature.
    const Vec3f nstar = n0.cross(n1);
    float phi = 0;
    for (auto n : normals)
        phi = fmax(phi, fabs(nstar.dot(n)));
    bool edge = phi < 0.7;

    // Find the center of the contour.
    Vec3f center(0, 0, 0);
    for (auto c : contour)
        center += c;
    center /= contour.size();

    // Construct the matrices for use in our least-square fit.
    Eigen::MatrixX3d A(normals.size(), 3);
    {
        int i=0;
        for (auto n : normals)
            A.row(i++) << n.transpose();
    }

    // When building the second matrix, shift position values to be centered
    // about the origin (because that's what the least-squares fit will
    // minimize).
    Eigen::VectorXd B(normals.size(), 1);
    {
        auto n = normals.begin();
        auto c = contour.begin();
        int i=0;
        while (n != normals.end())
            B.row(i++) << (n++)->dot(*(c++) - center);
    }

    // Use singular value decomposition to solve the least-squares fit.
    Eigen::JacobiSVD<Eigen::MatrixX3d> svd(A, Eigen::ComputeFullU |
                                              Eigen::ComputeFullV);

    // Set the smallest singular value to zero to make fitting happier.
    if (edge)
    {
        auto singular = svd.singularValues();
        svd.setThreshold(singular.minCoeff() / singular.maxCoeff() * 1.01);
    }

    // Solve for the new point's position.
    const Vec3f new_pt = svd.solve(B) + center;

    // Erase this triangle fan, as we'll be inserting a vertex in the center.
    triangles.erase(fan_start, voxel_start);

    // Construct a new triangle fan.
    contour.push_back(contour.front());
    {
        auto p0 = contour.begin();
        auto p1 = contour.begin();
        p1++;
        while (p1 != contour.end())
            push_swappable_triangle(Triangle(*(p0++), *(p1++), new_pt));
    }
}