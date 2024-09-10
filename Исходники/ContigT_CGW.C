void
dumpContigInfo(ChunkInstanceT *contig) {
  int           contigOrientation;
  MultiAlignT  *ma;
  char         *seq1;
  int           len1;

  VA_TYPE(char) *consensus = CreateVA_char(2048);
  VA_TYPE(char) *quality   = CreateVA_char(2048);

  fprintf( stderr, "*********************** contig analysis **************************\n");
  fprintf( stderr, "analyzing contig: %d\n", contig->id);

  if (contig->offsetAEnd.mean < contig->offsetBEnd.mean)
    contigOrientation = 0;
  else
    contigOrientation = 1;

  fprintf(stderr, "contig orientation: %d\t length: %d  contig offsetAEnd: %d\t offsetBEnd: %d\n",
          contigOrientation,
          (int)contig->bpLength.mean,
          (int)contig->offsetAEnd.mean,
          (int)contig->offsetBEnd.mean);

  ma = ScaffoldGraph->tigStore->loadMultiAlign(contig->id, ScaffoldGraph->ContigGraph->type == CI_GRAPH);

  // Get the consensus sequences for the contig from the Store
  GetConsensus(ScaffoldGraph->ContigGraph, contig->id, consensus, quality);

  seq1 = Getchar(consensus, 0);
  len1 = strlen(seq1);

  if (contigOrientation == 1)
    reverseComplementSequence(seq1, len1);

  if (len1 < 5000) {
    fprintf( stderr, ">contig%d consensus seq (flipped to reflect scaff orientation)\n", contig->id);
    fprintf( stderr, "%s\n", seq1);
  } else {
    char tmpchar = seq1[2500];
    seq1[2500] = '\0';

    fprintf( stderr, ">contig%d left end\n", contig->id);
    fprintf( stderr, "%s\n", seq1);

    seq1[2500] = tmpchar;

    fprintf( stderr, ">contig%d right end\n", contig->id);
    fprintf( stderr, "%s\n", seq1 + len1 - 2501);
  }

#if 1
  int numUnitigs = GetNumIntUnitigPoss(ma->u_list);
  fprintf( stderr, "number unitigs: %d\n", numUnitigs);

  int i;
  for (i = 0; i < numUnitigs; i++) {
    IntUnitigPos *upos = GetIntUnitigPos( ma->u_list, i);
    ChunkInstanceT *unitig = GetGraphNode( ScaffoldGraph->CIGraph, upos->ident);
    MultiAlignT *uma = ScaffoldGraph->tigStore->loadMultiAlign(unitig->id, ScaffoldGraph->CIGraph->type == CI_GRAPH);
    IntMultiPos *ump;
    int icntfrag;

    fprintf( stderr, "  unitig: %d\t num frags: %ld surrogate: %d\n", unitig->id, GetNumIntMultiPoss(uma->f_list),
             (unitig->flags.bits.isStoneSurrogate || unitig->flags.bits.isWalkSurrogate));

    if (unitig->flags.bits.isStoneSurrogate ||
        unitig->flags.bits.isWalkSurrogate) {
      fprintf (stderr, "  surrogate unitig offsetAEnd: %f, offsetBEnd: %f\n", unitig->offsetAEnd.mean, unitig->offsetBEnd.mean);

      unitig = GetGraphNode( ScaffoldGraph->CIGraph, unitig->info.CI.baseID);
      fprintf ( stderr, "  using original unitig: %d\n", unitig->id);
      uma = ScaffoldGraph->tigStore->loadMultiAlign(unitig->id,
                                                    ScaffoldGraph->CIGraph->type == CI_GRAPH);
    }

    // now print out info on the frags in the unitig
    for (icntfrag = 0; icntfrag < GetNumIntMultiPoss(uma->f_list); icntfrag++) {
      IntMultiPos *imp = GetIntMultiPos(uma->f_list, icntfrag);
      CIFragT     *frag = GetCIFragT(ScaffoldGraph->CIFrags, imp->ident);

      fprintf(stderr, "    frag: %6d\t contig pos (5p, 3p): %6d, %6d\n",
              imp->ident, (int) frag->contigOffset5p.mean, (int) frag->contigOffset3p.mean);
    }
  }
#endif


#if 1
  CIEdgeT * e;
  GraphEdgeIterator edges(ScaffoldGraph->ContigGraph, contig->id, ALL_END, ALL_EDGES);

  //  FALSE == ITERATOR_VERBOSE

  while((e = edges.nextRaw()) != NULL)
    PrintGraphEdge( stderr, ScaffoldGraph->ContigGraph, "Analyzing edge", e, 0);
#endif

  DeleteVA_char(consensus);
  DeleteVA_char(quality);
}