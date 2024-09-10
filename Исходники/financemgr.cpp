void FinanceMgr::testClick(){
#if 0
	DepMgrUi ui(this);
	ui.show();


	Database* mysql = new QMySql;
	bool ok = mysql->connect("127.0.0.1", 3306, "gdf", "root", "");
	if (ok)
	{
		QMessageBox::about(this, tr("FinaceMgr"), tr("connect ok"));
	}

	Array x;
	x["money_direction"] = "D";
	x["title_code"] = "fadf3344";
	x["title_description"] = "中文测试";
	//mysql->insert("subtitle", x);
	//return;

	Database_Result& dr = mysql->query("SELECT * FROM subtitle WHERE id > 3");
	//Database_Result& dr = mysql->from("subtitle")->where("id > 3")->limit("1")->get();

	Array values;
	values["money_direction"] = "F";
	values["title_code"] = "vu";

	Array wheres;
	wheres["id"] = "3";
	bool bok = mysql->update("subtitle", values, wheres);
	mysql->del("subtitle", wheres);


	if ( (!dr.isValid()) || !dr.hasRecord())
	{
		QMessageBox::about(this, tr("FinaceMgr"), tr("query error:%1").arg(dr.errorMsg().c_str()));
		return;
	}

	ResultArray& rAry = dr.resultArray();
	foreach(Array ary, rAry)
	{
		QMessageBox::about(NULL, "test click", arrayToString(ary).c_str());
	}