// Make sure p1 -> p2 is going CW around the poly.
Vector2 ShadowTessellator::calculateNormal(const Vector2& p1, const Vector2& p2) {
    Vector2 result = p2 - p1;
    if (result.x != 0 || result.y != 0) {
        result.normalize();
        // Calculate the normal , which is CCW 90 rotate to the delta.
        float tempy = result.y;
        result.y = result.x;
        result.x = -tempy;
    }
    return result;
}