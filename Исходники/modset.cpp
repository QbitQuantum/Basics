void BlockModset::ComputeModset(BlockMemory *mcfg, bool indirect)
{
  static BaseTimer compute_timer("modset_compute");
  Timer _timer(&compute_timer);

  // get any indirect callees for this function, provided they have been
  // computed and stored in the callee database (indirect is set).
  CallEdgeSet *indirect_callees = NULL;
  if (indirect)
    indirect_callees = CalleeCache.Lookup(m_id->BaseVar());

  BlockCFG *cfg = mcfg->GetCFG();
  for (size_t eind = 0; eind < cfg->GetEdgeCount(); eind++) {
    PEdge *edge = cfg->GetEdge(eind);
    PPoint point = edge->GetSource();

    if (edge->IsAssign() || edge->IsCall()) {
      // process direct assignments along this edge.

      const Vector<GuardAssign>* assigns = mcfg->GetAssigns(point);
      if (assigns) {
        for (size_t aind = 0; aind < assigns->Size(); aind++) {
          const GuardAssign &gasn = assigns->At(aind);
          ProcessUpdatedLval(mcfg, gasn.left, NULL, true, false);

          Exp *use_lval = NULL;
          Exp *kind = mcfg->GetTerminateAssign(point, gasn.left, gasn.right,
                                               &use_lval);
          if (kind) {
            ProcessUpdatedLval(mcfg, use_lval, kind, false, false);
            kind->DecRef();
          }
        }
      }
    }

    // pull in modsets from the direct and indirect callees of the edge.
    if (BlockId *callee = edge->GetDirectCallee()) {
      ComputeModsetCall(mcfg, edge, callee, NULL);
      callee->DecRef();
    }
    else if (edge->IsCall() && indirect_callees) {
      for (size_t ind = 0; ind < indirect_callees->GetEdgeCount(); ind++) {
        const CallEdge &cedge = indirect_callees->GetEdge(ind);

        // when comparing watch out for the case that this is a temporary
        // modset and does not share the same block kind as the edge point.
        if (cedge.where.version == cfg->GetVersion() &&
            cedge.where.point == point &&
            cedge.where.id->Function() == m_id->Function() &&
            cedge.where.id->Loop() == m_id->Loop()) {
          cedge.callee->IncRef();
          BlockId *callee = BlockId::Make(B_Function, cedge.callee);

          ComputeModsetCall(mcfg, edge, callee, cedge.rfld_chain);
          callee->DecRef();
        }
      }
    }
  }

  // sort the modset exps to ensure a consistent representation.
  if (m_modset_list)
    SortVector<PointValue,compare_PointValue>(m_modset_list);
  if (m_assign_list)
    SortVector<GuardAssign,compare_GuardAssign>(m_assign_list);

  if (indirect)
    CalleeCache.Release(m_id->BaseVar());
}