void PaTriListSingle0(PA_STATE &pa, UINT slot, UINT triIndex, __m128 triverts[3])
{
    // We have 12 simdscalars contained within 3 simdvectors which
    // hold at least 8 triangles worth of data. We want to assemble a single
    // triangle with data in horizontal form.
    simdvector &a = PaGetSimdVector(pa, 0, slot);
    simdvector &b = PaGetSimdVector(pa, 1, slot);
    simdvector &c = PaGetSimdVector(pa, 2, slot);
    simdscalar tmp0;
    simdscalar tmp1;

    // Convert from vertical to horizontal.
    switch (triIndex)
    {
    case 0:
        // Grab vertex 0 from lane 0 and store it in tri[0]
        tmp0 = _mm256_unpacklo_ps(a.x, a.z);
        tmp1 = _mm256_unpacklo_ps(a.y, a.w);
        triverts[0] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 0);

        // Grab vertex 1 from lane 1 and store it in tri[1]
        tmp0 = _mm256_unpacklo_ps(a.x, a.z);
        tmp1 = _mm256_unpacklo_ps(a.y, a.w);
        triverts[1] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 0);

        // Grab vertex 2 from lane 2 and store it in tri[2]
        tmp0 = _mm256_unpackhi_ps(a.x, a.z);
        tmp1 = _mm256_unpackhi_ps(a.y, a.w);
        triverts[2] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 0);

        break;
    case 1:
        // Grab vertex 0 from lane 3 from 'a' and store it in tri[0]
        tmp0 = _mm256_unpackhi_ps(a.x, a.z);
        tmp1 = _mm256_unpackhi_ps(a.y, a.w);
        triverts[0] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 0);

        // Grab vertex 1 from lane 4 from 'a' and store it in tri[1]
        tmp0 = _mm256_unpacklo_ps(a.x, a.z);
        tmp1 = _mm256_unpacklo_ps(a.y, a.w);
        triverts[1] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 1);

        // Grab vertex 2 from lane 5 from 'a' and store it in tri[2]
        tmp0 = _mm256_unpacklo_ps(a.x, a.z);
        tmp1 = _mm256_unpacklo_ps(a.y, a.w);
        triverts[2] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 1);

        break;
    case 2:
        // Grab vertex 0 from lane 6 from 'a' and store it in tri[0]
        tmp0 = _mm256_unpackhi_ps(a.x, a.z);
        tmp1 = _mm256_unpackhi_ps(a.y, a.w);
        triverts[0] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 1);

        // Grab vertex 1 from lane 7 from 'a' and store it in tri[1]
        tmp0 = _mm256_unpackhi_ps(a.x, a.z);
        tmp1 = _mm256_unpackhi_ps(a.y, a.w);
        triverts[1] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 1);

        // Grab vertex 2 from lane 0 from 'b' and store it in tri[2]
        tmp0 = _mm256_unpacklo_ps(b.x, b.z);
        tmp1 = _mm256_unpacklo_ps(b.y, b.w);
        triverts[2] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 0);

        break;
    case 3:
        // Grab vertex 0 from lane 1 from 'b' and store it in tri[0]
        tmp0 = _mm256_unpacklo_ps(b.x, b.z);
        tmp1 = _mm256_unpacklo_ps(b.y, b.w);
        triverts[0] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 0);

        // Grab vertex 1 from lane 2 from 'b' and store it in tri[1]
        tmp0 = _mm256_unpackhi_ps(b.x, b.z);
        tmp1 = _mm256_unpackhi_ps(b.y, b.w);
        triverts[1] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 0);

        // Grab vertex 2 from lane 3 from 'b' and store it in tri[2]
        tmp0 = _mm256_unpackhi_ps(b.x, b.z);
        tmp1 = _mm256_unpackhi_ps(b.y, b.w);
        triverts[2] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 0);

        break;

    case 4:
        // Grab vertex 0 from lane 4 from 'b' and store it in tri[0]
        tmp0 = _mm256_unpacklo_ps(b.x, b.z);
        tmp1 = _mm256_unpacklo_ps(b.y, b.w);
        triverts[0] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 1);

        // Grab vertex 1 from lane 5 from 'b' and store it in tri[1]
        tmp0 = _mm256_unpacklo_ps(b.x, b.z);
        tmp1 = _mm256_unpacklo_ps(b.y, b.w);
        triverts[1] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 1);

        // Grab vertex 2 from lane 6 from 'b' and store it in tri[2]
        tmp0 = _mm256_unpackhi_ps(b.x, b.z);
        tmp1 = _mm256_unpackhi_ps(b.y, b.w);
        triverts[2] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 1);

        break;
    case 5:
        // Grab vertex 0 from lane 7 from 'b' and store it in tri[0]
        tmp0 = _mm256_unpackhi_ps(b.x, b.z);
        tmp1 = _mm256_unpackhi_ps(b.y, b.w);
        triverts[0] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 1);

        // Grab vertex 1 from lane 0 from 'c' and store it in tri[1]
        tmp0 = _mm256_unpacklo_ps(c.x, c.z);
        tmp1 = _mm256_unpacklo_ps(c.y, c.w);
        triverts[1] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 0);

        // Grab vertex 2 from lane 1 from 'c' and store it in tri[2]
        tmp0 = _mm256_unpacklo_ps(c.x, c.z);
        tmp1 = _mm256_unpacklo_ps(c.y, c.w);
        triverts[2] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 0);
        break;
    case 6:
        // Grab vertex 0 from lane 2 from 'c' and store it in tri[0]
        tmp0 = _mm256_unpackhi_ps(c.x, c.z);
        tmp1 = _mm256_unpackhi_ps(c.y, c.w);
        triverts[0] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 0);

        // Grab vertex 1 from lane 3 from 'c' and store it in tri[1]
        tmp0 = _mm256_unpackhi_ps(c.x, c.z);
        tmp1 = _mm256_unpackhi_ps(c.y, c.w);
        triverts[1] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 0);

        // Grab vertex 2 from lane 4 from 'c' and store it in tri[2]
        tmp0 = _mm256_unpacklo_ps(c.x, c.z);
        tmp1 = _mm256_unpacklo_ps(c.y, c.w);
        triverts[2] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 1);

        break;
    case 7:
        // Grab vertex 0 from lane 5 from 'c' and store it in tri[0]
        tmp0 = _mm256_unpacklo_ps(c.x, c.z);
        tmp1 = _mm256_unpacklo_ps(c.y, c.w);
        triverts[0] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 1);

        // Grab vertex 1 from lane 6 from 'c' and store it in tri[1]
        tmp0 = _mm256_unpackhi_ps(c.x, c.z);
        tmp1 = _mm256_unpackhi_ps(c.y, c.w);
        triverts[1] = _mm256_extractf128_ps(_mm256_unpacklo_ps(tmp0, tmp1), 1);

        // Grab vertex 2 from lane 7 from 'c' and store it in tri[2]
        tmp0 = _mm256_unpackhi_ps(c.x, c.z);
        tmp1 = _mm256_unpackhi_ps(c.y, c.w);
        triverts[2] = _mm256_extractf128_ps(_mm256_unpackhi_ps(tmp0, tmp1), 1);
        break;
    };
}