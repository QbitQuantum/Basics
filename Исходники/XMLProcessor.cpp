bool XMLProcessor::process_node(bool hasReferTable, xml_node* currentNode, string referTableName, string referColumn, string referPrimaryKey)
{
	vector<xml_node> childnodesVecs;
	vector<pair<string, string>> columnNameandValues;
	string trueTableName;
	string originalTrueTableName = DBStringProcessor::getOriginalTrueTableName(currentNode->name());
	string hashTableValue = returnHashString(*currentNode);
	string mainKeyValue = "-1";
	for (xml_node_iterator it = currentNode->begin(); it != currentNode->end(); ++it)
	{
		if (it->first_child().name() == "")
		{
			string column_name = DBStringProcessor::getOriginalTrueTableName(it->name());
			cout << "name: " << it->name() << endl;
			string column_value = it->child_value();
			columnNameandValues.push_back(make_pair(column_name, column_value));
		}
		else
		{
			cout << it->name() << endl;
			childnodesVecs.push_back(*it);
		}
	}
	vector<string> columnVec;
	if (columnNameandValues.size() > 0)
	{
		for (vector<pair<string, string>>::iterator it = columnNameandValues.begin(); it != columnNameandValues.end(); it++)
		{
			columnVec.push_back(it->first);
		}
	}
	if (nodeToDBName[hashTableValue] == "")//if there is no corresponding table in database
	{
		if (currentNode->name() != "")//make sure it is not the root node
		{
			countSameNode[originalTrueTableName]++;//true name of table plus 1
			char str[10];
			_itoa_s(countSameNode[originalTrueTableName], str, 10);
			cout << originalTrueTableName + "_" + string(str) << endl;
			trueTableName = DBStringProcessor::getLowerCaseString(originalTrueTableName + "_" + string(str));
			nodeToDBName[hashTableValue] = trueTableName;
			dbConnect.insertTableOfHashNametoTrueName(hashTableValue, originalTrueTableName, string(str));
			cout << "Table " + trueTableName << " has not been created in database" << endl;
			if (hasReferTable)
			{
				dbConnect.createTable(hasReferTable, trueTableName, columnVec, referTableName, DBStringProcessor::getMainKeyString(referTableName));
			}
			else
			{
				dbConnect.createTable(hasReferTable, trueTableName, columnVec);
			}
		}
		else
		{
			cout << "Processing the root node!" << endl;
		}
	}
	else
	{
		cout << "Table " + trueTableName + " has already been created in database" << endl;
	}
	trueTableName = nodeToDBName[hashTableValue];
	if (currentNode->name() != "")
	{
		if (hasReferTable)
		{
			string referColumn = DBStringProcessor::getMainKeyString(referTableName);
			dbConnect.insertIntoTableandReturnMainKey(hasReferTable, trueTableName, columnNameandValues, mainKeyValue, referTableName, referColumn, referPrimaryKey);
		}
		else
		{
			dbConnect.insertIntoTableandReturnMainKey(hasReferTable, trueTableName, columnNameandValues, mainKeyValue);
		}
	}
	for (int index = 0; index < childnodesVecs.size(); index++)
	{
		string childTableName = DBStringProcessor::getOriginalTrueTableName(childnodesVecs[index].name());
		if (currentNode->name() != "")
			process_node(true, &childnodesVecs[index], trueTableName, DBStringProcessor::getMainKeyString(trueTableName), mainKeyValue);
		else
			process_node(false, &childnodesVecs[index]);
	}
	return true;
}