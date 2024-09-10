void Heightfield::fillProperties(ParsedBlock& pb)
{
    Bitmap* bmp = NULL;
    if (!pb.getBitmapFileProp("file", &bmp, filename)) pb.requiredProp("file");
    W = bmp->getWidth();
    H = bmp->getHeight();
    blur = 0;
    pb.getDoubleProp("blur", &blur);
    heights = new float[W * H];
    float minY = LARGE_FLOAT, maxY = -LARGE_FLOAT;
    // do we have blur? if no, just fetch the source image and store it:
    if (blur <= 0) {
        for (int y = 0; y < H; y++)
            for (int x = 0; x < W; x++) {
                float h = bmp->getPixel(x, y).intensity();
                heights[y * W + x] = h;
                minY = min(minY, h);
                maxY = max(maxY, h);
            }
    } else {
        // We have blur...
        // 1) convert image to greyscale (if not already):
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                float f = bmp->getPixel(x, y).intensity();
                bmp->setPixel(x, y, Color(f, f, f));
            }
        }
        // 2) calculate the gaussian coefficients, see http://en.wikipedia.org/wiki/Gaussian_blur
        static float gauss[128][128];
        int R = min(128, nearestInt(float(3 * blur)));
        for (int y = 0; y < R; y++)
            for (int x = 0; x < R; x++)
                gauss[y][x] = float(exp(-(sqr(x) + sqr(y))/(2 * sqr(blur))) / (2 * PI * sqr(blur)));
        // 3) apply gaussian blur with the specified number of blur units:
        // (this is potentially slow for large blur radii)
        for (int y = 0; y < H; y++) {
            for (int x = 0; x < W; x++) {
                float sum = 0;
                for (int dy = -R + 1; dy < R; dy++)
                    for (int dx = -R + 1; dx < R; dx++)
                        sum += gauss[abs(dy)][abs(dx)] * bmp->getPixel(x + dx, y + dy).r;
                heights[y * W + x] = sum;
                minY = min(minY, sum);
                maxY = max(maxY, sum);
            }
        }
    }
    // set the bounding box. minY and maxY are the bbox extents along Y and are calculated
    // from the heights[] array.
    bbox.vmin = Vector(0, minY, 0);
    bbox.vmax = Vector(W, maxY, H);

    // calculate the maxH array. maxH(x, y) = max(H(x, y), H(x + 1, y), H(x, y + 1), H(x + 1, y+1))
    maxH = new float[W*H];
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++) {
            float& maxH = this->maxH[y * W + x];
            maxH = heights[y * W + x];
            if (x < W - 1) maxH = max(maxH, heights[y * W + x + 1]);
            if (y < H - 1) {
                maxH = max(maxH, heights[(y + 1) * W + x]);
                if (x < W - 1)
                    maxH = max(maxH, heights[(y + 1) * W + x + 1]);
            }
        }
    // precalculate the normals at each integer point. We create normals by doing two forward differences
    // on the height along x and y at each point and using the cross product of these differences to
    // obtain the normal vector
    normals = new Vector[W * H];
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++) {
            float h0 = heights[y * W + x];
            float hdx = heights[y * W + min(W - 1, x + 1)];
            float hdy = heights[min(H - 1, y + 1) * W + x];
            Vector vdx = Vector(1, hdx - h0, 0); // forward difference along X
            Vector vdy = Vector(0, hdy - h0, 1); // forward difference along Z
            Vector norm = vdy ^ vdx;
            norm.normalize();
            normals[y * W + x] = norm;
        }
    useOptimization = false;
    pb.getBoolProp("useOptimization", &useOptimization);
    if (!disableAcceleratedStructures && useOptimization) {
        Uint32 clk = SDL_GetTicks();
        buildStruct();
        clk = SDL_GetTicks() - clk;
        printf("Heightfield acceleration struct built in %.3lfs\n", clk / 1000.0);
    }
}