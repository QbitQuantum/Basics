int main() {
    unsigned int i, bytes_read, n, written;
    char buffer[BUFF_SIZE];

    __m256i* mem256 = (__m256i*)&mem[0];
    __m256i* final =  (__m256i*)&mem[999936];
    __m256i zero256 = _mm256_setzero_si256();
    for (; mem256 < final; mem256 += 8) {
        _mm256_store_si256(&mem256[0], zero256);
        _mm256_store_si256(&mem256[1], zero256);
        _mm256_store_si256(&mem256[2], zero256);
        _mm256_store_si256(&mem256[3], zero256);
        _mm256_store_si256(&mem256[4], zero256);
        _mm256_store_si256(&mem256[5], zero256);
        _mm256_store_si256(&mem256[6], zero256);
        _mm256_store_si256(&mem256[7], zero256);
    }

    final = (__m256i*) &mem[1000000];