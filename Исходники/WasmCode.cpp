/* static */ UniqueCodeSegment
CodeSegment::create(JSContext* cx,
                    const Bytes& bytecode,
                    const LinkData& linkData,
                    const Metadata& metadata,
                    HandleWasmMemoryObject memory)
{
    MOZ_ASSERT(bytecode.length() % gc::SystemPageSize() == 0);
    MOZ_ASSERT(linkData.globalDataLength % gc::SystemPageSize() == 0);
    MOZ_ASSERT(linkData.functionCodeLength < bytecode.length());

    auto cs = cx->make_unique<CodeSegment>();
    if (!cs)
        return nullptr;

    cs->bytes_ = AllocateCodeSegment(cx, bytecode.length() + linkData.globalDataLength);
    if (!cs->bytes_)
        return nullptr;

    uint8_t* codeBase = cs->base();

    cs->functionCodeLength_ = linkData.functionCodeLength;
    cs->codeLength_ = bytecode.length();
    cs->globalDataLength_ = linkData.globalDataLength;
    cs->interruptCode_ = codeBase + linkData.interruptOffset;
    cs->outOfBoundsCode_ = codeBase + linkData.outOfBoundsOffset;
    cs->unalignedAccessCode_ = codeBase + linkData.unalignedAccessOffset;
    cs->badIndirectCallCode_ = codeBase + linkData.badIndirectCallOffset;

    {
        JitContext jcx(CompileRuntime::get(cx->compartment()->runtimeFromAnyThread()));
        AutoFlushICache afc("CodeSegment::create");
        AutoFlushICache::setRange(uintptr_t(codeBase), cs->codeLength());

        memcpy(codeBase, bytecode.begin(), bytecode.length());
        StaticallyLink(*cs, linkData, cx);
        if (memory)
            SpecializeToMemory(*cs, metadata, memory);
    }

    if (!ExecutableAllocator::makeExecutable(codeBase, cs->codeLength())) {
        ReportOutOfMemory(cx);
        return nullptr;
    }

    if (!SendCodeRangesToProfiler(cx, *cs, bytecode, metadata))
        return nullptr;

    return cs;
}