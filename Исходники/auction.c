int sse_auction_search(int *pr, int *P, int *ai0, int *ai1, int *a0, int *a1, int nodes, int arcs, int s, int t)
{
	int i __attribute__ ((aligned (16))) = 0;	
	int j __attribute__ ((aligned (16))) = t;
	int k __attribute__ ((aligned (16))) = 0;
	int m __attribute__ ((aligned (16))) = 0;	
	int maxla __attribute__ ((aligned (32))) = 0;
	int argmaxla __attribute__ ((aligned (16))) = 0;
	int cost __attribute__ ((aligned (16))) = 0;
	int length __attribute__ ((aligned (16))) = 1;
	int path_cost __attribute__ ((aligned (16))) = 0;
	
	uint32_t tmp1, tmp2;
	int cost_tab[nodes+1];

	__m128i a0sse, a1sse, ai0sse, ai1sse, ai1sse1, I, J, K, M, then;
	__m128i ARCS, MNODES, INFINITE, NEGINF, prsse, Psse, MAXLA, ARGMAXLA, LA, mask1, mask2, mask3, COST;
			
	for(i = 0; i <= nodes; i++) {
		cost_tab[i] = 0;
	}

	if(check_s_t(s, t, P, nodes) != 0) {
		return 1;
	}

	while(P[s] == INF) {
		k = -1;	
		m = -1;

		//printf("j = %d\n", j);

		J = _mm_set1_epi32(j);			//aktualna wartosc j
		K = _mm_set1_epi32(-1);			//poczatkowy indeks w tablicy z kosztami krawedzi
		M = _mm_set1_epi32(-1);			//koncowy indeks w tablicy z kosztami krawedzi
		MNODES = _mm_set1_epi32(nodes-1);	//liczba wezlow pomniejszona o 1 (do sprawdzenia czy koniec tablicy)
		ARCS = _mm_set1_epi32(arcs);		//liczba krawedzi
	
		/* wyliczenie k, m */
		for(i = 0; i < nodes; i+=4) {
			ai0sse = _mm_load_si128((__m128i*) &ai0[i]);	//ladowanie ai0 (numerow wezlow)
			ai1sse = _mm_load_si128((__m128i*) &ai1[i]);	//ladowanie ai1 (indeksow w tablicy z krawedziami)
			ai1sse1 = _mm_set_epi32(ai1[i+4],ai1[i+3],ai1[i+2],ai1[i+1]);	//ladowanie indeksow z ai1 przesunietych o 1
			mask1 = _mm_cmpeq_epi32(J, ai0sse);				//sprawdzenie warunku j == ai0[i]
			K = _mm_or_si128(_mm_and_si128(mask1,ai1sse), _mm_andnot_si128(mask1,K));	//ustalenie K
			I = _mm_set_epi32(i+3, i+2, i+1, i);						//aktualne wartosci i
			mask2 = _mm_cmplt_epi32(I, MNODES);				//sprawdzenie warunku i == nodes-1
			mask3 = _mm_and_si128(mask1,mask2);				//sprawdzenie sumy warunkow 1 i 2
			then = _mm_or_si128(_mm_and_si128(mask2,ai1sse1), _mm_andnot_si128(mask2,ARCS));	//m = ai1[i+1] lub arcs
			M = _mm_or_si128(_mm_and_si128(mask3,then), _mm_andnot_si128(mask3,M));		//ustalenie M
		}
	
		for(i = 0; i < nodes; i++) {
			if(ai0[i] == j) {
				k = ai1[i];		//k - indeks startowy krawedzi wychodzacych z j
				//printf("i = %d ", i);
				if(i < nodes - 1) {
					m = ai1[i+1];
				}
				else {
					m = arcs;
				}
			}
		}


		/* zapisanie k, m */
		for(i = 0; i < 4; i++) {
			tmp1 = get_from_m128i(K,i);
			tmp2 = get_from_m128i(M,i);
			if(tmp1 != -1) {
				k = tmp1;
			}
			if(tmp2 != -1) {
				m = tmp2;
			}
		}
		//printf("K,M: %d %d\n", k, m);
		
		/* wybor optymalnej krawedzi */
		if(k != -1) {		
			INFINITE = _mm_set1_epi32(INF);		//wartosc "nieskonczona"
			NEGINF = _mm_set1_epi32(0-INF);		//wartosc -INF
			COST = _mm_set1_epi32(cost);		//koszt wybranej krawedzi
			MAXLA = _mm_set1_epi32(0-INF);		//maksymalna wartosc la = pr[a0[i]] - a1[i]
			ARGMAXLA = _mm_set1_epi32(-1);		//indeks dla którego la jest najwieksza
			for(i = k; i < m; i+=4) {
				a1sse = _mm_set_epi32(a1[i],a1[i+1],a1[i+2],a1[i+3]);				//ladowanie a1
				a0sse = _mm_set_epi32(a0[i],a0[i+1],a0[i+2],a0[i+3]);				//ladowanie a0
				prsse = _mm_set_epi32(pr[a0[i]],pr[a0[i+1]],pr[a0[i+2]],pr[a0[i+3]]);		//ladowanie pr
				Psse = _mm_set_epi32(P[a0[i]],P[a0[i+1]],P[a0[i+2]],P[a0[i+3]]);		//ladowanie P
				mask1 = _mm_cmpgt_epi32(_mm_set1_epi32(m),_mm_set_epi32(i,i+1,i+2,i+3));	//czy ostatni obieg
				prsse = _mm_or_si128(_mm_and_si128(mask1,prsse), _mm_andnot_si128(mask1,NEGINF));	//obciecie cudzych lukow
				LA = _mm_sub_epi32(prsse, a1sse);		//la = pr[a0[i]] - a1[i]
				then = _mm_max_epi32(LA,MAXLA);			//maksymalna wartość la, maxla
				mask1 = _mm_cmpeq_epi32(Psse,INFINITE);		//czy P[i] == INF
				mask2 = _mm_and_si128(mask1,_mm_cmpgt_epi32(LA,MAXLA));		//czy P[i] == INF i LA > MAXLA
				MAXLA = _mm_or_si128(_mm_and_si128(mask1,then), _mm_andnot_si128(mask1,MAXLA));		//aktualizacja maxla
				ARGMAXLA = _mm_or_si128(_mm_and_si128(mask2,a0sse), _mm_andnot_si128(mask2,ARGMAXLA));	//aktualizacja argmaxla
				COST = _mm_or_si128(_mm_and_si128(mask2,a1sse), _mm_andnot_si128(mask2,COST));		//aktualizacja cost
			}
		}
	
		/* zapisanie maxla, argmaxla, cost */
		maxla = 0 - INF;
		for(i = 0; i < 4; i++) {
			tmp1 = get_from_m128i(MAXLA,i);
			if(tmp1 > maxla) {
				argmaxla = get_from_m128i(ARGMAXLA,i);
				maxla = tmp1;
				cost = get_from_m128i(COST,i);
			}
		}
		//printf("COST: %d, PATH_COST: %d\n", cost, path_cost);
		//printf("pr[j] = %d, maxla = %d, argmaxla = %d\n", pr[j], maxla, argmaxla);

		/* skrocenie sciezki */
		if(pr[j] > maxla || maxla == -INF) {
			
			/* uaktualnienie ceny */
			pr[j] = maxla;

			/* sciezka jednoelementowa nie jest skracana */
			if(j != t) {

				/* uaktualnienie sciezki */
				P[j] = INF;
				length = length - 1;
				path_cost = path_cost - cost_tab[length];
				cost_tab[length] = 0;
			
				/* powrot do poprzedniego wierzcholka w sciezce (j), k - odcinany */
				k = j;
				for(i = 0; i < nodes; i++) {
					if(P[i] == length - 1) {
						j = i;
						break;
					}
				}
			}
		}
		/* przedluzenie sciezki */
		else {
			P[argmaxla] = length;
			j = argmaxla;
			path_cost = path_cost + cost;
			cost_tab[length] = cost;
			length = length + 1;

			/* sciezka doszla do wierzcholka startowego => koniec */
			if(argmaxla == s)
			{
				printf("dlugosc sciezki: %d\n", path_cost);
				return 0;
			}
		}
	}
	return 0;


}