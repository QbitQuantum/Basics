void NBodyAlgorithm::calculateAcceleration(const float3(&posI)[4], const float massJ, const float3 posJ, __m128 accIx, __m128 accIy, __m128 accIz, float *accI) {
    __m128 pix = _mm_set_ps(posI[0].x, posI[1].x, posI[2].x, posI[3].x);
    __m128 piy = _mm_set_ps(posI[0].y, posI[1].y, posI[2].y, posI[3].y);
    __m128 piz = _mm_set_ps(posI[0].z, posI[1].z, posI[2].z, posI[3].z);

    __m128 pjx = _mm_set_ps1(posJ.x);
    __m128 pjy = _mm_set_ps1(posJ.y);
    __m128 pjz = _mm_set_ps1(posJ.z);

    __m128 rx = _mm_sub_ps(pjx, pix);
    __m128 ry = _mm_sub_ps(pjy, piy);
    __m128 rz = _mm_sub_ps(pjz, piz);

    __m128 eps2 = _mm_set_ps1(mp_properties->eps2);

    __m128 rx2 = _mm_mul_ps(rx, rx);
    __m128 ry2 = _mm_mul_ps(ry, ry);
    __m128 rz2 = _mm_mul_ps(rz, rz);
    __m128 rabs = _mm_sqrt_ps(_mm_add_ps(_mm_add_ps(rx2, ry2), _mm_add_ps(rz2, eps2)));

    __m128 m = _mm_set_ps1(massJ);
    __m128 rabsInv = _mm_div_ps(m, _mm_mul_ps(_mm_mul_ps(rabs, rabs), rabs));

    __m128 aix = _mm_mul_ps(rx, rabsInv);
    __m128 aiy = _mm_mul_ps(ry, rabsInv);
    __m128 aiz = _mm_mul_ps(rz, rabsInv);

    accIx = _mm_add_ps(accIx, aix);
    accIy = _mm_add_ps(accIy, aiy);
    accIz = _mm_add_ps(accIz, aiz);

    _mm_storer_ps(accI, accIx);
    _mm_storer_ps(accI + 4, accIy);
    _mm_storer_ps(accI + 8, accIz);
}