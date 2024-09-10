// In profiling mode, we need to maintain fp so that we can unwind the stack at
// any pc. In non-profiling mode, the only way to observe AsmJSActivation::fp is
// to call out to C++ so, as an optimization, we don't update fp. To avoid
// recompilation when the profiling mode is toggled, we generate both prologues
// a priori and switch between prologues when the profiling mode is toggled.
// Specifically, AsmJSModule::setProfilingEnabled patches all callsites to
// either call the profiling or non-profiling entry point.
void
js::GenerateAsmJSFunctionPrologue(MacroAssembler &masm, unsigned framePushed,
                                  AsmJSFunctionLabels *labels)
{
#if defined(JS_CODEGEN_ARM)
    // Flush pending pools so they do not get dumped between the 'begin' and
    // 'entry' labels since the difference must be less than UINT8_MAX.
    masm.flushBuffer();
#endif

    masm.align(CodeAlignment);

    GenerateProfilingPrologue(masm, framePushed, AsmJSExit::None, &labels->begin);
    Label body;
    masm.jump(&body);

    // Generate normal prologue:
    masm.align(CodeAlignment);
    masm.bind(&labels->entry);
    PushRetAddr(masm);
    masm.subPtr(Imm32(framePushed + AsmJSFrameBytesAfterReturnAddress), StackPointer);

    // Prologue join point, body begin:
    masm.bind(&body);
    masm.setFramePushed(framePushed);

    // Overflow checks are omitted by CodeGenerator in some cases (leaf
    // functions with small framePushed). Perform overflow-checking after
    // pushing framePushed to catch cases with really large frames.
    if (labels->overflowThunk) {
        // If framePushed is zero, we don't need a thunk to adjust StackPointer.
        Label *target = framePushed ? labels->overflowThunk.ptr() : &labels->overflowExit;
        masm.branchPtr(Assembler::AboveOrEqual,
                       AsmJSAbsoluteAddress(AsmJSImm_StackLimit),
                       StackPointer,
                       target);
    }
}