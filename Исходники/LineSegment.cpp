Vector2 LineSegment2D::closestPoint(const Vector2& Q) const {
    // Two constants that appear in the result
    const Vector2 k1(m_origin - Q);
    const Vector2& k2 = m_direction;
    
    if (fuzzyEq(m_length, 0)) {
        // This line segment has no length
        return m_origin;
    }

    // Time [0, 1] at which we hit the closest point travelling from p0 to p1.
    // Derivation can be obtained by minimizing the expression
    //     ||P0 + (P1 - P0)t - Q||.
    const float t = -k1.dot(k2) / (m_length * m_length);

    if (t < 0) {
        // Clipped to low end point
        return m_origin;
    } else if (t > 1) {
        // Clipped to high end point
        return m_origin + m_direction;
    } else {
        // Subsitute into the line equation to find 
        // the point on the segment.
        return m_origin + k2 * t;
    }
}