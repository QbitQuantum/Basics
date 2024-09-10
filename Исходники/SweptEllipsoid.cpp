// Checks intersection between a polygon an moving circle at inBegin + t * inDelta with radius^2 = inA * t^2 + inB * t + inC, t in [0, 1]
// Returns true when it does and returns the intersection position in outPoint and the intersection fraction (value for t) in outFraction
bool SweptCircleEdgeVertexIntersect(const Vector2 *inVertices, int inNumVertices, const Vector2 &inBegin, const Vector2 &inDelta, float inA, float inB, float inC, Vector2 &outPoint, float &outFraction)
{
    // Loop through edges
    float upper_bound = 1.0f;
    bool collision = false;
    for (const Vector2 *v1 = inVertices, *v2 = inVertices + inNumVertices - 1; v1 < inVertices + inNumVertices; v2 = v1, ++v1)
    {
        float t;

        // Check if circle hits the vertex
        Vector2 bv1 = *v1 - inBegin;
        float a1 = inA - inDelta.GetLengthSquared();
        float b1 = inB + 2.0f * inDelta.Dot(bv1);
        float c1 = inC - bv1.GetLengthSquared();
        if (FindLowestRootInInterval(a1, b1, c1, upper_bound, t))
        {
            // We have a collision
            collision = true;
            upper_bound = t;
            outPoint = *v1;
        }

        // Check if circle hits the edge
        Vector2 v1v2 = *v2 - *v1;
        float v1v2_dot_delta = v1v2.Dot(inDelta);
        float v1v2_dot_bv1 = v1v2.Dot(bv1);
        float v1v2_len_sq = v1v2.GetLengthSquared();
        float a2 = v1v2_len_sq * a1 + v1v2_dot_delta * v1v2_dot_delta;
        float b2 = v1v2_len_sq * b1 - 2.0f * v1v2_dot_bv1 * v1v2_dot_delta;
        float c2 = v1v2_len_sq * c1 + v1v2_dot_bv1 * v1v2_dot_bv1;
        if (FindLowestRootInInterval(a2, b2, c2, upper_bound, t))
        {
            // Check if the intersection point is on the edge
            float f = t * v1v2_dot_delta - v1v2_dot_bv1;
            if (f >= 0.0f && f <= v1v2_len_sq)
            {
                // We have a collision
                collision = true;
                upper_bound = t;
                outPoint = *v1 + v1v2 * (f / v1v2_len_sq);
            }
        }
    }

    // Check if we had a collision
    if (!collision)
        return false;
    outFraction = upper_bound;
    return true;
}