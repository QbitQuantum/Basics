CoglVertexP3*
crank_make_v_p3_sphere_uv (const guint  uc,
                           const guint  vc,
                           guint       *len)
{
    guint mlen;

    CoglVertexP3 *vertices;

    CoglVertexP3 *sides;

    gfloat vang_inc = G_PI / (vc + 1);
    gfloat vang_base = - G_PI_2 + vang_inc;

    gfloat uang_inc =  G_PI * 2 / uc;

    guint top_vert;

    guint j;
    guint i;


    mlen = 2 + uc * vc;
    vertices = g_new (CoglVertexP3, mlen);

    sides = vertices + 1;

    vertices[0].x = 0;
    vertices[0].y = 0;
    vertices[0].z = -1;

    for (j = 0; j < vc; j++)
    {
        CoglVertexP3 *row = sides + (uc * j);

        gfloat vang = fmaf (j, vang_inc, vang_base);
        gfloat vcos = cosf (vang);
        gfloat vsin = sinf (vang);

        for (i = 0; i < uc; i++)
        {
            gfloat uang = i * uang_inc;
            gfloat ucos = cosf (uang);
            gfloat usin = sinf (uang);

            row[i].x = ucos * vcos;
            row[i].y = usin * vcos;
            row[i].z = vsin;
        }
    }

    top_vert = uc * vc + 1;

    vertices[top_vert].x = 0;
    vertices[top_vert].y = 0;
    vertices[top_vert].z = -1;


    if (len != NULL)
        *len = mlen;

    return vertices;
}