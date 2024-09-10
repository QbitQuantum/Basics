int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db_r_1(env->getEnv(), "1.1.DSM");
	BDBOpe db_r_2(env->getEnv(), "1.2.DSM");
	BDBOpe db_n_1(env->getEnv(), "2.1.DSM");
	BDBOpe db_n2_1(env->getEnv(), "2.1.DSM");
	BDBOpe db_n2_2(env->getEnv(), "2.2.DSM");
	BDBOpe db_n_3(env->getEnv(), "2.3.DSM");
	BDBOpe db_s_1(env->getEnv(), "3.1.DSM");
	BDBOpe db_s_4(env->getEnv(), "3.4.DSM");
	BDBOpe db_p_1(env->getEnv(), "4.1.DSM");
	BDBOpe db_p_5(env->getEnv(), "4.5.DSM");
	BDBOpe db_c_1(env->getEnv(), "6.1.DSM");
	BDBOpe db_c_4(env->getEnv(), "6.4.DSM");
	BDBOpe db_o(env->getEnv(), "ORDERS.row");
	BDBOpe db_l(env->getEnv(), "LINEITEM.row");
	
	SecondDB *sDB1;
	int (*pf1)(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
	pf1 = L_1_secondary;
	sDB1 = new SecondDB(env->getEnv(), "8.1.secondary");
	sDB1->setNumCmp();
	
	SecondDB *sDB2;
	int (*pf2)(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
	pf2 = O_2_secondary;
	sDB2 = new SecondDB(env->getEnv(), "7.2.secondary");
	sDB2->setNumCmp();

	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12, *o13, *o14, *o15, *o16, *o17, *o18, *o19, *o20;
	Operator *o21, *o22, *o23, *o24, *o25, *o26, *o27, *o28, *o29, *o30;
	Operator *o31, *o32, *o33, *o34, *o35, *o36, *o37, *o38, *o39, *o40;
	Operator *o41, *o42, *o43, *o44, *o45, *o46, *o47, *o48, *o49, *o50, *o51;
	db_r_1.open();
	db_r_2.open();
	db_n_1.open();
	db_n2_1.open();
	db_n2_2.open();
	db_n_3.open();
	db_s_1.open();
	db_s_4.open();
	db_p_1.open();
	db_p_5.open();
	db_c_1.open();
	db_c_4.open();
	
	
	db_o.open();
	sDB2->open(0);
	db_o.associate(sDB2->getDb(), pf2);
	sDB2->openCursor();
	
	db_l.open();
	sDB1->open(0);
	db_l.associate(sDB1->getDb(), pf1);
	sDB1->openCursor();

	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n;
	TABLE_REC tableRec_s;
	TABLE_REC tableRec_p;
	TABLE_REC tableRec_c;
	TABLE_REC tableRec_o;
	TABLE_REC tableRec_l;

	tableRec_r.tableID = 1;
	tableRec_r.attriNum = 3;

	tableRec_n.tableID = 2;
	tableRec_n.attriNum = 4;
	
	tableRec_s.tableID = 3;
	tableRec_s.attriNum = 7;
	
	tableRec_p.tableID = 4;
	tableRec_p.attriNum = 9;
	
	tableRec_c.tableID = 6;
	tableRec_c.attriNum = 8;
	
	tableRec_o.tableID = 7;
	tableRec_o.attriNum = 9;
	
	tableRec_l.tableID = 8;
	tableRec_l.attriNum = 16;
	
	
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n[tableRec_n.attriNum];
	ATTRIBUTE_REC attriRec_s[tableRec_s.attriNum];
	ATTRIBUTE_REC attriRec_p[tableRec_p.attriNum];
	ATTRIBUTE_REC attriRec_c[tableRec_c.attriNum];
	ATTRIBUTE_REC attriRec_o[tableRec_o.attriNum];
	ATTRIBUTE_REC attriRec_l[tableRec_l.attriNum];

	AttributeManager AM(env->getEnv());
	
	AM.getForTableID(tableRec_r, attriRec_r);
	AM.getForTableID(tableRec_n, attriRec_n);
	AM.getForTableID(tableRec_s, attriRec_s);
	AM.getForTableID(tableRec_p, attriRec_p);
	AM.getForTableID(tableRec_c, attriRec_c);
	AM.getForTableID(tableRec_o, attriRec_o);
	AM.getForTableID(tableRec_l, attriRec_l);

/* selection1 */
	FixStrPosVal pv1(1,25);
	string str1("AMERICA");
	pv1.setStr(str1);

	ValueNode vn1 = ValueNode(&pv1);
	ColumnRefNode cn1;
	cn1.tableID = 1;
	cn1.attriID = 2;
	AxprNode an1 = AxprNode(EQ, &cn1, &vn1);
	

/* selection2 */

	DatePosVal pv2(1,(unsigned char *)"1995-01-01");
	DatePosVal pv3(1,(unsigned char *)"1996-12-31");
	

	ValueNode vn2 = ValueNode(&pv2);
	ValueNode vn3 = ValueNode(&pv3);
	ColumnRefNode cn2;
	cn2.tableID = 7;
	cn2.attriID = 5;
	AxprNode an2 = AxprNode(GE, &cn2, &vn2);
	AxprNode an3 = AxprNode(LE, &cn2, &vn3);
	AxprNode an4 = AxprNode(AND, &an2, &an3);

/* selection3 */
	VarStrPosVal pv4(1,25);
	string str2("ECONOMY ANODIZED STEEL");
	pv4.set((unsigned char*)str2.c_str());

	ValueNode vn4 = ValueNode(&pv4);
	ColumnRefNode cn3;
	cn3.tableID = 4;
	cn3.attriID = 5;
	AxprNode an5 = AxprNode(EQ, &cn3, &vn4);
	

	
/*Join1*/
	OPERATION_NODE jop1, jop2;
	jop1.tableID = 6;
	jop1.attributeID = 4;
	jop2.tableID = 6;
	jop2.attributeID = 1;
	
	JOIN_OPERATION_NODE jon1;
	jon1.rightNode = jop1;
	jon1.leftNode = jop2;

/*Join2*/
	OPERATION_NODE jop3, jop4;
	jop3.tableID = 7;
	jop3.attributeID = 2;
	jop4.tableID = 7;
	jop4.attributeID = 5;
	
	JOIN_OPERATION_NODE jon2;
	jon2.rightNode = jop3;
	jon2.leftNode = jop4;

/*Join3*/
	OPERATION_NODE jop5, jop6;
	jop5.tableID = 7;
	jop5.attributeID = 5;
	jop6.tableID = 7;
	jop6.attributeID = 1;
	
	JOIN_OPERATION_NODE jon3;
	jon3.rightNode = jop5;
	jon3.leftNode = jop6;

/*Join4*/
	OPERATION_NODE jop7, jop8;
	jop7.tableID = 7;
	jop7.attributeID = 1;
	jop8.tableID = 8;
	jop8.attributeID = 1;
	
	JOIN_OPERATION_NODE jon4;
	jon4.rightNode = jop7;
	jon4.leftNode = jop8;
	
/*Join5*/
	OPERATION_NODE jop9, jop10;
	jop9.tableID = 4;
	jop9.attributeID = 1;
	jop10.tableID = 8;
	jop10.attributeID = 2;
	
	JOIN_OPERATION_NODE jon5;
	jon5.rightNode = jop9;
	jon5.leftNode = jop10;

/*Join6*/
	OPERATION_NODE jop11, jop12;
	jop11.tableID = 3;
	jop11.attributeID = 1;
	jop12.tableID = 8;
	jop12.attributeID = 3;
	
	JOIN_OPERATION_NODE jon6;
	jon6.rightNode = jop11;
	jon6.leftNode = jop12;
	
/* Projection1 */

	OPERATION_NODE pro1[1];
	pro1[0].tableID = 6;
	pro1[0].attributeID = 1;
	
	
/* Projection2 */

	OPERATION_NODE pro2[2];
	pro2[0].tableID = 7;
	pro2[0].attributeID = 1;
	pro2[1].tableID = 7;
	pro2[1].attributeID = 5;
	
/* Projection3 */

	OPERATION_NODE pro3[1];
	pro3[0].tableID = 8;
	pro3[0].attributeID = 2;
	
/* Projection4 */

	OPERATION_NODE pro4[2];
	pro4[0].tableID = 8;
	pro4[0].attributeID = 3;
	pro4[1].tableID = 2;
	pro4[1].attributeID = 2;

/* Projection5 */

	OPERATION_NODE pro5[4];
	pro5[0].tableID = 7;
	pro5[0].attributeID = 5;
	pro5[1].tableID = 2;
	pro5[1].attributeID = 2;
	pro5[2].tableID = 8;
	pro5[2].attributeID = 6;
	pro5[3].tableID = 8;
	pro5[3].attributeID = 7;
	
/* Projection6 */

	OPERATION_NODE pro6[5];
	pro6[0].tableID = 7;
	pro6[0].attributeID = 5;
	pro6[1].tableID = 8;
	pro6[1].attributeID = 2;
	pro6[2].tableID = 8;
	pro6[2].attributeID = 3;
	pro6[3].tableID = 8;
	pro6[3].attributeID = 6;
	pro6[4].tableID = 8;
	pro6[4].attributeID = 7;

/* Projection7 */

	OPERATION_NODE pro7[4];
	pro7[0].tableID = 7;
	pro7[0].attributeID = 5;
	pro7[1].tableID = 8;
	pro7[1].attributeID = 3;
	pro7[2].tableID = 8;
	pro7[2].attributeID = 6;
	pro7[3].tableID = 8;
	pro7[3].attributeID = 7;

/* Projection8 */

	OPERATION_NODE pro8[2];
	pro8[0].tableID = 3;
	pro8[0].attributeID = 1;
	pro8[1].tableID = 2;
	pro8[1].attributeID = 2;

/* Projection9 */

	OPERATION_NODE pro9[4];
	pro9[0].tableID = 2;
	pro9[0].attributeID = 2;
	pro9[1].tableID = 7;
	pro9[1].attributeID = 5;
	pro9[2].tableID = 8;
	pro9[2].attributeID = 6;
	pro9[3].tableID = 8;
	pro9[3].attributeID = 7;

/* Extract */
	OPERATION_NODE ex[1];
	ex[0].tableID = 7;
	ex[0].attributeID = 5;

/* GROUP */
	IntPosVal pv5(1, 1);
	ValueNode vn5 = ValueNode(&pv5);
	ColumnRefNode cn4[2];
	cn4[0].tableID = 8;
	cn4[0].attriID = 6;
	cn4[1].tableID = 8;
	cn4[1].attriID = 7;
	ArithmeticNode arith1(SUB, &vn5, &cn4[1]);
	ArithmeticNode arith2(MUL, &cn4[0], &arith1);
	
	Aggregation *aggre[1];
	aggre[0] = new Sum(&arith2, 2);
	
	
	OPERATION_NODE group[1];
	group[0].tableID = 7;
	group[0].attributeID = 5;

/* Sort 1 */
	OPERATION_NODE so1[1];
	so1[0].tableID = 7;
	so1[0].attributeID = 5;
	so1[0].option = 0;
	
	


	OPERATION_NODE op1;
	op1.tableID = 2;
	op1.attributeID = 3;
	
	OPERATION_NODE op2;
	op2.tableID = 6;
	op2.attributeID = 4;
	
	OPERATION_NODE op3;
	op3.tableID = 7;
	op3.attributeID = 2;
	
	OPERATION_NODE op4;
	op4.tableID = 8;
	op4.attributeID = 1;
	
	OPERATION_NODE op5;
	op5.tableID = 3;
	op5.attributeID = 4;
	
	OPERATION_NODE op6;
	op6.tableID = 2;
	op6.attributeID = 2;
	
	
/* index position */
	
	OPERATION_NODE idx1[1];
	idx1[0].tableID = 7;
	idx1[0].attributeID = 1;
	
/* index position */
	
	OPERATION_NODE idx2[1];
	idx2[0].tableID = 6;
	idx2[0].attributeID = 1;

//===============================================================-


	o1 = new ScanDSM(&db_r_2, &attriRec_r[1], 1);
//	cout << "OK new o1" << endl;
	
	o2 = new SelectBitOut((Node *)&an1 ,(unsigned int)1);
//	cout << "OK new o2" << endl;
	o2->setPreOperator(o1);
	
	o3 = new ScanDSM(&db_r_1, attriRec_r, 1);
//	cout << "OK new o3" << endl;
	
	o4 = new BitFilter(o3, o2);
//	cout << "OK new o4" << endl;
	
	
	o5 = new ScanDSM(&db_n_3, &attriRec_n[2], 1);
//	cout << "OK new o5" << endl;
	
	o6 = new JoinIndex_OneHash(o4, o5); 
//	cout << "OK new o6" << endl;
	
	o7 = new ScanDSM(&db_n_1, &attriRec_n[0], 1);
//	cout << "OK new o7" << endl;
	
	o8 = new ScanFromJI(o7, o6, &op1);
//	cout << "OK new o8" << endl;

	o9 = new ScanDSM(&db_c_4, &attriRec_c[3], 1);
//	cout << "OK new o9" << endl;

	o10 = new JoinIndex_OneHash(o8, o9); 
//	cout << "OK new o10" << endl;
	
	o11 = new ScanDSM(&db_c_1, &attriRec_c[0], 1);
//	cout << "OK new o11" << endl;
	
	o12 = new ScanFromJI(o11, o10, &op2);
//	cout << "OK new o12" << endl;
	
	o13 = new Projection(pro1, 1);
	o13->setPreOperator(o12);
	

/* ======== Nested Loop Join with Index ============ */

	IndexScan *IS2 = new IndexScan((BDBOpe *)sDB2, attriRec_o, 9);
	o14 = new NestedJoin_Index(IS2, o13, idx2);
	//l_partkey, l_suppkey, l_extentdedprice, l_discount, o_orderdate
	//o15 = new Projection(pro6, 5);
	//o15->setPreOperator(o22);
	
/* ======================================================= */
	

	o17 = new Selection((Node *)&an4 ,(unsigned int)2);
//	cout << "OK new o17" << endl;
	o17->setPreOperator(o14);
	

	o21 = new Projection(pro2, 2);
	o21->setPreOperator(o17);
//	cout << "OK new o21" << endl;


/* ======== Nested Loop Join with Index ============ */

	IndexScan *IS1 = new IndexScan((BDBOpe *)sDB1, attriRec_l, 16);
	o22 = new NestedJoin_Index(IS1, o21, idx1);
	//l_partkey, l_suppkey, l_extentdedprice, l_discount, o_orderdate
	o23 = new Projection(pro6, 5);
	o23->setPreOperator(o22);
	
/* ======================================================= */
	
	
	

	o24 = new ScanDSM(&db_p_5, &attriRec_p[4], 1);
//	cout << "OK new o24" << endl;

	o25 = new SelectBitOut((Node *)&an5 ,1);
//	cout << "OK new o25" << endl;
	o25->setPreOperator(o24);
	
	o26 = new ScanDSM(&db_p_1, &attriRec_p[0], 1);
//	cout << "OK new o26" << endl;

	o27 = new BitFilter(o26, o25);
//	cout << "OK new o27" << endl;
	
	
	o29 = new OneSideHashJoin(o27, o23, &jon5, 1); 
//	cout << "OK new o29" << endl;
	
	o30 = new Projection(pro7, 4);
	o30->setPreOperator(o29);
//	cout << "OK new o30" << endl;
	
	
	
	
	o32 = new ScanDSM(&db_n2_1, &attriRec_n[0], 1);
//	cout << "OK new o32" << endl;
	/**/
	o33 = new ScanDSM(&db_n2_2, &attriRec_n[1], 1);
//	cout << "OK new o33" << endl;
	
	o34 = new ScanFromJI(o32, o33, &op6);
//	cout << "OK new o34" << endl;
	/*  */
	o35 = new ScanDSM(&db_s_4, &attriRec_s[3], 1);
//	cout << "OK new o35" << endl;
	
	o36 = new JoinIndex_OneHash(o34, o35); 
//	cout << "OK new o36" << endl;
	
	o37 = new ScanDSM(&db_s_1, &attriRec_s[0], 1);
//	cout << "OK new o37" << endl;
	
	o38 = new ScanFromJI(o37, o36, &op5);
//	cout << "OK new o38" << endl;

	o39 = new Projection(pro8, 2);
	o39->setPreOperator(o38);
	
	
	o40 = new OneSideHashJoin(o39, o30, &jon6,1); 
//	cout << "OK new o40" << endl;
	
	
	
	
	
	
	o41 = new Projection(pro9, 4);
	o41->setPreOperator(o40);
//	cout << "OK new o41" << endl;
	/*l_suppkey, n_name, l_partkey, o_orderdate,*/

	
	o48 = new Extract(ex, true, false, false);
	o48->setPreOperator(o41);
//	cout << "OK new o48" << endl;
	
	o49 = new GroupBy(group, 1, aggre, 1);
	o49->setPreOperator(o48);
//	cout << "OK new o49" << endl;
	
	o50 = new Sort(so1, 1);
	o50->setPreOperator(o49);
//	cout << "OK new o50" << endl;


	o51 = new OutPut(TIME_OUT);
//	cout << "OK new o51" << endl;
	o51->setPreOperator(o50);
	o51->init(env->getEnv());
	cout << "TEST START" << endl;
	
	cout << setprecision(2);
	cout << setiosflags(ios::fixed); 
	o51->exec();
	

}