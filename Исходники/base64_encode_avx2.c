char *_base64_encode_avx2(char *out, const unsigned char *in, size_t n, int options)
{
    size_t i;
    size_t o = 0;

    const char (*alphabet)[2] = _base64_alphabet_precombined;
    if (options & Base64UseUrlAlphabet)
        alphabet = _base64url_alphabet_precombined;

    for (i = 0; n - i >= 48; i += 48) {
        // read 48 bytes and duplicate each 16-byte chunk in the high part of the register
        __m256i chunk1 = _mm256_broadcastsi128_si256(* (const __m128i *)&in[i+0]);
        __m256i chunk2 = _mm256_broadcastsi128_si256(* (const __m128i *)&in[i+16]);
        __m256i chunk3 = _mm256_broadcastsi128_si256(* (const __m128i *)&in[i+32]);

        // first chunk of 12 bytes
        do_encode_12bytes(alphabet, out + o, chunk1);
        o += 16;

        // second chunk: 4 bytes left in chunk1
        do_encode_12bytes(alphabet, out + o, _mm256_alignr_epi8(chunk2, chunk1, 12));
        o += 16;

        // third chunk: 8 bytes left in chunk2
        do_encode_12bytes(alphabet, out + o, _mm256_alignr_epi8(chunk3, chunk2, 8));
        o += 16;

        // fourth chunk: 12 final bytes in chunk3
        do_encode_12bytes(alphabet, out + o, _mm256_srli_si256(chunk3, 4));
        o += 16;

        if (options & Base64InsertLineBreaks)
            out[o++] = '\n';
    }

    return _base64_encode_tail(out, o, in, n, options);
}