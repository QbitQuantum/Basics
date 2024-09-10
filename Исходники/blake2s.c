/* Permute the state while xoring in the block of data. */
static void blake2s_compress(BLAKE2S_CTX *S,
                            const uint8_t block[BLAKE2S_BLOCKBYTES])
{
    uint32_t m[16];
    uint32_t v[16];
    size_t i;

    for(i = 0; i < 16; ++i) {
        m[i] = load32(block + i * sizeof(m[i]));
    }

    for(i = 0; i < 8; ++i) {
        v[i] = S->h[i];
    }

    v[ 8] = blake2s_IV[0];
    v[ 9] = blake2s_IV[1];
    v[10] = blake2s_IV[2];
    v[11] = blake2s_IV[3];
    v[12] = S->t[0] ^ blake2s_IV[4];
    v[13] = S->t[1] ^ blake2s_IV[5];
    v[14] = S->f[0] ^ blake2s_IV[6];
    v[15] = S->f[1] ^ blake2s_IV[7];
#define G(r,i,a,b,c,d) \
    do { \
        a = a + b + m[blake2s_sigma[r][2*i+0]]; \
        d = rotr32(d ^ a, 16); \
        c = c + d; \
        b = rotr32(b ^ c, 12); \
        a = a + b + m[blake2s_sigma[r][2*i+1]]; \
        d = rotr32(d ^ a, 8); \
        c = c + d; \
        b = rotr32(b ^ c, 7); \
    } while(0)
#define ROUND(r)  \
    do { \
        G(r,0,v[ 0],v[ 4],v[ 8],v[12]); \
        G(r,1,v[ 1],v[ 5],v[ 9],v[13]); \
        G(r,2,v[ 2],v[ 6],v[10],v[14]); \
        G(r,3,v[ 3],v[ 7],v[11],v[15]); \
        G(r,4,v[ 0],v[ 5],v[10],v[15]); \
        G(r,5,v[ 1],v[ 6],v[11],v[12]); \
        G(r,6,v[ 2],v[ 7],v[ 8],v[13]); \
        G(r,7,v[ 3],v[ 4],v[ 9],v[14]); \
    } while(0)
    ROUND(0);
    ROUND(1);
    ROUND(2);
    ROUND(3);
    ROUND(4);
    ROUND(5);
    ROUND(6);
    ROUND(7);
    ROUND(8);
    ROUND(9);

    for(i = 0; i < 8; ++i) {
        S->h[i] = S->h[i] ^ v[i] ^ v[i + 8];
    }

#undef G
#undef ROUND
}