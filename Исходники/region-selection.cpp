RegionDescPtr selectTraceletLegacy(const RegionContext&    rCtx,
                                   const Transl::Tracelet& tlet) {
  typedef RegionDesc::Block Block;

  auto region = std::make_shared<RegionDesc>();
  SrcKey sk(tlet.m_sk);
  auto unit = tlet.func()->unit();

  const Func* topFunc = nullptr;
  Block* curBlock = nullptr;
  auto newBlock = [&](const Func* func, SrcKey start, Offset spOff) {
    assert(curBlock == nullptr || curBlock->length() > 0);
    region->blocks.push_back(
      std::make_shared<Block>(func, start.offset(), 0, spOff));
    curBlock = region->blocks.back().get();
  };
  newBlock(tlet.func(), sk, rCtx.spOffset);

  for (auto ni = tlet.m_instrStream.first; ni; ni = ni->next) {
    assert(sk == ni->source);
    assert(ni->unit() == unit);

    Offset curSpOffset = rCtx.spOffset + ni->stackOffset;

    curBlock->addInstruction();
    if ((curBlock->length() == 1 && ni->funcd != nullptr) ||
        ni->funcd != topFunc) {
      topFunc = ni->funcd;
      curBlock->setKnownFunc(sk, topFunc);
    }

    if (ni->calleeTrace && !ni->calleeTrace->m_inliningFailed) {
      assert(ni->op() == OpFCall);
      assert(ni->funcd == ni->calleeTrace->func());
      // This should be translated as an inlined call. Insert the blocks of the
      // callee in the region.
      auto const& callee = *ni->calleeTrace;
      curBlock->setInlinedCallee(ni->funcd);
      SrcKey cSk = callee.m_sk;
      Unit* cUnit = callee.func()->unit();

      newBlock(callee.func(), cSk, curSpOffset);

      for (auto cni = callee.m_instrStream.first; cni; cni = cni->next) {
        assert(cSk == cni->source);
        assert(cni->op() == OpRetC ||
               cni->op() == OpContRetC ||
               cni->op() == OpNativeImpl ||
               !instrIsNonCallControlFlow(cni->op()));

        curBlock->addInstruction();
        cSk.advance(cUnit);
      }

      if (ni->next) {
        sk.advance(unit);
        newBlock(tlet.func(), sk, curSpOffset);
      }
      continue;
    }

    if (!ni->noOp && isFPassStar(ni->op())) {
      curBlock->setParamByRef(sk, ni->preppedByRef);
    }

    if (ni->next && ni->op() == OpJmp) {
      // A Jmp that isn't the final instruction in a Tracelet means we traced
      // through a forward jump in analyze. Update sk to point to the next NI
      // in the stream.
      auto dest = ni->offset() + ni->imm[0].u_BA;
      assert(dest > sk.offset()); // We only trace for forward Jmps for now.
      sk.setOffset(dest);

      // The Jmp terminates this block.
      newBlock(tlet.func(), sk, curSpOffset);
    } else {
      sk.advance(unit);
    }
  }

  auto& frontBlock = *region->blocks.front();

  // Add tracelet guards as predictions on the first instruction. Predictions
  // and known types from static analysis will be applied by
  // Translator::translateRegion.
  for (auto const& dep : tlet.m_dependencies) {
    if (dep.second->rtt.isVagueValue() ||
        dep.second->location.isThis()) continue;

    typedef RegionDesc R;
    auto addPred = [&](const R::Location& loc) {
      auto type = Type(dep.second->rtt);
      frontBlock.addPredicted(tlet.m_sk, {loc, type});
    };

    switch (dep.first.space) {
      case Transl::Location::Stack: {
        uint32_t offsetFromSp = uint32_t(-dep.first.offset - 1);
        uint32_t offsetFromFp = rCtx.spOffset - offsetFromSp;
        addPred(R::Location::Stack{offsetFromSp, offsetFromFp});
        break;
      }
      case Transl::Location::Local:
        addPred(R::Location::Local{uint32_t(dep.first.offset)});
        break;

      default: not_reached();
    }
  }

  // Add reffiness dependencies as predictions on the first instruction.
  for (auto const& dep : tlet.m_refDeps.m_arMap) {
    RegionDesc::ReffinessPred pred{dep.second.m_mask,
                                   dep.second.m_vals,
                                   dep.first};
    frontBlock.addReffinessPred(tlet.m_sk, pred);
  }

  FTRACE(2, "Converted Tracelet:\n{}\nInto RegionDesc:\n{}\n",
         tlet.toString(), show(*region));
  return region;
}