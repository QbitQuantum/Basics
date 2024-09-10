NTSTATUS RemoveMatchExpression(__in WCHAR Expression[], __in ULONG ExpressionLength)
{
	// 这里要先判断链表是否为空
	if (IsListEmpty(&MatchExpressionList.HeadList))
	{
		KdPrint(("[ISISandBox] RemoveMatchExpression -> List is empty.\n"));
		return STATUS_SUCCESS;
	}

	KdPrint(("[ISISandBox] RemoveMatchExpression -> Get spinlock.\n"));
	KIRQL irql;
	KeAcquireSpinLock(&MatchExpressionList.Lock, &irql);

	// 链表头
	PLIST_ENTRY pList = MatchExpressionList.HeadList.Flink;

	BOOLEAN isFind = FALSE;
	while (pList != &MatchExpressionList.HeadList)
	{
		PMATCH_EXPRESSION element = CONTAINING_RECORD(pList, MATCH_EXPRESSION, ListEntry);

		if (RtlCompareMemory(element->Expression, Expression, ExpressionLength) == ExpressionLength)
		{
			pList->Blink->Flink = pList->Flink;
			pList->Flink->Blink = pList->Blink;
			pList = pList->Flink;

			// 这里的指针都已经断开了，即链表中不存在element了，现在只需要将其内存释放就OK了
			ExFreeToPagedLookasideList(&MatchExpressionList.PageList, element);
			KdPrint(("[ISISandBox] RemoveMatchExpression Delete expression | Expression : %S.\n", Expression));

			isFind = TRUE;
			break;
		}

		pList = pList->Flink;
	}

	KeReleaseSpinLock(&MatchExpressionList.Lock, irql);

	if (isFind)
		return STATUS_SUCCESS;
	else
	{
		KdPrint(("[ISISandBox] RemoveMatchExpression Cannot find expression : %S.\n", Expression));
		return STATUS_NOT_FOUND;
	}
}