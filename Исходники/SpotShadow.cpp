// Find the right polygon edge to shoot the ray at.
inline int findPolyIndex(bool isPositiveCross, int startPolyIndex, const Vector2& umbraDir,
        const Vector2* polyToCentroid, int polyLength) {
    // Make sure we loop with a bound.
    for (int i = 0; i < polyLength; i++) {
        int currentIndex = (i + startPolyIndex) % polyLength;
        const Vector2& currentToCentroid = polyToCentroid[currentIndex];
        const Vector2& nextToCentroid = polyToCentroid[(currentIndex + 1) % polyLength];

        float currentCrossUmbra = currentToCentroid.cross(umbraDir);
        float umbraCrossNext = umbraDir.cross(nextToCentroid);
        if (sameDirections(isPositiveCross, currentCrossUmbra, umbraCrossNext)) {
#if DEBUG_SHADOW
            ALOGD("findPolyIndex loop %d times , index %d", i, currentIndex );
#endif
            return currentIndex;
        }
    }
    LOG_ALWAYS_FATAL("Can't find the right polygon's edge from startPolyIndex %d", startPolyIndex);
    return -1;
}