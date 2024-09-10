long garbleCircuit(GarbledCircuit *garbledCircuit, InputLabels inputLabels, OutputMap outputMap) {

	GarblingContext garblingContext;
	GarbledGate *garbledGate;
	GarbledTable *garbledTable;
	DKCipherContext dkCipherContext;
	const __m128i *sched = ((__m128i *)(dkCipherContext.K.rd_key));
	block val;

	block *A, *B, *plainText,*cipherText;
	block tweak;
	long a, b, i, j,rnds = 10;
	block blocks[4];
	block keys[4];
	long lsb0,lsb1;
	block keyToEncrypt;
	int input0, input1,output;
	srand_sse( time(NULL));

	startTime = RDTSC;

	createInputLabels(inputLabels, garbledCircuit->n);

	garbledCircuit->id = getFreshId();

	for(i=0;i<2*garbledCircuit->n;i+=2) {
		garbledCircuit->wires[i/2].id = i+1;
		garbledCircuit->wires[i/2].label0 = inputLabels[i];
		garbledCircuit->wires[i/2].label1 = inputLabels[i+1];
	}
	garbledTable = garbledCircuit->garbledTable;
	garblingContext.gateIndex = 0;
	garblingContext.wireIndex = garbledCircuit->n + 1;
	block key = randomBlock();
	block rkey = randomBlock();
	AES_KEY KR;
	AES_set_encrypt_key(&rkey, 128, &KR);
	const __m128i *sched2 = ((__m128i *)(KR.rd_key));
	garblingContext.R = xorBlocks(garbledCircuit->wires[0].label0, garbledCircuit->wires[0].label1);
	garbledCircuit->globalKey = key;
	DKCipherInit(&key, &(garblingContext.dkCipherContext));
	int tableIndex = 0;

	for(i=0; i< garbledCircuit->q;i++) {
		garbledGate = &(garbledCircuit->garbledGates[i]);
		input0 = garbledGate->input0; input1 = garbledGate->input1;
		output = garbledGate->output;

#ifdef FREE_XOR
		if (garbledGate->type == XORGATE) {
			garbledCircuit->wires[output].label0 = xorBlocks(garbledCircuit->wires[input0].label0, garbledCircuit->wires[input1].label0);
			garbledCircuit->wires[output].label1 = xorBlocks(garbledCircuit->wires[input0].label1, garbledCircuit->wires[input1].label0);
			continue;
		}
#endif
		tweak = makeBlock(i, (long)0);
		lsb0 = getLSB(garbledCircuit->wires[input0].label0);
		lsb1 = getLSB(garbledCircuit->wires[input1].label0);
		char templ[20];
		char templ2[20];
		block val = _mm_xor_si128 (tweak, sched[0]);
		for (j=1; j<rnds; j++) val = _mm_aesenc_si128 (val,sched2[j]);
		*((block*)templ) = _mm_aesenclast_si128 (val, sched[j]);
		val = _mm_aesenclast_si128 (val, sched[j]);
		*((block *)templ2) = xorBlocks(*((block *)templ), garblingContext.R);

		TRUNCATE(templ);
		TRUNCATE(templ2);

		block *label0 = (block *)templ;
		block *label1 = (block *)templ2;
		garbledCircuit->wires[garbledGate->output].label0 = *((block*)templ);
		garbledCircuit->wires[garbledGate->output].label1 = *((block*)templ2);
		block A0, A1, B0, B1;
		A0 = DOUBLE(garbledCircuit->wires[input0].label0);
		A1 = DOUBLE(garbledCircuit->wires[input0].label1);
		B0 = DOUBLE(DOUBLE(garbledCircuit->wires[input1].label0));
		B1 = DOUBLE(DOUBLE(garbledCircuit->wires[input1].label1));

		keys[0] = xorBlocks(A0, B0);
		keys[0] = xorBlocks(keys[0], tweak);
		keys[1] = xorBlocks(A0,B1);
		keys[1] = xorBlocks(keys[1], tweak);
		keys[2] = xorBlocks(A1, B0);
		keys[2] = xorBlocks(keys[2], tweak);
		keys[3] = xorBlocks(A1, B1);
		keys[3] = xorBlocks(keys[3], tweak);

		if (garbledGate->type == ANDGATE) {

			blocks[0] = xorBlocks(keys[0], *label0);
			blocks[1] = xorBlocks(keys[1], *label0);
			blocks[2] = xorBlocks(keys[2], *label0);
			blocks[3] = xorBlocks(keys[3], *label1);
			goto write;
		}

		if (garbledGate->type == ORGATE) {

			blocks[0] = xorBlocks(keys[0], *label0);
			blocks[1] = xorBlocks(keys[1], *label1);
			blocks[2] = xorBlocks(keys[2], *label1);
			blocks[3] = xorBlocks(keys[3], *label1);
			goto write;

		}

		if (garbledGate->type == XORGATE) {

			blocks[0] = xorBlocks(keys[0], *label0);
			blocks[1] = xorBlocks(keys[1], *label1);
			blocks[2] = xorBlocks(keys[2], *label1);
			blocks[3] = xorBlocks(keys[3], *label0);
			goto write;

		}

		if (garbledGate->type == NOTGATE) {

			blocks[0] = xorBlocks(keys[0], *label1);
			blocks[1] = xorBlocks(keys[1], *label0);
			blocks[2] = xorBlocks(keys[2], *label1);
			blocks[3] = xorBlocks(keys[3], *label0);
			goto write;

		}
		write:
		AES_ecb_encrypt_blks(keys, 4, &(garblingContext.dkCipherContext.K));

		char toWrite[4][16];
		char **dest[4];

		*((block *) toWrite[0]) = xorBlocks(blocks[0], keys[0]);
		*((block *) toWrite[1]) = xorBlocks(blocks[1], keys[1]);
		*((block *) toWrite[2]) = xorBlocks(blocks[2], keys[2]);
		*((block *) toWrite[3]) = xorBlocks(blocks[3], keys[3]);

		short *cpsrc; short *cpdst;
		cpsrc = (short *)toWrite[0];
		cpdst = (short *)&garbledTable[tableIndex].table[2*lsb0 + lsb1];
		cpdst[0]=cpsrc[0];
		cpdst[1]=cpsrc[1];
		cpdst[2]=cpsrc[2];
		cpdst[3]=cpsrc[3];
		cpdst[4]=cpsrc[4];

		cpsrc = (short *)toWrite[1];
		cpdst = (short *)&garbledTable[tableIndex].table[2*(lsb0) + (1-lsb1)];
		cpdst[0]=cpsrc[0];
		cpdst[1]=cpsrc[1];
		cpdst[2]=cpsrc[2];
		cpdst[3]=cpsrc[3];
		cpdst[4]=cpsrc[4];

		cpsrc = (short *)toWrite[2];
		cpdst = (short *)&garbledTable[tableIndex].table[2*(1-lsb0) + (lsb1)];
		cpdst[0]=cpsrc[0];
		cpdst[1]=cpsrc[1];
		cpdst[2]=cpsrc[2];
		cpdst[3]=cpsrc[3];
		cpdst[4]=cpsrc[4];

		cpsrc = (short *)toWrite[3];
		cpdst = (short *)&garbledTable[tableIndex].table[2*(1-lsb0) + (1-lsb1)];
		cpdst[0]=cpsrc[0];
		cpdst[1]=cpsrc[1];
		cpdst[2]=cpsrc[2];
		cpdst[3]=cpsrc[3];
		cpdst[4]=cpsrc[4];

		tableIndex++;
	}
	for(i=0;i<garbledCircuit->m;i++) {
		outputMap[2*i] = garbledCircuit->wires[garbledCircuit->outputs[i]].label0;
		outputMap[2*i+1] = garbledCircuit->wires[garbledCircuit->outputs[i]].label1;
	}

	endTime = RDTSC;
	return (endTime - startTime);
}