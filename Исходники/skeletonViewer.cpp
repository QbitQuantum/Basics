//////////////////////////////////////////////////////////////////////////////////
//// Compute the current modelview matrix
//////////////////////////////////////////////////////////////////////////////////
Matrix3 getModelviewMatrix()
{
    up /= up.length(); // ensure the up vector is normalized

    // compute x, y, and z of modelview transform
    Vector3 foc = focus; //foc[1]*=-1;
    Vector3 f = (foc)-eye;
        f/=f.length();
    Vector3 s = f.cross(up);
    Vector3 u = (s/s.length()).cross(f);

    // correct dimensions
    f = -f;

    return Matrix3(s, u, f);
}