void eigen_hessian_3d(float* dst_e0, float* dst_e1, float* dst_e2, const float* src, size_t w, size_t h, size_t d, bool ref) {
    auto v = [=](size_t x, size_t y, size_t z) -> const float& {
        return src[(z*h + y)*w + x];
    };
    auto ev = [=](float* vol, size_t x, size_t y, size_t z) -> float& { return vol[(z*h + y)*w + x]; };
    for (size_t z=1; z<d-1; ++z) {
        for (size_t y=1; y<h-1; ++y) {
            auto ref_pixel = [=](size_t x) {
                const float f = 2.0f*v(x, y, z);
                const float f_xx = v(x + 1, y, z) + v(x - 1, y, z) - f;
                const float f_yy = v(x, y + 1, z) + v(x, y - 1, z) - f;
                const float f_zz = v(x, y, z + 1) + v(x, y, z - 1) - f;
                const float f_xy = v(x + 1, y + 1, z) + v(x - 1, y - 1, z) - v(x - 1, y + 1, z) - v(x + 1, y - 1, z);
                const float f_yz = v(x, y + 1, z + 1) + v(x, y - 1, z - 1) - v(x, y - 1, z + 1) - v(x, y + 1, z - 1);
                const float f_zx = v(x + 1, y, z + 1) + v(x - 1, y, z - 1) - v(x + 1, y, z - 1) - v(x - 1, y, z + 1);
                float m[9] = {
                    f_xx, f_xy, f_zx,
                    f_xy, f_yy, f_yz,
                    f_zx, f_yz, f_zz
                };
                float eigen[3];
                cubic_eigen<newton_iter>(m, eigen);
                ev(dst_e0, x, y, z) = eigen[0];
                ev(dst_e1, x, y, z) = eigen[1];
                ev(dst_e2, x, y, z) = eigen[2];
            };
            auto simd_pixel = [=](size_t x) {
                __m128 vf2 = _mm_loadu_ps((const float*)&src[(z*h + y)*w + x]);
                vf2 = _mm_add_ps(vf2, vf2);
                __m128 vfxm1 = _mm_loadu_ps((const float*)&src[(z*h + y)*w + x - 1]);
                __m128 vfxp1 = _mm_loadu_ps((const float*)&src[(z*h + y)*w + x + 1]);
                __m128 vfym1 = _mm_loadu_ps((const float*)&src[(z*h + y - 1)*w + x]);
                __m128 vfyp1 = _mm_loadu_ps((const float*)&src[(z*h + y + 1)*w + x]);
                __m128 vfzm1 = _mm_loadu_ps((const float*)&src[((z - 1)*h + y)*w + x]);
                __m128 vfzp1 = _mm_loadu_ps((const float*)&src[((z + 1)*h + y)*w + x]);
                __m128 vfxx = _mm_sub_ps(_mm_add_ps(vfxm1, vfxp1), vf2);
                __m128 vfyy = _mm_sub_ps(_mm_add_ps(vfym1, vfyp1), vf2);
                __m128 vfzz = _mm_sub_ps(_mm_add_ps(vfzm1, vfzp1), vf2);
                __m128 vfxm1ym1 = _mm_loadu_ps((const float*)&src[(z*h + y - 1)*w + x - 1]);
                __m128 vfxp1ym1 = _mm_loadu_ps((const float*)&src[(z*h + y - 1)*w + x + 1]);
                __m128 vfxm1yp1 = _mm_loadu_ps((const float*)&src[(z*h + y + 1)*w + x - 1]);
                __m128 vfxp1yp1 = _mm_loadu_ps((const float*)&src[(z*h + y + 1)*w + x + 1]);
                __m128 vfym1zm1 = _mm_loadu_ps((const float*)&src[((z - 1)*h + y - 1)*w + x]);
                __m128 vfyp1zm1 = _mm_loadu_ps((const float*)&src[((z - 1)*h + y + 1)*w + x]);
                __m128 vfym1zp1 = _mm_loadu_ps((const float*)&src[((z + 1)*h + y - 1)*w + x]);
                __m128 vfyp1zp1 = _mm_loadu_ps((const float*)&src[((z + 1)*h + y + 1)*w + x]);
                __m128 vfzm1xm1 = _mm_loadu_ps((const float*)&src[((z - 1)*h + y)*w + x - 1]);
                __m128 vfzp1xm1 = _mm_loadu_ps((const float*)&src[((z + 1)*h + y)*w + x - 1]);
                __m128 vfzm1xp1 = _mm_loadu_ps((const float*)&src[((z - 1)*h + y)*w + x + 1]);
                __m128 vfzp1xp1 = _mm_loadu_ps((const float*)&src[((z + 1)*h + y)*w + x + 1]);
                __m128 vfxy = _mm_sub_ps(_mm_add_ps(vfxp1yp1, vfxm1ym1), _mm_add_ps(vfxm1yp1, vfxp1ym1));
                __m128 vfyz = _mm_sub_ps(_mm_add_ps(vfyp1zp1, vfym1zm1), _mm_add_ps(vfym1zp1, vfyp1zm1));
                __m128 vfzx = _mm_sub_ps(_mm_add_ps(vfzp1xp1, vfzm1xm1), _mm_add_ps(vfzm1xp1, vfzp1xm1));
                __m128 ve0, ve1, ve2;
                cubic_eigen<newton_iter>(vfxx, vfxy, vfzx, vfyy, vfyz, vfzz, ve0, ve1, ve2);
                _mm_storeu_ps((float*)&dst_e0[(z*h + y)*w + x], ve0);
                _mm_storeu_ps((float*)&dst_e1[(z*h + y)*w + x], ve1);
                _mm_storeu_ps((float*)&dst_e2[(z*h + y)*w + x], ve2);
            };
            size_t x = 1;
            for (; x<std::min<size_t>(w-1, 4); ++x)
                ref_pixel(x);
            if (!ref) {
                for (; x<w-1-4; x+=4)
                    simd_pixel(x);
            }
            for (; x<w-1; ++x)
                ref_pixel(x);
        }
    }
}