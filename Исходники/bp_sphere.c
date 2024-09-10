static int intersect (unsigned int prim_id , const ray_t *ray, intersect_t *isect) {
    vector_t dest;
    double B, C, D;
    const float EPSILON = 0.003;

    SUB (dest, ray->orig, get_sphere_center (prim_id));
    B = DOT (dest, ray->dir);
    C = DOT (dest, dest);
    C -= get_sphere_radius (prim_id) * get_sphere_radius (prim_id);

    D = B*B  - C;

    if (D > 0) {
        const double sqrt_D = sqrt (D),
                     t0 = -B - sqrt_D,
                     t1 = -B + sqrt_D;

        if (t0 > EPSILON && t0 <= isect->t) {
            isect->t = t0;
            return 1;
        }
        else if (t1 > EPSILON && t1 <= isect->t) {
            isect->t = t1;
            return 1;
        }
        return 0;
    }
    return 0;
}