tt_result_t __check_numa_node_id(tt_u32_t node_id)
{
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION info = NULL;
    DWORD info_len = 0;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION cur_info = NULL;
    tt_u32_t cur_len = 0;
    tt_result_t result = TT_FAIL;

    // get info
    if (!((GetLogicalProcessorInformation(info, &info_len) == FALSE) &&
          (GetLastError() == ERROR_INSUFFICIENT_BUFFER))) {
        return TT_FAIL;
    }
    info = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(info_len);
    if (info == NULL) {
        return TT_FAIL;
    }
    if (!GetLogicalProcessorInformation(info, &info_len)) {
        free(info);
        return TT_FAIL;
    }

    // enumerate info
    cur_info = info;
    while (cur_len < info_len) {
        if (cur_info->Relationship == RelationNumaNode) {
            if (cur_info->NumaNode.NodeNumber == node_id) {
                result = TT_SUCCESS;
                break;
            }
        }

        ++cur_info;
        cur_len += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    }
    free(info);
    return result;
}