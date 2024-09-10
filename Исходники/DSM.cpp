int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db_l_5(env->getEnv(), "8.5.DSM");
	BDBOpe db_l_6(env->getEnv(), "8.6.DSM");
	BDBOpe db_l_7(env->getEnv(), "8.7.DSM");
	BDBOpe db_l_11(env->getEnv(), "8.11.DSM");
	
	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12;
	
	db_l_5.open();
	db_l_6.open();
	db_l_7.open();
	db_l_11.open();
	
	TABLE_REC tableRec_l;
	tableRec_l.tableID = 8;
	tableRec_l.attriNum = 16;
	ATTRIBUTE_REC attriRec_l[tableRec_l.attriNum];
	AttributeManager AM(env->getEnv());
	
	AM.getForTableID(tableRec_l, attriRec_l);
	
/* selection1 */

	DatePosVal pv1(1,(unsigned char *)"1994-01-01");

	ValueNode vn1 = ValueNode(&pv1);
	ColumnRefNode cn1;
	cn1.tableID = 8;
	cn1.attriID = 11;
	AxprNode an1 = AxprNode(GE, &cn1, &vn1);
	


	DatePosVal pv2(1,(unsigned char *)"1995-01-01");

	ValueNode vn2 = ValueNode(&pv2);
	ColumnRefNode cn2;
	cn2.tableID = 8;
	cn2.attriID = 11;
	AxprNode an2 = AxprNode(LT, &cn2, &vn2);
	
	AxprNode an7 = AxprNode(AND, &an1, &an2);
	
/* selection3 */

	FloatPosVal pv3(1, 0.06-0.01);
	FloatPosVal pv4(1, 0.06+0.01);
	

	ValueNode vn3 = ValueNode(&pv3);
	ValueNode vn4 = ValueNode(&pv4);
	ColumnRefNode cn3;
	cn3.tableID = 8;
	cn3.attriID = 7;
	AxprNode an3 = AxprNode(GE, &cn3, &vn3);
	AxprNode an4 = AxprNode(LE, &cn3, &vn4);
	AxprNode an5 = AxprNode(AND, &an3, &an4);
	
/* selection4 */

	FloatPosVal pv5(1, 24);

	ValueNode vn5 = ValueNode(&pv5);
	ColumnRefNode cn4;
	cn4.tableID = 8;
	cn4.attriID = 5;
	AxprNode an6 = AxprNode(LT, &cn4, &vn5);
	
	
/* AGGREGATION */
	ColumnRefNode cn5[2];
	cn5[0].tableID = 8;
	cn5[0].attriID = 6;
	cn5[1].tableID = 8;
	cn5[1].attriID = 7;
	ArithmeticNode arith1(MUL, &cn5[0], &cn5[1]);
	
	Aggregation *aggre[1];
	aggre[0] = new Sum(&arith1, 2);
	
	
	
	OPERATION_NODE op1;
	op1.tableID = 8;
	op1.attributeID = 7;
	
	
	
	o1 = new ScanDSM(&db_l_11, &attriRec_l[10], 1);
//	cout << "OK new o1" << endl;
	
	o2 = new SelectBitOut((Node *)&an7 ,(unsigned int)2);
//	cout << "OK new o2" << endl;
	o2->setPreOperator(o1);
	
	o3 = new ScanDSM(&db_l_5, &attriRec_l[4], 1);
//	cout << "OK new o3" << endl;
	
	o4 = new BitFilter(o3, o2);
//	cout << "OK new o4" << endl;
	
	o5 = new Selection((Node *)&an6 ,(unsigned int)1);
//	cout << "OK new o5" << endl;
	o5->setPreOperator(o4);
	
	o6 = new ScanDSM(&db_l_7, &attriRec_l[6], 1);
//	cout << "OK new o6" << endl;

	o7 = new Selection((Node *)&an5 ,(unsigned int)2);
//	cout << "OK new o7" << endl;
	o7->setPreOperator(o6);
	
	o8 = new ScanFromJI(o5, o7, &op1);
//	cout << "OK new o8" << endl;
	
	o9 = new ScanDSM(&db_l_6, &attriRec_l[5], 1);
//	cout << "OK new o9" << endl;
	
	o10 = new ScanFromJI(o9, o8, &op1);
//	cout << "OK new o10" << endl;
	
	o11 = new AggreOut(aggre, 1);
	o11->setPreOperator(o10);
//	cout << "OK new o11" << endl;
	
	o12 = new OutPut(STD_OUT);
//	cout << "OK new o12" << endl;
	o12->setPreOperator(o11);
	o12->init(env->getEnv());
	cout << "TEST START" << endl;
	
	cout << setprecision(6);
	cout << setiosflags(ios::fixed); 
	o12->exec();
}