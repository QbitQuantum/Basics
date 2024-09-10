static void print_bounds(zarray_t * vertices)
{
    // Approximate centroid: Just average all vertices, regardless of
    // the frequency they are referenced by an index
    float minMax[3][2] = {{FLT_MAX,-FLT_MAX},{FLT_MAX,-FLT_MAX},{FLT_MAX,-FLT_MAX}};
    for (int i = 0; i < zarray_size(vertices); i++) {
        float pt[3];
        zarray_get(vertices, i, &pt);

        // iterate over xyz coords
        for (int j = 0; j < 3; j++) {
            minMax[j][0] = fminf(pt[j], minMax[j][0]);
            minMax[j][1] = fmaxf(pt[j], minMax[j][1]);
        }
    }

    printf(" Object bounds: xyz [%.2f, %.2f][%.2f, %.2f][%.2f, %.2f]\n",
           minMax[0][0],minMax[0][1],
           minMax[1][0],minMax[1][1],
           minMax[2][0],minMax[2][1]);
}