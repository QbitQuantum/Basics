static
int
abAbacus::SetUngappedFragmentPositions(FragType type,int32 n_frags, MultiAlignT *uma) {

  int32 num_frags   = GetNumIntMultiPoss(uma->f_list);
  int32 num_unitigs = GetNumIntUnitigPoss(uma->u_list);

  HashTable_AS *unitigFrags = CreateScalarHashTable_AS();

  int32 num_columns   = GetMultiAlignLength(uma);
  int32 ungapped_pos  = 0;

  int32 *gapped_positions = new int32 [num_columns + 1];
  char  *consensus        = Getchar(uma->consensus,0);

  for (int32 i=0; i<num_columns+1; i++) {
    gapped_positions[i] = ungapped_pos;

    if (consensus[i] != '-')
      ungapped_pos++;
  }

  //  Remember the first fragment we add.
  int32 first_frag = GetNumCNS_AlignedContigElements(fragment_positions);

  for (int32 ifrag=0; ifrag<num_frags; ifrag++) {
    CNS_AlignedContigElement epos;
    IntMultiPos *frag = GetIntMultiPos(uma->f_list, ifrag);

    if (ExistsInHashTable_AS(unitigFrags, frag->ident, 0)) {
      fprintf(stderr,"SetUngappedFragmentPositions()-- ident %d already in hashtable\n", frag->ident);
      assert(0);
    }
    if (HASH_SUCCESS != InsertInHashTable_AS(unitigFrags, frag->ident, 0, 1, 0)) {
      fprintf(stderr,"SetUngappedFragmentPositions()-- Failure to insert ident %d in hashtable\n", frag->ident);
      assert(0);
    }

    assert(frag->position.bgn >= 0);
    assert(frag->position.bgn < num_columns + 1);
    assert(frag->position.end >= 0);
    assert(frag->position.end < num_columns + 1);

    epos.frg_or_utg                  = CNS_ELEMENT_IS_FRAGMENT;
    epos.idx.fragment.frgIdent       = frag->ident;
    epos.idx.fragment.frgType        = frag->type;
    epos.idx.fragment.frgContained   = frag->contained;
    epos.idx.fragment.frgInUnitig    = (type == AS_CONTIG) ? -1 : uma->maID;
    epos.position.bgn                = gapped_positions[frag->position.bgn];
    epos.position.end                = gapped_positions[frag->position.end];

    //fprintf(stderr, "SetUngappedFragmentPositions()-- FRG id=%d type=%c pos=%d,%d (orig pos=%d,%d)\n",
    //        frag->ident, frag->type, epos.position.bgn, epos.position.end, frag->position.bgn, frag->position.end);

    //  Adjust the ungapped position if we fall within a gap
    //
    if (epos.position.bgn == epos.position.end) {
      fprintf(stderr,"SetUngappedFragmentPositions()-- Encountered bgn==end=="F_S32" in ungapped coords within SetUngappedFragmentPositions for "F_CID "(gapped coords "F_S32","F_S32")\n",
              epos.position.bgn,frag->ident,frag->position.bgn,frag->position.end);
      assert(frag->position.bgn != frag->position.end);

      if (frag->position.bgn < frag->position.end) {
        if (epos.position.bgn > 0)
          epos.position.bgn--;
        else
          epos.position.end++;
      } else {
        if (epos.position.end > 0)
          epos.position.end--;
        else
          epos.position.bgn++;
      }
      fprintf(stderr,"SetUngappedFragmentPositions()--   Reset to "F_S32","F_S32"\n",
              epos.position.bgn,
              epos.position.end);
    }

    AppendVA_CNS_AlignedContigElement(fragment_positions, &epos);
  }


  for (int32 ifrag=0; ifrag < num_unitigs; ifrag++){
    CNS_AlignedContigElement epos;
    IntUnitigPos *unitig = GetIntUnitigPos(uma->u_list, ifrag);

    epos.frg_or_utg           = CNS_ELEMENT_IS_UNITIG;
    epos.idx.unitig.utgIdent  = unitig->ident;
    epos.idx.unitig.utgType   = unitig->type;
    epos.position.bgn         = gapped_positions[unitig->position.bgn];
    epos.position.end         = gapped_positions[unitig->position.end];

    //fprintf(stderr, "SetUngappedFragmentPositions()-- UTG id=%d type=%c pos=%d,%d (orig pos=%d,%d)\n",
    //        unitig->ident, unitig->type, epos.position.bgn, epos.position.end, unitig->position.bgn, unitig->position.end);

    AppendVA_CNS_AlignedContigElement(fragment_positions,&epos);
  }

  //  This is used only by ReplaceEndUnitigInContig().  Mark fragments in the "anchoring" contig
  //  that belong to this unitig.
  //
  if (type != AS_CONTIG) {
    Fragment *anchor = GetFragment(fragmentStore,0);

    if ((anchor != NULL) &&
        (anchor->type == AS_CONTIG)) {
      CNS_AlignedContigElement *af = GetCNS_AlignedContigElement(fragment_positions, anchor->components);

      for (int32 ifrag=0; ifrag < anchor->n_components; ifrag++, af++) {
        if ((af->frg_or_utg == CNS_ELEMENT_IS_FRAGMENT) &&
            (ExistsInHashTable_AS(unitigFrags, af->idx.fragment.frgIdent, 0)))
          af->idx.fragment.frgInUnitig = uma->maID;
      }
    }
  }

  DeleteHashTable_AS(unitigFrags);
  delete [] gapped_positions;

  return first_frag;
}