HRESULT D3DVertexCacher::FillParallelogramAA(float fx11, float fy11,
                                             float dx21, float dy21,
                                             float dx12, float dy12)
{
    HRESULT res;
    DECLARE_MATRIX(om);

    GET_INVERTED_MATRIX(om, fx11, fy11, dx21, dy21, dx12, dy12,
                        return D3D_OK);

    if (SUCCEEDED(res = EnsureCapacity(D3DPT_TRIANGLELIST, 2*3))) {
        float px = fx11, py = fy11;
        float pw = 0.0f, ph = 0.0f;
        ADJUST_PGRAM(px, dx21, pw);
        ADJUST_PGRAM(py, dy21, ph);
        ADJUST_PGRAM(px, dx12, pw);
        ADJUST_PGRAM(py, dy12, ph);
        float px1 = floor(px);
        float py1 = floor(py);
        float px2 = ceil(px + pw);
        float py2 = ceil(py + ph);
        float u11, v11, u12, v12, u21, v21, u22, v22;
        TRANSFORM(om, u11, v11, px1, py1);
        TRANSFORM(om, u21, v21, px2, py1);
        TRANSFORM(om, u12, v12, px1, py2);
        TRANSFORM(om, u22, v22, px2, py2);
        ADD_TRIANGLE_XYUVUVC(px1, py1, px2, py1, px1, py2,
                             u11, v11, u21, v21, u12, v12,
                             5.0, 5.0, 6.0, 5.0, 5.0, 6.0,
                             color);
        ADD_TRIANGLE_XYUVUVC(px1, py2, px2, py1, px2, py2,
                             u12, v12, u21, v21, u22, v22,
                             5.0, 6.0, 6.0, 5.0, 6.0, 6.0,
                             color);
    }
    return res;
}