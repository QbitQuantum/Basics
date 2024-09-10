void SPUThread::dmaTransfer(U32 cmd, U32 eal, U32 lsa, U32 size) {
    if (cmd & (MFC_BARRIER_ENABLE | MFC_FENCE_ENABLE)) {
#ifdef NUCLEUS_ARCH_X86
        _mm_mfence();
#endif
    }

    const auto& memory = parent->memory;
    switch (cmd & ~(MFC_BARRIER_ENABLE | MFC_FENCE_ENABLE)) {
    case MFC_PUT_CMD:
    case MFC_PUTR_CMD:
        memcpy(memory->ptr(eal), memory->ptr(lsa), size);
        break;
    case MFC_GET_CMD:
        memcpy(memory->ptr(lsa), memory->ptr(eal), size);
        break;
    default:
        assert_true("Unexpected");
    }
}