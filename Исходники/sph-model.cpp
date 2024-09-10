double sph_model::view_face(const double *M, int vw, int vh,
                            double ee, double ww, double nn, double ss, int j)
{
    double ne[3], a[3], e[3], A[4], E[4];    // North-east corner
    double nw[3], b[3], f[3], B[4], F[4];    // North-west corner
    double se[3], c[3], g[3], C[4], G[4];    // South-east corner
    double sw[3], d[3], h[3], D[4], H[4];    // South-west corner
    
    vnormalize(ne, cube_v[cube_i[j][0]]);
    vnormalize(nw, cube_v[cube_i[j][1]]);
    vnormalize(se, cube_v[cube_i[j][2]]);
    vnormalize(sw, cube_v[cube_i[j][3]]);
    
    bislerp(a, ne, nw, se, sw, ee, nn);
    bislerp(b, ne, nw, se, sw, ww, nn);
    bislerp(c, ne, nw, se, sw, ee, ss);
    bislerp(d, ne, nw, se, sw, ww, ss);
    
    zoom(a, a);
    zoom(b, b);
    zoom(c, c);
    zoom(d, d);
    
    // Compute the maximum extent due to bulge.

    double v[3];
    
    v[0] = a[0] + b[0] + c[0] + d[0];
    v[1] = a[1] + b[1] + c[1] + d[1];
    v[2] = a[2] + b[2] + c[2] + d[2];
    
    double k = vlen(v) / vdot(a, v);

    // Compute the outer corners of the bulge bound.
    
    vmul(e, a, k);
    vmul(f, b, k);
    vmul(g, c, k);
    vmul(h, d, k);

    // Compute W and reject any volume on the far side of the singularity.
    
    A[3] = M[ 3] * a[0] + M[ 7] * a[1] + M[11] * a[2] + M[15];
    B[3] = M[ 3] * b[0] + M[ 7] * b[1] + M[11] * b[2] + M[15];
    C[3] = M[ 3] * c[0] + M[ 7] * c[1] + M[11] * c[2] + M[15];
    D[3] = M[ 3] * d[0] + M[ 7] * d[1] + M[11] * d[2] + M[15];
    E[3] = M[ 3] * e[0] + M[ 7] * e[1] + M[11] * e[2] + M[15];
    F[3] = M[ 3] * f[0] + M[ 7] * f[1] + M[11] * f[2] + M[15];
    G[3] = M[ 3] * g[0] + M[ 7] * g[1] + M[11] * g[2] + M[15];
    H[3] = M[ 3] * h[0] + M[ 7] * h[1] + M[11] * h[2] + M[15];

    if (A[3] <= 0 && B[3] <= 0 && C[3] <= 0 && D[3] <= 0 &&
        E[3] <= 0 && F[3] <= 0 && G[3] <= 0 && H[3] <= 0)
        return 0;

    // Compute Z and apply the near and far clipping planes.

    A[2] = M[ 2] * a[0] + M[ 6] * a[1] + M[10] * a[2] + M[14];
    B[2] = M[ 2] * b[0] + M[ 6] * b[1] + M[10] * b[2] + M[14];
    C[2] = M[ 2] * c[0] + M[ 6] * c[1] + M[10] * c[2] + M[14];
    D[2] = M[ 2] * d[0] + M[ 6] * d[1] + M[10] * d[2] + M[14];
    E[2] = M[ 2] * e[0] + M[ 6] * e[1] + M[10] * e[2] + M[14];
    F[2] = M[ 2] * f[0] + M[ 6] * f[1] + M[10] * f[2] + M[14];
    G[2] = M[ 2] * g[0] + M[ 6] * g[1] + M[10] * g[2] + M[14];
    H[2] = M[ 2] * h[0] + M[ 6] * h[1] + M[10] * h[2] + M[14];
    
    if (A[2] >  A[3] && B[2] >  B[3] && C[2] >  C[3] && D[2] >  D[3] &&
        E[2] >  E[3] && F[2] >  F[3] && G[2] >  G[3] && H[2] >  H[3])
        return 0;
    if (A[2] < -A[3] && B[2] < -B[3] && C[2] < -C[3] && D[2] < -D[3] &&
        E[2] < -E[3] && F[2] < -F[3] && G[2] < -G[3] && H[2] < -H[3])
        return 0;

    // Compute Y and apply the bottom and top clipping planes.

    A[1] = M[ 1] * a[0] + M[ 5] * a[1] + M[ 9] * a[2] + M[13];
    B[1] = M[ 1] * b[0] + M[ 5] * b[1] + M[ 9] * b[2] + M[13];
    C[1] = M[ 1] * c[0] + M[ 5] * c[1] + M[ 9] * c[2] + M[13];
    D[1] = M[ 1] * d[0] + M[ 5] * d[1] + M[ 9] * d[2] + M[13];
    E[1] = M[ 1] * e[0] + M[ 5] * e[1] + M[ 9] * e[2] + M[13];
    F[1] = M[ 1] * f[0] + M[ 5] * f[1] + M[ 9] * f[2] + M[13];
    G[1] = M[ 1] * g[0] + M[ 5] * g[1] + M[ 9] * g[2] + M[13];
    H[1] = M[ 1] * h[0] + M[ 5] * h[1] + M[ 9] * h[2] + M[13];
    
    if (A[1] >  A[3] && B[1] >  B[3] && C[1] >  C[3] && D[1] >  D[3] &&
        E[1] >  E[3] && F[1] >  F[3] && G[1] >  G[3] && H[1] >  H[3])
        return 0;
    if (A[1] < -A[3] && B[1] < -B[3] && C[1] < -C[3] && D[1] < -D[3] &&
        E[1] < -E[3] && F[1] < -F[3] && G[1] < -G[3] && H[1] < -H[3])
        return 0;

    // Compute X and apply the left and right clipping planes.

    A[0] = M[ 0] * a[0] + M[ 4] * a[1] + M[ 8] * a[2] + M[12];
    B[0] = M[ 0] * b[0] + M[ 4] * b[1] + M[ 8] * b[2] + M[12];
    C[0] = M[ 0] * c[0] + M[ 4] * c[1] + M[ 8] * c[2] + M[12];
    D[0] = M[ 0] * d[0] + M[ 4] * d[1] + M[ 8] * d[2] + M[12];
    E[0] = M[ 0] * e[0] + M[ 4] * e[1] + M[ 8] * e[2] + M[12];
    F[0] = M[ 0] * f[0] + M[ 4] * f[1] + M[ 8] * f[2] + M[12];
    G[0] = M[ 0] * g[0] + M[ 4] * g[1] + M[ 8] * g[2] + M[12];
    H[0] = M[ 0] * h[0] + M[ 4] * h[1] + M[ 8] * h[2] + M[12];
    
    if (A[0] >  A[3] && B[0] >  B[3] && C[0] >  C[3] && D[0] >  D[3] &&
        E[0] >  E[3] && F[0] >  F[3] && G[0] >  G[3] && H[0] >  H[3])
        return 0;
    if (A[0] < -A[3] && B[0] < -B[3] && C[0] < -C[3] && D[0] < -D[3] &&
        E[0] < -E[3] && F[0] < -F[3] && G[0] < -G[3] && H[0] < -H[3])
        return 0;

    // Compute the length of the longest visible edge, in pixels.

//  return max(length(A, B, vw, vh),
//             length(C, D, vw, vh),
//             length(A, C, vw, vh),
//             length(B, D, vw, vh));
    return std::max(max(length(A, B, vw, vh),
                        length(C, D, vw, vh),
                        length(A, C, vw, vh),
                        length(B, D, vw, vh)),
                    max(length(E, F, vw, vh),
                        length(G, H, vw, vh),
                        length(E, G, vw, vh),
                        length(F, H, vw, vh)));
}