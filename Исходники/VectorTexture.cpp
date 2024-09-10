    void VectorTexture::rasterizeGraphics(NSVGimage* svg, Filtering filtering, Wrap wrap, std::string filepath)
    {
        // TODO: Size depending on image scale. Better depend on rendering resolution

        uint width = (uint)(svg->width);
        uint height = (uint)(svg->height);
        const uint channelCount = 4;

        // Create rasterizer
        NSVGrasterizer* rast = nsvgCreateRasterizer();

        // Prepare memory for image
        std::vector<uchar> image;
        image.resize(width * height * channelCount);

        // Rasterize
        nsvgRasterize(rast, svg, 0, 0, 1, image.data(), width, height, width * channelCount);

        // Flip image
        std::vector<uchar> copyImage(image);

        // Go over lines
        for (uint i = 0; i < height; i++)
        {
            // Go over columns
            for (uint j = 0; j < width; j++)
            {
                // Go over channels
                for (uint k = 0; k < channelCount; k++)
                {
                    image[i * width * channelCount + j * channelCount + k] = copyImage[(height - 1 - i) * width * channelCount + j * channelCount + k];
                }
            }
        }

        // Create OpenGL from image
        createOpenGLTexture(image, filtering, wrap, width, height, channelCount, filepath);

        // Delete NanoSVG stuff
        nsvgDeleteRasterizer(rast);
    }