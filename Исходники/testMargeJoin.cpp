int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db1(env->getEnv(), DB1);
	BDBOpe db2(env->getEnv(), DB2);
	Operator *o1, *o2, *o3, *o4;
	
	db1.open();
	db2.open();
	TABLE_REC tableRec1, tableRec2;
	
	tableRec1.tableID = DB1_tableID;
	tableRec1.attriNum = DB1_attriNum;
	tableRec2.tableID = DB2_tableID;
	tableRec2.attriNum = DB2_attriNum;
	
	ATTRIBUTE_REC attriRec1[tableRec1.attriNum];
	ATTRIBUTE_REC attriRec2[tableRec2.attriNum];
	AttributeManager AM(env->getEnv());
	
	AM.getForTableID(tableRec1, attriRec1);
	AM.getForTableID(tableRec2, attriRec2);
	
/* JOin target */
	OPERATION_NODE pn[2];
	pn[0].tableID = 15;
	pn[0].attributeID = 1;
	pn[0].option = 0;
	pn[1].tableID = 16;
	pn[1].attributeID = 1;
	pn[1].option = 0;

	
	JOIN_OPERATION_NODE jpn[1];
	jpn[0].rightNode = pn[0];
	jpn[0].leftNode = pn[1];
/* ============ */	

	o1 = new Scan_U2(&db1, attriRec1, DB1_attriNum, 1000000, 10);
	((Scan_U2 *)o1)->storeData();
	o2 = new Scan_U2(&db2, attriRec2, DB2_attriNum, 1000000, 10);
	((Scan_U2 *)o2)->storeData();
	
	o3 = new MargeJoin(o1, o2 , jpn, 1);
	o4 = new OutPut(TIME_OUT);

	o4->setPreOperator(o3);
	o4->init(env->getEnv());
	o4->exec();
}