static void init_bmi2(uint16_t table[], uint16_t *attacks[], Bitboard masks[],
                      Bitboard masks2[], int deltas[], Fn index)
{
  Bitboard edges, b;

  for (int s = 0; s < 64; s++) {
    attacks[s] = table;

    // Board edges are not considered in the relevant occupancies
    edges = ((Rank1BB | Rank8BB) & ~rank_bb_s(s)) | ((FileABB | FileHBB) & ~file_bb_s(s));

    masks2[s] = sliding_attack(deltas, s, 0);
    masks[s] = masks2[s] & ~edges;

    // Use Carry-Rippler trick to enumerate all subsets of masks[s] and
    // fill the attacks table.
    b = 0;
    do {
      attacks[s][index(s, b)] = _pext_u64(sliding_attack(deltas, s, b), masks2[s]);
      b = (b - masks[s]) & masks[s];
      table++;
    } while (b);
  }
}