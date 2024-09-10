Welder::Welder(    
    const Array<Vector3>& _oldVertexArray,
    Array<Vector3>&       _newVertexArray,
    Array<int>&           _toNew,
    Array<int>&           _toOld,
    double                _radius) :
    oldVertexArray(_oldVertexArray),
    newVertexArray(_newVertexArray),
    toNew(_toNew),
    toOld(_toOld),
    radius(_radius) {

    // Compute a scale factor that moves the range
    // of all ordinates to [0, 1]
    Vector3 minBound = Vector3::inf();
    Vector3 maxBound = -minBound;

    for (int i = 0; i < oldVertexArray.size(); ++i) {
        minBound = minBound.min(oldVertexArray[i]);
        maxBound = maxBound.max(oldVertexArray[i]);
    }

    offset = minBound;
    scale  = maxBound - minBound;
    for (int i = 0; i < 3; ++i) {
        // The model might have zero extent along some axis
        if (fuzzyEq(scale[i], 0.0)) {
            scale[i] = 1.0;
        } else {
            scale[i] = 1.0 / scale[i];
        }
    }
}