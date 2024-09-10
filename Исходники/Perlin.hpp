        uint getHeight(uint x, uint y, uint z) {
                uint cacheIdx = Morton::encode2(x, y);
                float scalef = exp2f(scale);
                if (z == 0) {
                        uint height = (Perlin::perlinNoise2d(x/scalef, y/scalef) + 2.0f) * scalef/2.0f;
                        if (cachedHeights.size() <= cacheIdx) {
                                cachedHeights.resize(cacheIdx + 1);
                        }
                        cachedHeights[cacheIdx] = height;
                        return height;
                }
                else {
                        return cachedHeights[cacheIdx];
                }

        }