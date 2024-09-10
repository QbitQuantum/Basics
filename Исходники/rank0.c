/* rank 2, in place, square transpose, tiled, buffered */
static void apply_ip_sq_tiledbuf(const plan *ego_, R *I, R *O)
{
     const P *ego = (const P *) ego_;
     UNUSED(O);
     transpose(ego->d, ego->rnk, ego->vl, I, X(transpose_tiledbuf));
}