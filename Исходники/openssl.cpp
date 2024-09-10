int main() {
	srand((unsigned)time(NULL));
	int i;
	EC_KEY* key;
	//key = EC_KEY_new_by_curve_name(415);
	key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
	const EC_GROUP *group = EC_KEY_get0_group(key);
	if (EC_KEY_generate_key(key)==0) {
		printf("Error generate key\n");
		return -1;
	}
	unsigned char pk_b[33];
	const EC_POINT *pub = EC_KEY_get0_public_key(key);
	if (EC_POINT_point2oct(group, pub, POINT_CONVERSION_COMPRESSED, pk_b, 33, 0)!=33) {
		printf("Error 2\n");
		return -1;
	}
	unsigned char h1[16],h2[16];

	printf("\x02");
	for (i=0;i<16;i++) {
		h1[i]=rand()%256;
		printf("%c",h1[i]);
	}
	for (i=0;i<33;i++)
		printf("%c",pk_b[i]);
	fflush(stdout);
	//get h2
	for (i=0;i<16;i++) 
		h2[i]=rand()%256;
	for (i=0;i<16;i++)
		scanf("%c",&h2[i]);
		
	//get peerpk_b
	unsigned char peerpk_b[33]={2 , 30 , 25 , 50 , 17 , 242 , 232 , 55 , 157 , 18 , 106 , 115 , 214 , 193 , 192 , 39 , 207 , 226 , 184 , 216 , 244 , 147 , 111 , 188 , 125 , 230 , 38 , 125 , 231 , 50 , 56 , 152 , 148 };
	for (i=0;i<33;i++)
		scanf("%c",&peerpk_b[i]);
	
	EC_POINT *peerpk = EC_POINT_new(group);
	if (EC_POINT_oct2point(group, peerpk, peerpk_b, 33, 0)==0) {
		printf("Error 3\n");
		return -1;
	}
	unsigned char skey[33];
	if (ECDH_compute_key(skey, 32,  peerpk, key, NULL)==0) {
		printf("Error 4\n");
		return -1;
	}


	SHA512_CTX shactx;	
	unsigned char hash[SHA512_DIGEST_LENGTH];
	SHA512_Init(&shactx);
	SHA512_Update(&shactx, h2, 16);
	SHA512_Update(&shactx, skey, 32);
	SHA512_Update(&shactx, h1, 16);
	SHA512_Final(hash, &shactx);

	for (i=0;i<64;i++)
		printf("%02x",hash[i]);	
	fflush(stdout);

	struct cipher c;
	c.recvfd=0;
	c.sendfd=1;
	for (i=0;i<16;i++)
		c.sendkey[i]=hash[i];
	for (i=0;i<4;i++)
		c.sendiv[i]=hash[32+i];
	for (i=0;i<16;i++)
		c.recvkey[i]=hash[16+i];
	for (i=0;i<4;i++)
		c.recviv[i]=hash[36+i];
	c.sendcnt=0;
	c.recvcnt=0;

	unsigned char d[1000];
	unsigned char oiv[8];
	int op;
	char dlen;

	while (true) {
		scanf("%d",&op);
		scanf("%c",&dlen);
		scanf("%c",&dlen);
		for (i=0;i<dlen;i++)
			scanf("%c",&d[i]);
		if (op==1) {
			for (i=0;i<8;i++)
				oiv[i]=rand()%256;
			encrypt(c,d,dlen,oiv);
			c.recvcnt+=1;
		} else if (op==2) {
			for (i=0;i<8;i++)
				scanf("%c",&oiv[i]);
			decrypt(c,d,dlen,oiv, NULL);
			c.sendcnt+=1;
		}
		fflush(stdout);
	}
	
	return 0;
}