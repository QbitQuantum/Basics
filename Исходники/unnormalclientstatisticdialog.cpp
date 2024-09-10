void UnnormalClientStatisticDialog::doStatistic()
{
	boost::shared_ptr<ClientGroupCenter> groupCenter = g_DataCenter->createClientGroupCenter();
	UnnormalStateCenter *unnormalStateCenter = g_DataCenter->createUnnormalStateCenter();

	QHash<int,int> groupIdToTableIndex;

	//添加好每一客户组对应的行
	for(ClientGroupCenter::Iterator it = groupCenter->begin();
	it != groupCenter->end();
	++it)
	{
		int row = m_Table->rowCount();
		m_Table->insertRow(row);
		m_Table->setItem(row, 0, new QTableWidgetItem( (*it)->getName() ));
		m_Table->setItem(row, 1, new QTableWidgetItem( QString::number(( *it)->getClientCount())) );
		groupIdToTableIndex.insert((*it)->getId(), row);
	}

	//添加一个总和行
	int allCount = m_Table->rowCount();
	m_Table->insertRow(allCount);
	m_Table->setVerticalHeaderItem(allCount, new QTableWidgetItem(tr("总和")) );
	m_Table->setItem(allCount,0, new QTableWidgetItem(tr("总和")) );
	m_Table->setItem(m_Table->rowCount()-1, 1,
					 new QTableWidgetItem(QString::number(g_DataCenter->createClientCenter()->getClientCount())));

	//设置好异常信息的每一列
	eachColumnCount(2, unnormalStateCenter->m_TempSet, groupIdToTableIndex);
	eachColumnCount(3, unnormalStateCenter->m_HumiSet, groupIdToTableIndex);
	eachColumnCount(4, unnormalStateCenter->m_GlassSet, groupIdToTableIndex);
	eachColumnCount(5, unnormalStateCenter->m_DoorSet, groupIdToTableIndex);
	eachColumnCount(6, unnormalStateCenter->m_PowerSet, groupIdToTableIndex);
	eachColumnCount(7, unnormalStateCenter->m_ScreenSet, groupIdToTableIndex);


	//设置好总和行
	int allSum = 0;
	for(int rowIndex = 0; rowIndex < m_Table->rowCount() - 1; ++rowIndex)
	{
		int sum = 0;
		for(int colIndex = 2; colIndex < m_Table->columnCount() - 1; ++colIndex)
		{
			sum += m_Table->item(rowIndex, colIndex)->text().toInt();
		}
		QTableWidgetItem *sumItem = new QTableWidgetItem(QString::number(sum));
		if(sum != 0)
		{
			sumItem->setTextColor(QColor("red"));
		}
		m_Table->setItem(rowIndex, m_Table->columnCount()-1, sumItem);
		allSum += sum;
	}

	QTableWidgetItem *allSumItem = new QTableWidgetItem(QString::number(allSum));
	if(allSum != 0)
	{
		allSumItem->setTextColor(QColor("red"));
	}
	m_Table->setItem(m_Table->rowCount()-1, m_Table->columnCount()-1, allSumItem);
}