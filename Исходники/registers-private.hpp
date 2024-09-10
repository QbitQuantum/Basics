vector_register<256, double> setZero() {
    return vector_register<256, double>(_mm256_setzero_pd());
}