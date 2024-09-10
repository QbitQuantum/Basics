void
writeCCO(FILE *asmFile, bool doWrite) {
  SnapConConMesg      cco;
  GenericMesg         pmesg = { &cco, MESG_CCO };
  GraphNodeIterator   contigs;
  ContigT             *contig;

  fprintf(stderr, "writeCCO()--\n");

  InitGraphNodeIterator(&contigs, ScaffoldGraph->ContigGraph, GRAPH_NODE_DEFAULT);
  while ((contig = NextGraphNodeIterator(&contigs)) != NULL) {
    assert(contig->id >= 0);
    assert(contig->id < GetNumGraphNodes(ScaffoldGraph->ContigGraph));

    if (contig->flags.bits.isChaff)
      continue;

    NodeCGW_T *unitig = GetGraphNode(ScaffoldGraph->CIGraph, contig->info.Contig.AEndCI);

    if ((ScaffoldGraph->tigStore->getNumUnitigs(contig->id, FALSE) == 1) &&
        (contig->scaffoldID == NULLINDEX) &&
        (unitig->info.CI.numInstances > 0))
      //  Contig is a surrogate instance
      continue;

    MultiAlignT *ma = ScaffoldGraph->tigStore->loadMultiAlign(contig->id, FALSE);

    cco.eaccession  = AS_UID_fromInteger(getUID(uidServer));
    cco.iaccession  = contig->id;
    cco.placed      = ScaffoldGraph->tigStore->getContigStatus(contig->id);
    cco.length      = GetMultiAlignLength(ma);
    cco.consensus   = Getchar(ma->consensus, 0);
    cco.quality     = Getchar(ma->quality, 0);
    cco.forced      = 0;
    cco.num_pieces  = GetNumIntMultiPoss(ma->f_list);
    cco.num_unitigs = GetNumIntMultiPoss(ma->u_list);
    cco.num_vars    = GetNumIntMultiPoss(ma->v_list);
    cco.pieces      = NULL;
    cco.unitigs     = NULL;
    cco.vars        = NULL;

    if (cco.consensus == NULL)
      fprintf(stderr, "buildCCOMessage()-- contig %d missing consensus sequence\n",
              cco.iaccession);
    assert(cco.consensus != NULL);
    if (cco.length != strlen(cco.consensus))
      fprintf(stderr, "buildCCOMessage()-- contig %d length %d != consensus string length "F_SIZE_T"\n",
              cco.iaccession, cco.length, strlen(cco.consensus));
    assert(cco.length == strlen(cco.consensus));

    if (cco.num_pieces > 0) {
      cco.pieces = (SnapMultiPos *)safe_malloc(cco.num_pieces * sizeof(SnapMultiPos));

      for(int32 i=0; i<cco.num_pieces; i++) {
        IntMultiPos *imp = GetIntMultiPos(ma->f_list, i);

        cco.pieces[i].type         = imp->type;
        cco.pieces[i].eident       = FRGmap.lookup(imp->ident);
        cco.pieces[i].delta_length = imp->delta_length;
        cco.pieces[i].position     = imp->position;
        cco.pieces[i].delta        = imp->delta;
      }
    }

    if (cco.num_unitigs > 0) {
      cco.unitigs = (UnitigPos *)safe_malloc(cco.num_unitigs * sizeof(UnitigPos));

      for(int32 i=0; i<cco.num_unitigs; i++) {
        IntUnitigPos *imp = GetIntUnitigPos(ma->u_list, i);

        cco.unitigs[i].type         = imp->type;
        cco.unitigs[i].eident       = UTGmap.lookup(imp->ident);
        cco.unitigs[i].position     = imp->position;
        cco.unitigs[i].delta        = imp->delta;
        cco.unitigs[i].delta_length = imp->delta_length;
      }
    }

    if (cco.num_vars > 0) {
      cco.vars = (IntMultiVar *)safe_malloc(cco.num_vars * sizeof(IntMultiVar));

      for(int32 i=0; i<cco.num_vars; i++) {
        IntMultiVar *imv = GetIntMultiVar(ma->v_list, i);

        cco.vars[i].var_id                = imv->var_id;
        cco.vars[i].phased_id             = imv->phased_id;

        cco.vars[i].position              = imv->position;
        cco.vars[i].num_reads             = imv->num_reads;
        cco.vars[i].num_alleles           = imv->num_alleles;
        cco.vars[i].num_alleles_confirmed = imv->num_alleles_confirmed;
        cco.vars[i].min_anchor_size       = imv->min_anchor_size;
        cco.vars[i].var_length            = imv->var_length;

        cco.vars[i].alleles               = imv->alleles;
        cco.vars[i].var_seq_memory        = imv->var_seq_memory;
        cco.vars[i].read_id_memory        = imv->read_id_memory;

        cco.vars[i].enc_num_reads         = NULL;
        cco.vars[i].enc_weights           = NULL;
        cco.vars[i].enc_var_seq           = NULL;
        cco.vars[i].enc_read_ids          = NULL;
      }
    }

    if (doWrite)
      WriteProtoMesg_AS(asmFile, &pmesg);

    safe_free(cco.pieces);
    safe_free(cco.unitigs);
    safe_free(cco.vars);

    CCOmap.add(cco.iaccession, cco.eaccession);
  }
}