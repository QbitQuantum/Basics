inline static int16_t smith_waterman_farrar(Objeto*o, char *sec_database, int16_t long_sec_database){
	int32_t * aux_Max;
	int16_t ret_max = 0;

	__m512i vGapOpen, vGapExtend, zero;
	__m512i vF, vH, vMax, vE_j, vAux0;
	int segLen = (64 / sizeof(int32_t));
	int numSeg = (long_sec_ref + 63 / sizeof(int32_t)) / (64 / sizeof(int32_t));

		int32_t cog[segLen] __attribute__((aligned(64)));
		int32_t ceg[segLen] __attribute__((aligned(64)));
		//
		for(int x=0;x<segLen;x++) {
			cog[x] = coste_open_gap;
			ceg[x] = coste_extend_gap;
		}
		vGapOpen = _mm512_load_epi32(cog);
		vGapExtend = _mm512_load_epi32(ceg);
		zero = _mm512_xor_epi32(zero, zero);


	vMax = _mm512_xor_epi32(vMax, vMax); // vMax = <0, 0, ..., 0>

	for(int j=0; j<long_profile; j++){
		o->columnaPrevia_Max[j] = 0;
		//o->columna_Up[j] = 0;
		o->columna_Left[j] = 0;
	}
	for(int x=0; x<long_sec_database; x++){
		// vF = <0, 0, ..., 0>
		vF = _mm512_xor_epi32(vF, vF);

		// vH = vHStore[numSeg - 1] << 1
		vH = _mm512_load_epi32(o->columnaPrevia_Max + (numSeg - 1) * segLen);
		vH = shiftRight(vH);

		//
		int8_t pos_letra_database = letras[(int)(sec_database[x])];
		//printf("Letra %d %c %d\n", x, sec_database[x], pos_letra_database);
		int32_t offset = pos_letra_database * long_profile;
		int j;
		for(j=0; j<numSeg; j++){
			// vH = vH + vProfile[letra][j]
			int32_t * valor_match = profile + offset;
			offset += segLen;
			vAux0 = _mm512_load_epi32(valor_match);
			vH = _mm512_add_epi32(vH, vAux0);

			// vMax = max(vMax, vH);
			vMax = _mm512_max_epi32(vMax, vH);

			// vE[j] = max(vH, vE[j])
			// vH = max(vH, vF)
			vE_j = _mm512_load_epi32(o->columna_Left + j*segLen);
			vH = _mm512_max_epi32(vH, vE_j);
			vH = _mm512_max_epi32(vH, vF);

			// vHStore[j] = vH
			_mm512_store_epi32(o->columnaActual_Max + j*segLen, vH);

			// vAux = vH - vGapOpen
			vAux0 = _mm512_sub_epi32(vH, vGapOpen);
			vAux0 = _mm512_max_epi32(vAux0, zero);
			// vE[j] = vE[j] - vGapExtend
			vE_j = _mm512_sub_epi32(vE_j, vGapExtend);
			vE_j = _mm512_max_epi32(vE_j, zero);
			// vE[j] = max(vE[j], vAux)
			vE_j = _mm512_max_epi32(vE_j, vAux0);
			_mm512_store_epi32(o->columna_Left + j*segLen, vE_j);
			// vF = vF - vGapExtend
			vF = _mm512_sub_epi32(vF, vGapExtend);
			vF = _mm512_max_epi32(vF, zero);
			// vF = max(vF, vAux)
			vF = _mm512_max_epi32(vF, vAux0);

			// vH = vHLoad[j]
			vH = _mm512_load_epi32(o->columnaPrevia_Max + j*segLen);
		}
		// Optimización de SWAT
		/*
		for(int x=0; x<long_profile; x++){
			printf("vMax[%d]=%d\n", x, o->columnaActual_Max[x]);
		}
		printf("Numseg: %d\n", numSeg);
		displayV("F", vF);
		*/
		// vF = vF << 1
		vF = shiftRight(vF);

		j = 0;
		do { // while(AnyElement(vF > vHStore[j] - vGapOpen
			vH = _mm512_load_epi32(o->columnaActual_Max + j*segLen);
			vAux0 = _mm512_sub_epi32(vH, vGapOpen);
			vAux0 = _mm512_max_epi32(vAux0, zero);
			__mmask16 mascara = _mm512_cmpgt_epi32_mask (vF, vAux0);
			if (mascara == 0) break;
			// vHStore[j] = max(vHStore[j], vF)
			vH = _mm512_max_epi32(vH, vF);
			_mm512_store_epi32(o->columnaActual_Max + j*segLen, vH);

			// vF = vF - vGapExtend
			vF = _mm512_sub_epi32(vF, vGapExtend);
			vF = _mm512_max_epi32(vF, zero);
			if (++j >= numSeg) {
				// vF = vF << 1
				vF = shiftRight(vF);
				j = 0;
			}

		} while(1);

		//
		aux_Max = o->columnaActual_Max;
		o->columnaActual_Max = o->columnaPrevia_Max;
		o->columnaPrevia_Max = aux_Max;
		//
	}

	int32_t max[segLen] __attribute__((aligned(64)));
	_mm512_store_epi32(max, vMax);
	for(int x=1;x<segLen;x++) {
		if(max[0] < max[x]) max[0] = max[x];
	}
	if (max[0] > 32767) max[0] = 32767;
	ret_max = max[0];
	return ret_max;
}