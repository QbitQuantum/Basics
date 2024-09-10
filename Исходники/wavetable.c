static smpl_t interp_2(fvec_t *input, smpl_t pos) {
    uint_t idx = (uint_t)FLOOR(pos);
    smpl_t frac = pos - (smpl_t)idx;
    smpl_t a = input->data[idx];
    smpl_t b = input->data[idx + 1];
    return a + frac * ( b - a );
}