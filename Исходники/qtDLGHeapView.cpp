void qtDLGHeapView::OnSelectionChanged()
{
	HEAPENTRY32 he;
	ZeroMemory(&he, sizeof(HEAPENTRY32));
	he.dwSize = sizeof(HEAPENTRY32);

	if(tblHeapView->selectedItems().size() <= 0) 
	{
		tblHeapBlocks->setRowCount(0);
		return;
	}

	quint64 PID = tblHeapView->selectedItems()[0]->text().toULongLong(0,16),
			heapID = tblHeapView->selectedItems()[1]->text().toULongLong(0,16),
			blockCount = NULL;

	if(Heap32First(&he,PID,heapID))
	{
		tblHeapBlocks->setRowCount(0);
		do
		{
			tblHeapBlocks->insertRow(tblHeapBlocks->rowCount());
			// PID
			tblHeapBlocks->setItem(tblHeapBlocks->rowCount() - 1,0,
				new QTableWidgetItem(QString().sprintf("%08X",PID)));

			// Heap ID
			tblHeapBlocks->setItem(tblHeapBlocks->rowCount() - 1,1,
				new QTableWidgetItem(QString().sprintf("%08X",he.th32HeapID)));

			// Base Address
			tblHeapBlocks->setItem(tblHeapBlocks->rowCount() - 1,2,
				new QTableWidgetItem(QString().sprintf("%08X",he.dwAddress)));

			// Allocated Size
			tblHeapBlocks->setItem(tblHeapBlocks->rowCount() - 1,3,
				new QTableWidgetItem(QString().sprintf("%08X",he.dwBlockSize)));

			// Block Count
			tblHeapBlocks->setItem(tblHeapBlocks->rowCount() - 1,4,
				new QTableWidgetItem(QString().sprintf("%d",++blockCount)));

			// Flags
			switch(he.dwFlags)
			{
			case LF32_FIXED:
				tblHeapBlocks->setItem(tblHeapBlocks->rowCount() - 1,5,
					new QTableWidgetItem(QString("LF32_FIXED")));
				break;
			case LF32_FREE:
				tblHeapBlocks->setItem(tblHeapBlocks->rowCount() - 1,5,
					new QTableWidgetItem(QString("LF32_FREE")));
				break;
			case LF32_MOVEABLE:
				tblHeapBlocks->setItem(tblHeapBlocks->rowCount() - 1,5,
					new QTableWidgetItem(QString("LF32_MOVEABLE")));
				break;
			default:
				tblHeapBlocks->setItem(tblHeapBlocks->rowCount() - 1,5,
					new QTableWidgetItem(""));
				break;
			}

			he.dwSize = sizeof(HEAPENTRY32);
		}while(Heap32Next(&he));
	}
}