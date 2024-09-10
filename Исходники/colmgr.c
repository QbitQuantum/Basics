BOOLEAN PhCmForwardSort(
    _In_ PPH_TREENEW_NODE *Nodes,
    _In_ ULONG NumberOfNodes,
    _In_ ULONG SortColumn,
    _In_ PH_SORT_ORDER SortOrder,
    _In_ PPH_CM_MANAGER Manager
    )
{
    PH_TREENEW_COLUMN tnColumn;
    PPH_CM_COLUMN column;
    PH_CM_SORT_CONTEXT sortContext;

    if (SortColumn < Manager->MinId)
        return FALSE;

    if (!TreeNew_GetColumn(Manager->Handle, SortColumn, &tnColumn))
        return TRUE;

    column = tnColumn.Context;

    if (!column->SortFunction)
        return TRUE;

    sortContext.SortFunction = column->SortFunction;
    sortContext.SubId = column->SubId;
    sortContext.Context = column->Context;
    sortContext.PostSortFunction = Manager->PostSortFunction;
    sortContext.SortOrder = SortOrder;
    qsort_s(Nodes, NumberOfNodes, sizeof(PVOID), PhCmpSortFunction, &sortContext);

    return TRUE;
}