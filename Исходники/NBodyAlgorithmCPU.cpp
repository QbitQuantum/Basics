void NBodyAlgorithmCPU::calculateAccelerationWithColor(const float3(&posI)[8], const float massJ, const float3 posJ, float3(&accI)[8], unsigned int(&numNeighbours)[8]) {
    __m256 pix = _mm256_set_ps(posI[0].x, posI[1].x, posI[2].x, posI[3].x, posI[4].x, posI[5].x, posI[6].x, posI[7].x);
    __m256 piy = _mm256_set_ps(posI[0].y, posI[1].y, posI[2].y, posI[3].y, posI[4].y, posI[5].y, posI[6].y, posI[7].y);
    __m256 piz = _mm256_set_ps(posI[0].z, posI[1].z, posI[2].z, posI[3].z, posI[4].z, posI[5].z, posI[6].z, posI[7].z);

    __m256 pjx = _mm256_set1_ps(posJ.x);
    __m256 pjy = _mm256_set1_ps(posJ.y);
    __m256 pjz = _mm256_set1_ps(posJ.z);

    __m256 rx = _mm256_sub_ps(pjx, pix);
    __m256 ry = _mm256_sub_ps(pjy, piy);
    __m256 rz = _mm256_sub_ps(pjz, piz);

    __m256 eps2 = _mm256_set1_ps(mp_properties->EPS2);

    __m256 rx2 = _mm256_mul_ps(rx, rx);
    __m256 ry2 = _mm256_mul_ps(ry, ry);
    __m256 rz2 = _mm256_mul_ps(rz, rz);
    __m256 rabs = _mm256_sqrt_ps(_mm256_add_ps(_mm256_add_ps(rx2, ry2), _mm256_add_ps(rz2, eps2)));

    __m256 cmpDistance = _mm256_set1_ps(float(mp_properties->positionScale));
    __m256 close = _mm256_cmp_ps(rabs, cmpDistance, 2);

    for (int i = 0; i < 8; i++) {
        if (close.m256_f32[i] == 0) {
            numNeighbours[7 - i] = 0;
        }
    }

    __m256 m = _mm256_set1_ps(massJ);
    __m256 rabsInv = _mm256_div_ps(m, _mm256_mul_ps(_mm256_mul_ps(rabs, rabs), rabs));

    __m256 aix = _mm256_mul_ps(rx, rabsInv);
    __m256 aiy = _mm256_mul_ps(ry, rabsInv);
    __m256 aiz = _mm256_mul_ps(rz, rabsInv);

    for (int i = 0; i < 8; i++) {
        accI[7 - i].x = aix.m256_f32[i];
        accI[7 - i].y = aiy.m256_f32[i];
        accI[7 - i].z = aiz.m256_f32[i];
    }

}