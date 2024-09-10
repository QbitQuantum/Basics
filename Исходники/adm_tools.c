void adm_decouple_d(const adm_dwt_band_t_d *ref, const adm_dwt_band_t_d *dis, const adm_dwt_band_t_d *r, const adm_dwt_band_t_d *a, int w, int h, int ref_stride, int dis_stride, int r_stride, int a_stride)
{
#ifdef ADM_OPT_AVOID_ATAN
    const double cos_1deg_sq = cos(1.0 * M_PI / 180.0) * cos(1.0 * M_PI / 180.0);
#endif
    const double eps = 1e-30;

    int ref_px_stride = ref_stride / sizeof(double);
    int dis_px_stride = dis_stride / sizeof(double);
    int r_px_stride = r_stride / sizeof(double);
    int a_px_stride = a_stride / sizeof(double);

    double oh, ov, od, th, tv, td;
    double kh, kv, kd, tmph, tmpv, tmpd;
#ifdef ADM_OPT_AVOID_ATAN
    double ot_dp, o_mag_sq, t_mag_sq;
#else
    double oa, ta, diff;
#endif
    int angle_flag;
    int i, j;

    for (i = 0; i < h; ++i) {
        for (j = 0; j < w; ++j) {
            oh = ref->band_h[i * ref_px_stride + j];
            ov = ref->band_v[i * ref_px_stride + j];
            od = ref->band_d[i * ref_px_stride + j];
            th = dis->band_h[i * dis_px_stride + j];
            tv = dis->band_v[i * dis_px_stride + j];
            td = dis->band_d[i * dis_px_stride + j];

            kh = DIVD(th, oh + eps);
            kv = DIVD(tv, ov + eps);
            kd = DIVD(td, od + eps);

            kh = kh < 0.0 ? 0.0 : (kh > 1.0 ? 1.0 : kh);
            kv = kv < 0.0 ? 0.0 : (kv > 1.0 ? 1.0 : kv);
            kd = kd < 0.0 ? 0.0 : (kd > 1.0 ? 1.0 : kd);

            tmph = kh * oh;
            tmpv = kv * ov;
            tmpd = kd * od;
#ifdef ADM_OPT_AVOID_ATAN
            /* Determine if angle between (oh,ov) and (th,tv) is less than 1 degree.
             * Given that u is the angle (oh,ov) and v is the angle (th,tv), this can
             * be done by testing the inequvality.
             *
             * { (u.v.) >= 0 } AND { (u.v)^2 >= cos(1deg)^2 * ||u||^2 * ||v||^2 }
             *
             * Proof:
             *
             * cos(theta) = (u.v) / (||u|| * ||v||)
             *
             * IF u.v >= 0 THEN
             *   cos(theta)^2 = (u.v)^2 / (||u||^2 * ||v||^2)
             *   (u.v)^2 = cos(theta)^2 * ||u||^2 * ||v||^2
             *
             *   IF |theta| < 1deg THEN
             *     (u.v)^2 >= cos(1deg)^2 * ||u||^2 * ||v||^2
             *   END
             * ELSE
             *   |theta| > 90deg
             * END
             */
            ot_dp = oh * th + ov * tv;
            o_mag_sq = oh * oh + ov * ov;
            t_mag_sq = th * th + tv * tv;

            angle_flag = (ot_dp >= 0.0) && (ot_dp * ot_dp >= cos_1deg_sq * o_mag_sq * t_mag_sq);
#else
            oa = atan(DIVD(ov, oh + eps));
            ta = atan(DIVD(tv, th + eps));

            if (oh < 0.0)
                oa += M_PI;
            if (th < 0.0)
                ta += M_PI;

            diff = fabs(oa - ta) * 180.0 / M_PI;
            angle_flag = diff < 1.0;
#endif
            if (angle_flag) {
                tmph = th;
                tmpv = tv;
                tmpd = td;
            }

            r->band_h[i * r_px_stride + j] = tmph;
            r->band_v[i * r_px_stride + j] = tmpv;
            r->band_d[i * r_px_stride + j] = tmpd;

            a->band_h[i * a_px_stride + j] = th - tmph;
            a->band_v[i * a_px_stride + j] = tv - tmpv;
            a->band_d[i * a_px_stride + j] = td - tmpd;
        }
    }
}