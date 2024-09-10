void ColorCubePoints::LineSolver::solve(vector<Vec3f> &points)
{
    const int m = points.size();    // Number of functions to minimize
    const int n = 5;                // Number of independent variables

    vector<int> iwa(n);                // Integer work array
    vector<float> wa(m*n + 5*n + m);   // Working array
    vector<float> residuals(m);
    
    // Default tolerance: sqaure root of machine precision
    float tol = sqrt(sdpmpar(1));

    // If solution is out of range, start over
    float limit0 = 4.0f;
    if (result.x0 < -limit0 || result.x0 > limit0 ||
        result.y0 < -limit0 || result.y0 > limit0) {
        result.setDefault();
    }
    
    // Minimize the system of equations
    slmdif1(&minFunc, &points[0], m, n,
          &result.array[0], &residuals[0],
          tol, &iwa[0], &wa[0], (int)wa.size());

    // Local coordinate system has a stable XY plane perpendicular to the line, and Z along the line.
    // X and Y axes are defined relative to Z, to be the same length.
    
    Vec3f origin(result.x0, result.y0, 0.0f);
    Vec3f zAxis(result.xz, result.yz, 1.0f);
    float zScale = 1.0f / zAxis.length();

    Vec3f up(0.0f, 1.0f, 0.0f);
    Vec3f xAxis = zAxis.cross(up).normalized() * zScale;
    Vec3f yAxis = xAxis.cross(zAxis).normalized() * zScale;

    localToWorld.setColumn(0, Vec4f(xAxis, origin.x));
    localToWorld.setColumn(1, Vec4f(yAxis, origin.y));
    localToWorld.setColumn(2, Vec4f(zAxis, origin.z));
    localToWorld.setColumn(3, Vec4f(0.0f, 0.0f, 0.0f, 1.0f));

    worldToLocal = localToWorld.affineInverted();
}