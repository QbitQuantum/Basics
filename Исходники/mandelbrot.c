void render(uchar* image,
            uint width, uint height,
            uint max_iterations,
            float x_scale,
            float y_scale,
            float x_adjust,
            float y_adjust)
{
    for (uint x_dim = 0; x_dim < width; x_dim++) {
        for (uint y_dim = 0; y_dim < height; y_dim++) {
            uint index = BYTES_PER_PIXEL * (width * y_dim + x_dim);
            float x_origin = ((float) x_dim/width)*x_scale - x_adjust;
            float y_origin = ((float) y_dim/width)*y_scale - y_adjust;

            float x = 0.0;
            float y = 0.0;
            uint iteration = 0;

            // Escape time algorithm
            while(x*x + y*y < LIMIT && iteration < max_iterations) {
                float xtemp = x*x - y*y + x_origin;
                y = 2*x*y + y_origin;
                x = xtemp;
                iteration++;
            }

            if (iteration == max_iterations) {
                image[index    ] = 0;
                image[index + 1] = 0;
                image[index + 2] = 0;
                image[index + 3] = 0;
            }
            else {
                // Continous coloring
                // Computes the color as a linear interpolation of surrounding points
                // smoothing the color transition.
                float zn  = sqrt(x*x + y*y);
                float nu  = log10f(log10f(zn) / log10f(2)) / log10f(2);
                float itr = ((float) iteration) + 1 - nu;
                float t   = fmodf(itr, 1.0);
                iteration = (uint) itr;
                uint color1 = iteration;
                uint color2 = iteration+1;

                // Assign RGB values by multiplying the iteration count by a even multiples.
                // Should replace this with a predefined colormap.
                image[index    ] = 1;
                image[index + 1] = ((uint) LERP(color1, color2, t)*2) % max_iterations;
                image[index + 2] = ((uint) LERP(color1, color2, t)*4) % max_iterations;
                image[index + 3] = ((uint) LERP(color1, color2, t)*6) % max_iterations;
            }
        }
    }
}