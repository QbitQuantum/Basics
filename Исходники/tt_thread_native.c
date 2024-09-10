tt_result_t __thread_bind_numa(IN HANDLE hThread, IN USHORT Node)
{
    GROUP_AFFINITY ProcessorMask;

    // how to handle the arch in which a numa node includes more than
    // 64 cpus??

    if (!GetNumaNodeProcessorMaskEx(Node, &ProcessorMask)) {
        TT_ERROR("fail to get numa node processor mask");
        return TT_FAIL;
    }

    if (!SetThreadGroupAffinity(hThread, &ProcessorMask, NULL)) {
        TT_ERROR("fail to bind thread to numa node[%d]", Node);
        return TT_FAIL;
    }

    return TT_SUCCESS;
}