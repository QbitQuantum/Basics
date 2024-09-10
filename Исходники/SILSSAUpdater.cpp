  /// Like ValueIsPHI but also check if the PHI has no source
  /// operands, i.e., it was just added.
  static SILArgument *ValueIsNewPHI(SILValue Val, SILSSAUpdater *Updater) {
    SILArgument *PHI = ValueIsPHI(Val, Updater);
    if (PHI) {
      auto *PhiBB = PHI->getParent();
      size_t PhiIdx = PHI->getIndex();

      // If all predecessor edges are 'not set' this is a new phi.
      for (auto *PredBB : PhiBB->getPreds()) {
        OperandValueArrayRef Edges =
            getEdgeValuesForTerminator(PredBB->getTerminator(), PhiBB);

        assert(PhiIdx < Edges.size() && "Not enough edges!");

        SILValue V = Edges[PhiIdx];
        // Check for the 'not set' sentinel.
        if (V.getDef() != Updater->PHISentinel.get())
          return nullptr;
      }
      return PHI;
    }
    return nullptr;
  }