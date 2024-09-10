fastf_t
texture_perlin_omega(struct texture_perlin_s *P, vect_t V)
{
    vect_t q;
    fastf_t r0[3], r1[3], sy, sz, a, b, c, d, t, u, v;
    int b0[3], b1[3], b00, b10, b01, b11;
    int i, j;


    for (i = 0; i < 3; i++) {
	t = V[i] + N;
	b0[i] = ((int)t) & BM;
	b1[i] = (b0[i]+1) & BM;
	r0[i] = t - (int)t;
	r1[i] = r0[i] - 1.0;
    }

    i = P->PV[b0[0]];
    j = P->PV[b1[0]];

    b00 = P->PV[i + b0[1]];
    b10 = P->PV[j + b0[1]];
    b01 = P->PV[i + b1[1]];
    b11 = P->PV[j + b1[1]];

    t = S_CURVE(r0[0]);
    sy = S_CURVE(r0[1]);
    sz = S_CURVE(r0[2]);

    VMOVE(q, P->RV[b00 + b0[2]]);
    u = AT3(r0[0], r0[1], r0[2]);
    VMOVE(q, P->RV[b10 + b0[2]]);
    v = AT3(r1[0], r0[1], r0[2]);
    a = LERP(t, u, v);

    VMOVE(q, P->RV[b01 + b0[2]]);
    u = AT3(r0[0], r1[1], r0[2]);
    VMOVE(q, P->RV[b11 + b0[2]]);
    v = AT3(r1[0], r1[1], r0[2]);
    b = LERP(t, u, v);

    c = LERP(sy, a, b);

    VMOVE(q, P->RV[b00 + b1[2]]);
    u = AT3(r0[0], r0[1], r1[2]);
    VMOVE(q, P->RV[b10 + b1[2]]);
    v = AT3(r1[0], r0[1], r1[2]);
    a = LERP(t, u, v);

    VMOVE(q, P->RV[b01 + b1[2]]);
    u = AT3(r0[0], r1[1], r1[2]);
    VMOVE(q, P->RV[b11 + b1[2]]);
    v = AT3(r1[0], r1[1], r1[2]);
    b = LERP(t, u, v);

    d = LERP(sy, a, b);

    return LERP(sz, c, d);
}