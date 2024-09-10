static Point3f findRayIntersection(Point3f k1, Point3f b1, Point3f k2, Point3f b2)
{    
    float a[4], b[2], x[2];
    a[0] = k1.dot(k1);
    a[1] = a[2] = -k1.dot(k2);
    a[3] = k2.dot(k2);
    b[0] = k1.dot(b2 - b1);
    b[1] = k2.dot(b1 - b2);
    Mat_<float> A(2, 2, a), B(2, 1, b), X(2, 1, x);
    solve(A, B, X);
    
    float s1 = X.at<float>(0, 0);
    float s2 = X.at<float>(1, 0);
    return (k1*s1 + b1 + k2*s2 + b2)*0.5f;
};