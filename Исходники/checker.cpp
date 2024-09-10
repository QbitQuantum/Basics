void GetMatchingHeapWrites(const EscapeAccess &heap_write,
                           Vector<HeapWriteInfo> *writes)
{
  BlockId *id = heap_write.where.id;
  BlockMemory *mcfg = GetBlockMemory(id);

  if (mcfg == NULL) {
    logout << "WARNING: Missing memory: '" << id << "'" << endl;
    return;
  }

  BlockCFG *cfg = mcfg->GetCFG();

  // for incremental analysis, make sure the write CFG uses the right version.
  // as for checking callers, if the CFG has changed but the new one still
  // has a matching write, we will see an escape access for the new CFG.
  if (cfg->GetVersion() != heap_write.where.version) {
    if (checker_verbose.IsSpecified())
      logout << "CHECK: Write is an older version: "
             << heap_write.where.id << ": "
             << heap_write.where.version << endl;
    mcfg->DecRef();
    return;
  }

  PPoint point = heap_write.where.point;
  PPoint exit_point = mcfg->GetCFG()->GetExitPoint();

  // find a point-relative lvalue written at the write point with
  // the sanitized representation from the heap_write trace.
  // TODO: we only match against direct assignments in the CFG for now,
  // ignoring structural copies (which are simple recursive writes).

  PEdge *edge = cfg->GetSingleOutgoingEdge(point);
  Exp *point_lval = NULL;

  if (PEdgeAssign *nedge = edge->IfAssign())
    point_lval = nedge->GetLeftSide();
  else if (PEdgeCall *nedge = edge->IfCall())
    point_lval = nedge->GetReturnValue();

  bool lval_matches = false;

  if (point_lval) {
    if (Exp *new_point_lval = Trace::SanitizeExp(point_lval)) {
      lval_matches = (new_point_lval == heap_write.target->GetValue());
      new_point_lval->DecRef();
    }
  }

  if (!lval_matches) {
    mcfg->DecRef();
    return;
  }

  // it would be nice to remove Val() expressions from this list, but we can't
  // do that as lvalues in memory assignments can contain Val and we want to
  // see the effects of those assignments. TODO: fix.
  GuardExpVector lval_res;
  mcfg->TranslateExp(TRK_Point, point, point_lval, &lval_res);

  for (size_t ind = 0; ind < lval_res.Size(); ind++) {
    const GuardExp &lv = lval_res[ind];

    HeapWriteInfo info;
    info.mcfg = mcfg;
    info.lval = lv.exp;
    info.base_lval = point_lval;

    // look for a condition where the lvalue is not written.
    GuardExpVector exit_vals;
    info.mcfg->GetValComplete(info.lval, NULL, exit_point, &exit_vals);

    for (size_t ind = 0; ind < exit_vals.Size(); ind++) {
      const GuardExp &val = exit_vals[ind];

      // exclude cases where the lvalue refers to its value at block entry.
      if (ExpDrf *nval = val.exp->IfDrf()) {
        if (nval->GetTarget() == info.lval)
          info.exclude.PushBack(val.guard);
      }
    }

    if (!writes->Contains(info)) {
      info.mcfg->IncRef(writes);
      info.lval->IncRef(writes);
      info.base_lval->IncRef(writes);
      IncRefVector<Bit>(info.exclude, writes);
      writes->PushBack(info);
    }
  }

  mcfg->DecRef();
}