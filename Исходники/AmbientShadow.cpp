inline int getEdgeExtraAndUpdateSpike(Vector2* currentSpike, const Vector3& secondVertex,
                                      const Vector3& centroid) {
    Vector2 secondSpike = {secondVertex.x - centroid.x, secondVertex.y - centroid.y};
    secondSpike.normalize();

    int result = ShadowTessellator::getExtraVertexNumber(secondSpike, *currentSpike,
                                                         EDGE_RADIANS_DIVISOR);
    *currentSpike = secondSpike;
    return result;
}