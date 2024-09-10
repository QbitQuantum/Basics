// 測試 讀檔第2部分Connections
TEST_F(ER_ModelTest, loadConnections) 
{
	// 測試
	// 參數:vector<string>::iterator(linIt), map<int, string> &(connectionMap)
	// 回傳:無
	// 附註:建置model內容
	ER_FileManager file;
	file.openFile("unittest//test_file1_part2.erd", ER_FileManager::Read);
	string content = file.readFile();
	vector<string> lines;
	lines = Tool_Function::split(content, '\n');
	// 建立資料
	map<int, string> connectionMap;
	connectionMap.insert(pair<int, string> (7, ""));
	connectionMap.insert(pair<int, string> (8, ""));
	connectionMap.insert(pair<int, string> (9, ""));
	connectionMap.insert(pair<int, string> (10, ""));
	connectionMap.insert(pair<int, string> (11, "1"));
	connectionMap.insert(pair<int, string> (12, "1"));
	connectionMap.insert(pair<int, string> (14, ""));

	model->addNode(ERD_Component::Entity, "Engineer");  //id=0
	model->addNode(ERD_Component::Attribute, "EmpID");  //id=1
	model->addNode(ERD_Component::Relationship, "Has");   //id=2
	model->addNode(ERD_Component::Attribute, "Name");   //id=3
	model->addNode(ERD_Component::Entity, "PC");  //id=4
	model->addNode(ERD_Component::Attribute, "PC_ID");   //id=5
	model->addNode(ERD_Component::Attribute, "Purchase_Date");   //id=6
	model->addNode(ERD_Component::Attribute, "Department", 13);   //id=13
	// 建立資料end

	for (vector<string>::iterator it = lines.begin(); it < lines.end(); it++)
	{
		model->loadConnections(it, connectionMap);
	}
	file.closeFile();
	EXPECT_EQ(15, model->getComponents().size());
}