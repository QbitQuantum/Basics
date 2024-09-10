void compute_tangents_C(double *tangents, double *y, double *energies,
                        int n_dofs_image, int n_images
                        ) {

    /* Compute the tangents for every degree of freedom of a NEBM band,
     * following the rules from Henkelman and Jonsson [Henkelman et al.,
     * Journal of Chemical Physics 113, 22 (2000)]
     *
     * We assume we have n_images images in the band, which is represented by
     * the *y array. the *y array has the structure

     *      y = [ theta0_0 phi0_0 theta0_1, phi0_1  ... phi0_(n_dofs_images),
     *            theta1_0 phi1_0 theta1_1, phi1_1  ... phi1_(n_dofs_images),
     *            ...
     *            theta(n_images -1)_0 phi(n_images -1)_0  ... phi(n_images - 1)_(n_dofs_images)]

     * where (theta(i)_j, phi(i)_j) are the spherical coordinates of the j-th
     * spin in the i-th image of the band. Thus we have n_dofs_image spins per
     * image. Images at the extremes, i=0,(n_images-1), are kept fixed, thus we
     * do not compute the tangents for them.
     *
     * The *energies array contains the energy of every image, thus its length
     * is n_images.
     *
     * The tangents have the same length of an image, thus the *tangents array
     * has length (n_images * n_dofs_image), just as the *y array, and we keep
     * the first and last n_dofs_image components as zero (they correspond to
     * the extreme images)
     *
     * To compute the tangents, we use the t+ and t- vectors. Denoting the i-th
     * image by Y_i, these vectors are defined by

     *      t+_i = Y_(i+1) - Y_i          t-_i = Y_i - Y_(i-1)

     * Then, when an image is at a saddle point, we have, using the energies
     * of the neighbouring images,:

     *               __
     *      t_i  =   |   t+_i    if  E_(i+1) > E_i > E_(i-1)
     *              <
     *               |_  t-_i    if  E_(i+1) < E_i < E_(i-1)

     * Otherwise, if we have a maximum or a minimum  (E_(i+1) < E_i > E_(i-1)
     * or E_(i+1) > E_i < E_(i-1) respectively), we use an average of the
     * vectors:
     *
                     __
     *      t_i  =   |   t+_i * dE_max + t-_i * dE_min  if  E_(i+1) > E_(i-1)
     *              <
     *               |_  t+_i * dE_min + t-_i * dE_max  if  E_(i+1) < E_(i-1)

     * where dE_max = max( |E_(i+1) - E_i|, |E_i - E_(i-1)|) and
     *       dE_min = min( |E_(i+1) - E_i|, |E_i - E_(i-1)|)
     *
     */

    int i, j;

    // Index where the components of an image start in the *y array,
    int im_idx;
    // And also the previous and next images:
    int next_im_idx, prev_im_idx;

    double *t_plus;
    double *t_minus;
    t_plus  = malloc(n_dofs_image * sizeof(double));
    t_minus = malloc(n_dofs_image * sizeof(double));

    double deltaE_plus, deltaE_minus;
    double deltaE_MAX, deltaE_MIN;

    for(i = 1; i < n_images - 1; i++){

        im_idx = i * (n_dofs_image);
        next_im_idx = (i + 1) * (n_dofs_image);
        prev_im_idx = (i - 1) * (n_dofs_image);

        // Tangents of the i-th image
        double * t = &tangents[im_idx];

        // Compute the t+ and t- vectors for the i-th image of the band, which
        // is given by the difference of the Y_i image with its neighbours
        for(j = 0; j < n_dofs_image; j++){
            t_plus[j]  = y[next_im_idx + j] - y[im_idx + j];
            t_minus[j] = y[im_idx + j]      - y[prev_im_idx + j];
        }

        // Similarly, compute the energy differences
        deltaE_plus  = energies[i + 1] - energies[i];
        deltaE_minus = energies[i]     - energies[i - 1];

        /* Now we follow Henkelman and Jonsson rules [Henkelman et al., Journal
         * of Chemical Physics 113, 22 (2000)] for the tangent directions
         * (remember that there is a tangent for every spin (degree of
         * freedom))
         *
         * The first two cases are straightforward: If the energy has a
         * positive (negative) slope, just make the difference between the spin
         * directions with respect to the right (left) image.
         *
         * The other case is when the image is an energy maximum, or minimum
         */

        /* ----------------------------------------------------------------- */

        if(deltaE_plus > 0 && deltaE_minus > 0) {
            for(j = 0; j < n_dofs_image; j++) t[j] = t_plus[j];
        }

        /* ----------------------------------------------------------------- */

        else if(deltaE_plus < 0 && deltaE_minus < 0) {
            for(j = 0; j < n_dofs_image; j++) t[j] = t_minus[j];
        }

        /* ----------------------------------------------------------------- */

        else {

            /* According to the energy of the neighbouring images, the tangent
             * of the i-th image will be a combination of the differences wrt
             * to the left and right images components weighted according to
             * the neighbours energies
             */
            deltaE_MAX = fmax(fabs(deltaE_plus), fabs(deltaE_minus));
            deltaE_MIN = fmin(fabs(deltaE_plus), fabs(deltaE_minus));

            if (energies[i + 1] > energies[i - 1]) {
                for(j = 0; j < n_dofs_image; j++) {
                    t[j] = t_plus[j] * deltaE_MAX + t_minus[j] * deltaE_MIN;
                }
            }

            else {
                for(j = 0; j < n_dofs_image; j++) {
                    t[j] = t_plus[j] * deltaE_MIN + t_minus[j] * deltaE_MAX;
                }
            }

        }

        /* ----------------------------------------------------------------- */

    } // Close loop in images
    free(t_plus);
    free(t_minus);
} // Close main function