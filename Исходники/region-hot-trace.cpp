RegionDescPtr selectHotTrace(TransID triggerId,
                             const ProfData* profData,
                             TransCFG& cfg,
                             TransIDSet& selectedSet) {
  JIT::RegionDescPtr region = smart::make_unique<JIT::RegionDesc>();
  TransID tid    = triggerId;
  TransID prevId = InvalidID;
  selectedSet.clear();

  while (!setContains(selectedSet, tid)) {

    RegionDesc::BlockPtr block = profData->transBlock(tid);
    if (block == nullptr) break;

    // If the debugger is attached, only allow single-block regions.
    if (prevId != InvalidID && isDebuggerAttachedProcess()) {
      FTRACE(5, "selectHotRegion: breaking region at Translation {} "
             "because of debugger is attached\n", tid);
      break;
    }

    // Break if block is not the first and requires reffiness checks.
    // Task #2589970: fix translateRegion to support mid-region reffiness checks
    if (prevId != InvalidID) {
      auto nRefDeps = block->reffinessPreds().size();
      if (nRefDeps > 0) {
        FTRACE(5, "selectHotRegion: breaking region because of refDeps ({}) at "
               "Translation {}\n", nRefDeps, tid);
        break;
      }
    }

    // Break trace if translation tid cannot follow the execution of
    // the entire translation prevTd.  This can only happen if the
    // execution of prevId takes a side exit that leads to the
    // execution of tid.
    if (prevId != InvalidID) {
      Op* lastInstr = profData->transLastInstr(prevId);
      const Unit* unit = profData->transFunc(prevId)->unit();
      OffsetSet succOffs = findSuccOffsets(lastInstr, unit);
      if (!setContains(succOffs, profData->transSrcKey(tid).offset())) {
        if (HPHP::Trace::moduleEnabled(HPHP::Trace::pgo, 5)) {
          FTRACE(5, "selectHotTrace: WARNING: Breaking region @: {}\n",
                 JIT::show(*region));
          FTRACE(5, "selectHotTrace: next translation selected: tid = {}\n{}\n",
                 tid, JIT::show(*block));
          std::string succStr("succOffs = ");
          for (auto succ : succOffs) {
            succStr += lexical_cast<std::string>(succ);
          }
          FTRACE(5, "\n{}\n", succStr);
        }
        break;
      }
    }
    region->blocks.emplace_back(block);
    selectedSet.insert(tid);

    Op lastOp = *(profData->transLastInstr(tid));
    if (breaksRegion(lastOp)) {
      FTRACE(5, "selectHotTrace: breaking region because of last instruction "
             "in Translation {}: {}\n", tid, opcodeToName(lastOp));
      break;
    }

    auto outArcs = cfg.outArcs(tid);
    if (outArcs.size() == 0) {
      FTRACE(5, "selectHotTrace: breaking region because there's no successor "
             "for Translation {}\n", tid);
      break;
    }

    auto maxWeight = std::numeric_limits<int64_t>::min();
    TransCFG::Arc* maxArc = nullptr;
    for (auto arc : outArcs) {
      if (arc->weight() >= maxWeight) {
        maxWeight = arc->weight();
        maxArc = arc;
      }
    }
    assert(maxArc != nullptr);

    prevId = tid;
    tid = maxArc->dst();
  }

  return region;
}