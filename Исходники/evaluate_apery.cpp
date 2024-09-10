int Position::evaluate(const Color us) const
{
	int list0[NLIST], list1[NLIST];
	int sq_bk, sq_wk;
#ifndef TWIG
	int score;
#else
	EvalSum score;
#endif
	static int count=0;
	count++;
	int nlist=0;

	// 持ち駒をリスト化する
#define FOO(hand, Piece, list0_index, list1_index)    \
	for (int i = I2Hand##Piece(hand); i >= 1; --i) {  \
		list0[nlist] = list0_index + i;               \
		list1[nlist] = list1_index + i;               \
		++nlist; \
	}

	FOO(HAND_B, Pawn  , f_hand_pawn  , e_hand_pawn  )
	FOO(HAND_W, Pawn  , e_hand_pawn  , f_hand_pawn  )
	FOO(HAND_B, Lance , f_hand_lance , e_hand_lance )
	FOO(HAND_W, Lance , e_hand_lance , f_hand_lance )
	FOO(HAND_B, Knight, f_hand_knight, e_hand_knight)
	FOO(HAND_W, Knight, e_hand_knight, f_hand_knight)
	FOO(HAND_B, Silver, f_hand_silver, e_hand_silver)
	FOO(HAND_W, Silver, e_hand_silver, f_hand_silver)
	FOO(HAND_B, Gold  , f_hand_gold  , e_hand_gold  )
	FOO(HAND_W, Gold  , e_hand_gold  , f_hand_gold  )
	FOO(HAND_B, Bishop, f_hand_bishop, e_hand_bishop)
	FOO(HAND_W, Bishop, e_hand_bishop, f_hand_bishop)
	FOO(HAND_B, Rook  , f_hand_rook  , e_hand_rook  )
	FOO(HAND_W, Rook  , e_hand_rook  , f_hand_rook  )
#undef FOO

	nlist = make_list_apery(list0, list1, nlist);

	sq_bk = SQ_BKING;
	sq_wk = SQ_WKING;
	assert(0 <= sq_bk && sq_bk < nsquare);
	assert(0 <= sq_wk && sq_wk < nsquare);
	const auto* ppkppb = KPP[sq_bk     ];
	const auto* ppkppw = KPP[Inv(sq_wk)];

#ifndef TWIG
	score = fv_kk[sq_bk][sq_wk];
	for (int i = 0; i < nlist; i++ ) {
		const int k0 = list0[i];
		const int k1 = list1[i];
		assert(0 <= k0 && k0 < fe_end);
		assert(0 <= k1 && k1 < fe_end);
		const auto* pkppb = ppkppb[k0];
		const auto* pkppw = ppkppw[k1];
		for (int j = 0; j < i; j++ ) {
			const int l0 = list0[j];
			const int l1 = list1[j];
			assert(0 <= l0 && l0 < fe_end);
			assert(0 <= l1 && l1 < fe_end);
			score += pkppb[l0];
			score -= pkppw[l1];
		}
		score += fv_kkp[sq_bk][sq_wk][k0];
	}

	score += MATERIAL * FV_SCALE;
	score /= FV_SCALE;

	score = (us == BLACK) ? score : -score;

	return score;
#else
	EvalSum sum;
	sum.p[2] = KK[sq_bk][sq_wk];
#if defined USE_AVX2_EVAL || defined USE_SSE_EVAL
	sum.m[0] = _mm_setzero_si128();
	for (int i = 0; i < nlist; ++i) {
		const int k0 = list0[i];
		const int k1 = list1[i];
		const auto* pkppb = ppkppb[k0];
		const auto* pkppw = ppkppw[k1];
		for (int j = 0; j < i; ++j) {
			const int l0 = list0[j];
			const int l1 = list1[j];
			__m128i tmp;
			tmp = _mm_set_epi32(0, 0, *reinterpret_cast<const int32_t*>(&pkppw[l1][0]), *reinterpret_cast<const int32_t*>(&pkppb[l0][0]));
			tmp = _mm_cvtepi16_epi32(tmp);
			sum.m[0] = _mm_add_epi32(sum.m[0], tmp);
		}
		sum.p[2] += KKP[sq_bk][sq_wk][k0];
	}
	sum.p[2][0] += MATERIAL * FV_SCALE;

#else
	// loop 開始を i = 1 からにして、i = 0 の分のKKPを先に足す。
	sum.p[2] += KKP[sq_bk][sq_wk][list0[0]];
	sum.p[0][0] = 0;
	sum.p[0][1] = 0;
	sum.p[1][0] = 0;
	sum.p[1][1] = 0;
	for (int i = 1; i < nlist; ++i) {
		const int k0 = list0[i];
		const int k1 = list1[i];
		const auto* pkppb = ppkppb[k0];
		const auto* pkppw = ppkppw[k1];
		for (int j = 0; j < i; ++j) {
			const int l0 = list0[j];
			const int l1 = list1[j];
			sum.p[0] += pkppb[l0];
			sum.p[1] += pkppw[l1];
		}
		sum.p[2] += KKP[sq_bk][sq_wk][k0];
	}
	sum.p[2][0] += MATERIAL * FV_SCALE;
#endif

#ifdef _DEBUG
	score.p[2] = KK[sq_bk][sq_wk];

	score.p[0][0] = 0;
	score.p[0][1] = 0;
	score.p[1][0] = 0;
	score.p[1][1] = 0;

	for (int i = 0; i < nlist; ++i) {
		const int k0 = list0[i];
		const int k1 = list1[i];
		const auto* pkppb = ppkppb[k0];
		const auto* pkppw = ppkppw[k1];
		for (int j = 0; j < i; ++j) {
			const int l0 = list0[j];
			const int l1 = list1[j];
			score.p[0][0] += pkppb[l0][0];
			score.p[0][1] += pkppb[l0][1];
			score.p[1][0] += pkppw[l1][0];
			score.p[1][1] += pkppw[l1][1];
		}
		score.p[2][0] += KKP[sq_bk][sq_wk][k0][0];
		score.p[2][1] += KKP[sq_bk][sq_wk][k0][1];
	}

	score.p[2][0] += MATERIAL * FV_SCALE;
	assert(score.sum(us) == sum.sum(us));
#endif

	return sum.sum(us) / FV_SCALE ;

#endif
}