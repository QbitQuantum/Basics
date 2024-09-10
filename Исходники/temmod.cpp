TEMmod::TEMmod(PClip c, double thy, double thc, int tp, int chroma, int lnk,
               bool inv, float sc, IScriptEnvironment* env)
    : GenericVideoFilter(c), link(lnk), invert(inv), type(tp), scale(sc)
{
    if (!vi.IsPlanar()) {
        env->ThrowError("TEMmod: Planar format only.");
    }
    if (vi.IsY8()) {
        link = 0;
        chroma = 0;
    }

    process[0] = 1; process[1] = process[2] = chroma;

    double th[] = {thy, thc};
    for (int i = 0; i < 2; i++) {
        double d;
        if (type == 1) {
            d = th[i] * th[i] * 4 + 0.5;
        } else if (type == 2) {
            d = th[i] * th[i] * 10000 + 0.5;
        } else if (type == 3) {
            d = th[i] * 2 + 0.5;
        } else if (type == 4) {
            d = th[i] * 100 / 3.0 + 0.5;
        } else {
            d = th[i] * 4 + 0.5;
        }
        threshold[i] = static_cast<int>(d);
    }
    threshold[2] = threshold[1];

    if (threshold[0] == 0 || threshold[1] == 0) {
        link = 0;
    }

    if (type == 1) {
        calc_map = calc_maps[threshold[0] > 0 ? 1 : 0];
    } else if (type == 2) {
        calc_map = calc_maps[2 + (threshold[0] > 0 ? 1 : 0)];
    } else {
        calc_map = calc_maps[type + 1];
    }

    const link_planes_func* links = link == 1 ? link_y_to_uv : link_all;
    if (vi.IsYV24()) {
        link_planes = links[0];
    } else if (vi.IsYV16()) {
        link_planes = links[1];
    } else if (vi.IsYV12()) {
        link_planes = links[2];
    } else {
        link_planes = links[3];
    }

    buff_pitch = ((vi.width + 47) / 16) * 16;
    buff = (uint8_t*)_aligned_malloc(buff_pitch * (type * 2 + 1), 16);
    if (!buff) {
        env->ThrowError("TEMmod: failed to allocate buffer.");
    }
}