LinePatternPos LineAtlas::addDash(const std::vector<float>& dasharray, LinePatternCap patternCap) {
    int n = patternCap == LinePatternCap::Round ? 7 : 0;
    int dashheight = 2 * n + 1;
    const uint8_t offset = 128;

    if (nextRow + dashheight > height) {
        Log::Warning(Event::OpenGL, "line atlas bitmap overflow");
        return LinePatternPos();
    }

    float length = 0;
    for (const float part : dasharray) {
        length += part;
    }

    float stretch = width / length;
    float halfWidth = stretch * 0.5;
    // If dasharray has an odd length, both the first and last parts
    // are dashes and should be joined seamlessly.
    bool oddLength = dasharray.size() % 2 == 1;

    for (int y = -n; y <= n; y++) {
        int row = nextRow + n + y;
        int index = width * row;

        float left = 0;
        float right = dasharray[0];
        unsigned int partIndex = 1;

        if (oddLength) {
            left -= dasharray.back();
        }

        for (int x = 0; x < width; x++) {

            while (right < x / stretch) {
                left = right;
                right = right + dasharray[partIndex];

                if (oddLength && partIndex == dasharray.size() - 1) {
                    right += dasharray.front();
                }

                partIndex++;
            }

            float distLeft = fabs(x - left * stretch);
            float distRight = fabs(x - right * stretch);
            float dist = fmin(distLeft, distRight);
            bool inside = (partIndex % 2) == 1;
            int signedDistance;

            if (patternCap == LinePatternCap::Round) {
                float distMiddle = n ? (float)y / n * (halfWidth + 1) : 0;
                if (inside) {
                    float distEdge = halfWidth - fabs(distMiddle);
                    signedDistance = sqrt(dist * dist + distEdge * distEdge);
                } else {
                    signedDistance = halfWidth - sqrt(dist * dist + distMiddle * distMiddle);
                }

            } else {
                signedDistance = int((inside ? 1 : -1) * dist);
            }

            data[index + x] = fmax(0, fmin(255, signedDistance + offset));
        }
    }

    LinePatternPos position;
    position.y = (0.5 + nextRow + n) / height;
    position.height = (2.0 * n) / height;
    position.width = length;

    nextRow += dashheight;

    dirty = true;

    return position;
}