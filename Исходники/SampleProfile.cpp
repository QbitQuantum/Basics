/// \brief Get the weight for an instruction.
///
/// The "weight" of an instruction \p Inst is the number of samples
/// collected on that instruction at runtime. To retrieve it, we
/// need to compute the line number of \p Inst relative to the start of its
/// function. We use HeaderLineno to compute the offset. We then
/// look up the samples collected for \p Inst using BodySamples.
///
/// \param Inst Instruction to query.
///
/// \returns the weight of \p Inst.
ErrorOr<uint64_t>
SampleProfileLoader::getInstWeight(const Instruction &Inst) const {
    DebugLoc DLoc = Inst.getDebugLoc();
    if (!DLoc)
        return std::error_code();

    const FunctionSamples *FS = findFunctionSamples(Inst);
    if (!FS)
        return std::error_code();

    const DILocation *DIL = DLoc;
    unsigned Lineno = DLoc.getLine();
    unsigned HeaderLineno = DIL->getScope()->getSubprogram()->getLine();

    uint32_t LineOffset = getOffset(Lineno, HeaderLineno);
    uint32_t Discriminator = DIL->getDiscriminator();
    ErrorOr<uint64_t> R = FS->findSamplesAt(LineOffset, Discriminator);
    if (R) {
        bool FirstMark =
            CoverageTracker.markSamplesUsed(FS, LineOffset, Discriminator, R.get());
        if (FirstMark) {
            const Function *F = Inst.getParent()->getParent();
            LLVMContext &Ctx = F->getContext();
            emitOptimizationRemark(
                Ctx, DEBUG_TYPE, *F, DLoc,
                Twine("Applied ") + Twine(*R) + " samples from profile (offset: " +
                Twine(LineOffset) +
                ((Discriminator) ? Twine(".") + Twine(Discriminator) : "") + ")");
        }
        DEBUG(dbgs() << "    " << Lineno << "." << DIL->getDiscriminator() << ":"
              << Inst << " (line offset: " << Lineno - HeaderLineno << "."
              << DIL->getDiscriminator() << " - weight: " << R.get()
              << ")\n");
    }
    return R;
}