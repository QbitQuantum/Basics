static size_t tls1_1_multi_block_encrypt(EVP_AES_HMAC_SHA256 *key,
	unsigned char *out, const unsigned char *inp, size_t inp_len,
	int n4x)	/* n4x is 1 or 2 */
{
	HASH_DESC	hash_d[8], edges[8];
	CIPH_DESC	ciph_d[8];
	unsigned char	storage[sizeof(SHA256_MB_CTX)+32];
	union {	u64	q[16];
		u32	d[32];
		u8	c[128];	} blocks[8];
	SHA256_MB_CTX	*ctx;
	unsigned int	frag, last, packlen, i, x4=4*n4x;
	size_t		ret = 0;
	u8		*IVs;

	ctx = (SHA256_MB_CTX *)(storage+32-((size_t)storage%32));	/* align */

	frag = (unsigned int)inp_len>>(1+n4x);
	last = (unsigned int)inp_len+frag-(frag<<(1+n4x));
	if (last>frag && ((last+13+9)%64)<(x4-1)) {
		frag++;
		last -= x4-1;
	}

	hash_d[0].ptr = inp;
	for (i=1;i<x4;i++)	hash_d[i].ptr = hash_d[i-1].ptr+frag;

	for (i=0;i<x4;i++) {
		unsigned int len = (i==(x4-1)?last:frag);

		ctx->A[i] = key->md.h[0];
		ctx->B[i] = key->md.h[1];
		ctx->C[i] = key->md.h[2];
		ctx->D[i] = key->md.h[3];
		ctx->E[i] = key->md.h[4];
		ctx->F[i] = key->md.h[5];
		ctx->G[i] = key->md.h[6];
		ctx->H[i] = key->md.h[7];

		/* fix seqnum */
#if defined(BSWAP8)
		blocks[i].q[0] = BSWAP8(BSWAP8(*(u64*)key->md.data)+i);
#else
		blocks[i].c[7] += ((u8*)key->md.data)[7]+i;
		if (blocks[i].c[7] < i) {
			int j;

			for (j=6;j>=0;j--) {
				if (blocks[i].c[j]=((u8*)key->md.data)[j]+1) break;
			}
		}
#endif
		blocks[i].c[8] = ((u8*)key->md.data)[8];
		blocks[i].c[9] = ((u8*)key->md.data)[9];
		blocks[i].c[10] = ((u8*)key->md.data)[10];
		/* fix length */
		blocks[i].c[11] = (u8)(len>>8);
		blocks[i].c[12] = (u8)(len);

		memcpy(blocks[i].c+13,hash_d[i].ptr,64-13);
		hash_d[i].ptr += 64-13;
		hash_d[i].blocks = (len-(64-13))/64;

		edges[i].ptr = blocks[i].c;
		edges[i].blocks = 1;
	}

	/* hash 13-byte headers and first 64-13 bytes of inputs */
	sha256_multi_block(ctx,edges,n4x);
	/* hash bulk inputs */
	sha256_multi_block(ctx,hash_d,n4x);

	memset(blocks,0,sizeof(blocks));
	for (i=0;i<x4;i++) {
		unsigned int		len = (i==(x4-1)?last:frag),
					off = hash_d[i].blocks*64;
		const unsigned char    *ptr = hash_d[i].ptr+off;

		off = len-(64-13)-off;	/* remainder actually */
		memcpy(blocks[i].c,ptr,off);
		blocks[i].c[off]=0x80;
		len += 64+13;		/* 64 is HMAC header */
		len *= 8;		/* convert to bits */
		if (off<(64-8)) {
			blocks[i].d[15] = BSWAP4(len);
			edges[i].blocks = 1;			
		} else {
			blocks[i].d[31] = BSWAP4(len);
			edges[i].blocks = 2;
		}
		edges[i].ptr = blocks[i].c;
	}

	/* hash input tails and finalize */
	sha256_multi_block(ctx,edges,n4x);

	memset(blocks,0,sizeof(blocks));
	for (i=0;i<x4;i++) {
		blocks[i].d[0] = BSWAP4(ctx->A[i]);	ctx->A[i] = key->tail.h[0];
		blocks[i].d[1] = BSWAP4(ctx->B[i]);	ctx->B[i] = key->tail.h[1];
		blocks[i].d[2] = BSWAP4(ctx->C[i]);	ctx->C[i] = key->tail.h[2];
		blocks[i].d[3] = BSWAP4(ctx->D[i]);	ctx->D[i] = key->tail.h[3];
		blocks[i].d[4] = BSWAP4(ctx->E[i]);	ctx->E[i] = key->tail.h[4];
		blocks[i].d[5] = BSWAP4(ctx->F[i]);	ctx->F[i] = key->tail.h[5];
		blocks[i].d[6] = BSWAP4(ctx->G[i]);	ctx->G[i] = key->tail.h[6];
		blocks[i].d[7] = BSWAP4(ctx->H[i]);	ctx->H[i] = key->tail.h[7];
		blocks[i].c[32] = 0x80;
		blocks[i].d[15] = BSWAP4((64+32)*8);
		edges[i].ptr = blocks[i].c;
		edges[i].blocks = 1;
	}

	/* finalize MACs */
	sha256_multi_block(ctx,edges,n4x);

	packlen = 5+16+((frag+32+16)&-16);

	out += (packlen<<(1+n4x))-packlen;
	inp += (frag<<(1+n4x))-frag;

	RAND_bytes((IVs=blocks[0].c),16*x4);	/* ask for IVs in bulk */

	for (i=x4-1;;i--) {
		unsigned int len = (i==(x4-1)?last:frag), pad, j;
		unsigned char *out0 = out;

		out += 5+16;		/* place for header and explicit IV */
		ciph_d[i].inp = out;
		ciph_d[i].out = out;

		memmove(out,inp,len);
		out += len;

		/* write MAC */
		((u32 *)out)[0] = BSWAP4(ctx->A[i]);
		((u32 *)out)[1] = BSWAP4(ctx->B[i]);
		((u32 *)out)[2] = BSWAP4(ctx->C[i]);
		((u32 *)out)[3] = BSWAP4(ctx->D[i]);
		((u32 *)out)[4] = BSWAP4(ctx->E[i]);
		((u32 *)out)[5] = BSWAP4(ctx->F[i]);
		((u32 *)out)[6] = BSWAP4(ctx->G[i]);
		((u32 *)out)[7] = BSWAP4(ctx->H[i]);
		out += 32;
		len += 32;

		/* pad */
		pad = 15-len%16;
		for (j=0;j<=pad;j++) *(out++) = pad;
		len += pad+1;

		ciph_d[i].blocks = len/16;
		len += 16;	/* account for explicit iv */

		/* arrange header */
		out0[0] = ((u8*)key->md.data)[8];
		out0[1] = ((u8*)key->md.data)[9];
		out0[2] = ((u8*)key->md.data)[10];
		out0[3] = (u8)(len>>8);
		out0[4] = (u8)(len);

		/* explicit iv */
		memcpy(ciph_d[i].iv, IVs, 16);
		memcpy(&out0[5],     IVs, 16);

		ret += len+5;

		if (i==0) break;

		out = out0-packlen;
		inp -= frag;
		IVs += 16;
	}

	aesni_multi_cbc_encrypt(ciph_d,&key->ks,n4x);

	OPENSSL_cleanse(blocks,sizeof(blocks));
	OPENSSL_cleanse(ctx,sizeof(*ctx));

	return ret;
}