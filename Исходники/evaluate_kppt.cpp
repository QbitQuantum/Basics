  // 現在の局面の評価値の内訳を表示する。
  void print_eval_stat(Position& pos)
  {
    cout << "--- EVAL STAT\n";

    Square sq_bk = pos.king_square(BLACK);
    Square sq_wk = pos.king_square(WHITE);
    const auto* ppkppb = kpp[sq_bk];
    const auto* ppkppw = kpp[Inv(sq_wk)];

    auto& pos_ = *const_cast<Position*>(&pos);

    auto list_fb = pos_.eval_list()->piece_list_fb();
    auto list_fw = pos_.eval_list()->piece_list_fw();

    int i, j;
    BonaPiece k0, k1, l0, l1;

    // 38枚の駒を表示
    for (i = 0; i < PIECE_NO_KING; ++i)
      cout << int(list_fb[i]) << " = " << list_fb[i] << " , " << int(list_fw[i]) << " =  " << list_fw[i] << endl;

    // 評価値の合計
    EvalSum sum;

    // SSE2は少なくとも有るという前提で。

    // sum.p[0](BKPP)とsum.p[1](WKPP)をゼロクリア
    sum.m[0] = _mm_setzero_si128();

    // KK
    sum.p[2] = kk[sq_bk][sq_wk];
    cout << "KKC : " << sq_bk << " " << sq_wk << " = " << kk[sq_bk][sq_wk][0] << " + " << kk[sq_bk][sq_wk][1] << "\n";

    for (i = 0; i < PIECE_NO_KING; ++i)
    {
      k0 = list_fb[i];
      k1 = list_fw[i];
      const auto* pkppb = ppkppb[k0];
      const auto* pkppw = ppkppw[k1];
      for (j = 0; j < i; ++j)
      {
        l0 = list_fb[j];
        l1 = list_fw[j];

#if 0
        sum.p[0] += pkppb[l0];
        sum.p[1] += pkppw[l1];
#else
        // SSEによる実装

        // pkppw[l1][0],pkppw[l1][1],pkppb[l0][0],pkppb[l0][1]の16bit変数4つを整数拡張で32bit化して足し合わせる
        __m128i tmp;
        tmp = _mm_set_epi32(0, 0, *reinterpret_cast<const int32_t*>(&pkppw[l1][0]), *reinterpret_cast<const int32_t*>(&pkppb[l0][0]));
        tmp = _mm_cvtepi16_epi32(tmp);
        sum.m[0] = _mm_add_epi32(sum.m[0], tmp);

        cout << "BKPP : " << sq_bk << " " << k0 << " " << l0 << " = " << pkppb[l0][0] << " + " << pkppb[l0][1] << "\n";
        cout << "WKPP : " << sq_wk << " " << k1 << " " << l1 << " = " << pkppw[l1][0] << " + " << pkppw[l1][1] << "\n";

#endif
      }
      sum.p[2] += kkp[sq_bk][sq_wk][k0];

      cout << "KKP : " << sq_bk << " " << sq_wk << " " << k0 << " = " << kkp[sq_bk][sq_wk][k0][0] << " + " << kkp[sq_bk][sq_wk][k0][1] << "\n";

    }

    cout << "Material = " << pos.state()->materialValue << endl;
    cout << sum;
    cout << "---\n";

  }