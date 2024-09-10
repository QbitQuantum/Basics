bool
ModuleGenerator::finishLinkData(Bytes& code)
{
    // Inflate the global bytes up to page size so that the total bytes are a
    // page size (as required by the allocator functions).
    linkData_.globalDataLength = AlignBytes(linkData_.globalDataLength, gc::SystemPageSize());

    // Add links to absolute addresses identified symbolically.
    for (size_t i = 0; i < masm_.numAsmJSAbsoluteAddresses(); i++) {
        AsmJSAbsoluteAddress src = masm_.asmJSAbsoluteAddress(i);
        if (!linkData_.symbolicLinks[src.target].append(src.patchAt.offset()))
            return false;
    }

    // Relative link metadata: absolute addresses that refer to another point within
    // the asm.js module.

    // CodeLabels are used for switch cases and loads from floating-point /
    // SIMD values in the constant pool.
    for (size_t i = 0; i < masm_.numCodeLabels(); i++) {
        CodeLabel cl = masm_.codeLabel(i);
        LinkData::InternalLink inLink(LinkData::InternalLink::CodeLabel);
        inLink.patchAtOffset = masm_.labelToPatchOffset(*cl.patchAt());
        inLink.targetOffset = cl.target()->offset();
        if (!linkData_.internalLinks.append(inLink))
            return false;
    }

#if defined(JS_CODEGEN_X86)
    // Global data accesses in x86 need to be patched with the absolute
    // address of the global. Globals are allocated sequentially after the
    // code section so we can just use an InternalLink.
    for (GlobalAccess a : masm_.globalAccesses()) {
        LinkData::InternalLink inLink(LinkData::InternalLink::RawPointer);
        inLink.patchAtOffset = masm_.labelToPatchOffset(a.patchAt);
        inLink.targetOffset = code.length() + a.globalDataOffset;
        if (!linkData_.internalLinks.append(inLink))
            return false;
    }
#elif defined(JS_CODEGEN_X64)
    // Global data accesses on x64 use rip-relative addressing and thus we can
    // patch here, now that we know the final codeLength.
    for (GlobalAccess a : masm_.globalAccesses()) {
        void* from = code.begin() + a.patchAt.offset();
        void* to = code.end() + a.globalDataOffset;
        X86Encoding::SetRel32(from, to);
    }
#else
    // Global access is performed using the GlobalReg and requires no patching.
    MOZ_ASSERT(masm_.globalAccesses().length() == 0);
#endif

    return true;
}