Vector3f cTrackball::ballVector(Vector2f screen) const
{
    // normalize and centre the screen coordinates first
    screen -= m_center;
    screen /= m_radius;
    
    float lsqared = screen.squaredNorm();
    Vector3f ball;
    
    // if we are grabbing outside the bounds of the virtual hemisphere, 
    // take a point on the edge
    if (lsqared > 1.0)
    {
        screen.normalize();
        ball = Vector3f(screen[0], screen[1], 0.0f);
    }
    // otherwise we are on the protruding hemisphere
    else
    {
        float z = sqrtf(1.0f - lsqared);
        ball = Vector3f(screen[0], screen[1], z);
    }

    // return the ball vector, taking into account the camera's orientation
    return m_inverseCamera * ball;
}