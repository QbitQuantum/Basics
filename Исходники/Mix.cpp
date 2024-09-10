int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db_r_1(env->getEnv(), "1.1.DSM");
	BDBOpe db_r_2(env->getEnv(), "1.2.DSM");
	BDBOpe db_n_1(env->getEnv(), "2.1.DSM");
	BDBOpe db_n_2(env->getEnv(), "2.2.DSM");
	BDBOpe db_n_3(env->getEnv(), "2.3.DSM");
	BDBOpe db_s_1(env->getEnv(), "3.1.DSM");
	BDBOpe db_s_4(env->getEnv(), "3.4.DSM");
	BDBOpe db_c_1(env->getEnv(), "6.1.DSM");
	BDBOpe db_c_4(env->getEnv(), "6.4.DSM");
	BDBOpe db_o(env->getEnv(), "ORDERS.row");
	BDBOpe db_l(env->getEnv(), "LINEITEM.row");
	
	SecondDB *sDB,*sDB_o;
	int (*pf)(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
	pf = L_1_secondary;
	sDB = new SecondDB(env->getEnv(), "8.1.secondary");
	sDB->setNumCmp();
	
	int (*pf_o)(Db *sdbp, const Dbt*pkey, const Dbt *pdata, Dbt *skey);
	pf_o = O_2_secondary;
	sDB_o = new SecondDB(env->getEnv(), "7.2.secondary");
	sDB_o->setNumCmp();
	
	db_r_1.open();
	db_r_2.open();
	db_n_1.open();
	db_n_2.open();
	db_n_3.open();
	db_s_1.open();
	db_s_4.open();
	db_c_1.open();
	db_c_4.open();
	db_o.open();
	db_l.open();
	sDB->open(0);
	db_l.associate(sDB->getDb(), pf);
	sDB->openCursor();
	sDB_o->open(0);
	db_o.associate(sDB_o->getDb(), pf_o);
	sDB_o->openCursor();


	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12, *o13, *o14, *o15, *o16, *o17, *o18, *o19, *o20;
	Operator *o21, *o22, *o23, *o24, *o25, *o26, *o27, *o28, *o29, *o30;
	Operator *o31, *o32, *o33, *o34, *o35, *o36, *o37, *o38, *o39, *o40;



	TABLE_REC tableRec_r;
	TABLE_REC tableRec_n;
	TABLE_REC tableRec_c;
	TABLE_REC tableRec_o;
	TABLE_REC tableRec_l;
	TABLE_REC tableRec_s;

	
/* set table info */
	tableRec_r.tableID = 1;
	tableRec_r.attriNum = 3;
	
	tableRec_n.tableID = 2;
	tableRec_n.attriNum = 4;
	
	tableRec_s.tableID = 3;
	tableRec_s.attriNum = 7;
	
	tableRec_c.tableID = 6;
	tableRec_c.attriNum = 8;

	tableRec_o.tableID = 7;
	tableRec_o.attriNum = 9;
	
	tableRec_l.tableID = 8;
	tableRec_l.attriNum = 16;
	


/* aet attriRec */
	ATTRIBUTE_REC attriRec_r[tableRec_r.attriNum];
	ATTRIBUTE_REC attriRec_n[tableRec_n.attriNum];
	ATTRIBUTE_REC attriRec_s[tableRec_s.attriNum];
	ATTRIBUTE_REC attriRec_c[tableRec_c.attriNum];
	ATTRIBUTE_REC attriRec_o[tableRec_o.attriNum];
	ATTRIBUTE_REC attriRec_l[tableRec_l.attriNum];
	

	AttributeManager AM(env->getEnv());
	

	AM.getForTableID(tableRec_r, attriRec_r);
	AM.getForTableID(tableRec_n, attriRec_n);
	AM.getForTableID(tableRec_c, attriRec_c);
	AM.getForTableID(tableRec_o, attriRec_o);
	AM.getForTableID(tableRec_l, attriRec_l);
	AM.getForTableID(tableRec_s, attriRec_s);

/* selection1 */
	FixStrPosVal pv1(1,25);
	string str1("ASIA");
	pv1.setStr(str1);

	ValueNode vn1 = ValueNode(&pv1);
	ColumnRefNode cn1;
	cn1.tableID = 1;
	cn1.attriID = 2;
	AxprNode an1 = AxprNode(EQ, &cn1, &vn1);
	

/* selection2 */

	DatePosVal pv2(1,(unsigned char *)"1994-01-01");
	DatePosVal pv3(1,(unsigned char *)"1995-01-01");
	

	ValueNode vn2 = ValueNode(&pv2);
	ValueNode vn3 = ValueNode(&pv3);
	ColumnRefNode cn2;
	cn2.tableID = 7;
	cn2.attriID = 5;
	AxprNode an2 = AxprNode(GE, &cn2, &vn2);
	AxprNode an3 = AxprNode(LT, &cn2, &vn3);
	AxprNode an4 = AxprNode(AND, &an2, &an3);
	
	
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
	group[0].tableID = 2;
	group[0].attributeID = 2;
	
/* Sort 1 */
	OPERATION_NODE so1[1];
	so1[0].tableID = 0;
	so1[0].attributeID = 0;
	so1[0].position = 1;
	so1[0].option = 1;

/* Projection1 */

	OPERATION_NODE pro1[2];
	pro1[0].tableID = 2;
	pro1[0].attributeID = 1;
	pro1[1].tableID = 2;
	pro1[1].attributeID = 2;
	
/* Projection2 */

	OPERATION_NODE pro2[3];
	pro2[0].tableID = 3;
	pro2[0].attributeID = 1;
	pro2[1].tableID = 3;
	pro2[1].attributeID = 4;
	pro2[2].tableID = 2;
	pro2[2].attributeID = 2;
	
/* Projection3 */

	OPERATION_NODE pro3[3];
	pro3[0].tableID = 2;
	pro3[0].attributeID = 2;
	pro3[1].tableID = 8;
	pro3[1].attributeID = 6;
	pro3[2].tableID = 8;
	pro3[2].attributeID = 7;

/* Projection4 */

	OPERATION_NODE pro4[3];
	pro4[0].tableID = 2;
	pro4[0].attributeID = 2;
	pro4[1].tableID = 6;
	pro4[1].attributeID = 1;
	pro4[2].tableID =6;
	pro4[2].attributeID = 4;

/* Projection5 */

	OPERATION_NODE pro5[3];
	pro5[0].tableID = 2;
	pro5[0].attributeID = 2;
	pro5[1].tableID = 6;
	pro5[1].attributeID = 4;
	pro5[2].tableID = 7;
	pro5[2].attributeID = 1;

/* Projection6 */

	OPERATION_NODE pro6[5];
	pro6[0].tableID = 2;
	pro6[0].attributeID = 2;
	pro6[1].tableID = 6;
	pro6[1].attributeID = 4;
	pro6[2].tableID = 8;
	pro6[2].attributeID = 3;
	pro6[3].tableID = 8;
	pro6[3].attributeID = 6;
	pro6[4].tableID = 8;
	pro6[4].attributeID = 7;

/* Projection11 */
	
	OPERATION_NODE pro11[4];
	pro11[0].tableID = 2;
	pro11[0].attributeID = 2;
	pro11[1].tableID = 6;
	pro11[1].attributeID = 4;
	pro11[2].tableID = 7;
	pro11[2].attributeID = 1;
	pro11[3].tableID = 7;
	pro11[3].attributeID = 5;
	
	
	OPERATION_NODE op1;
	op1.tableID = 2;
	op1.attributeID = 3;
	
	OPERATION_NODE op2;
	op2.tableID = 3;
	op2.attributeID = 4;
	
	OPERATION_NODE op3;
	op3.tableID = 8;
	op3.attributeID = 3;
	
	OPERATION_NODE op4;
	op4.tableID = 7;
	op4.attributeID = 2;
	
	OPERATION_NODE op5;
	op5.tableID = 6;
	op5.attributeID = 4;

/* index position */
	
	OPERATION_NODE pro10[1];
	pro10[0].tableID = 7;
	pro10[0].attributeID = 1;
	
	
/* Join1 */
	OPERATION_NODE pn1[2];
	pn1[0].tableID = 2;
	pn1[0].attributeID = 1;
	pn1[1].tableID = 6;
	pn1[1].attributeID = 4;

	
	JOIN_OPERATION_NODE jpn1[1];
	jpn1[0].rightNode = pn1[0];
	jpn1[0].leftNode = pn1[1];

/* Join2 */
	OPERATION_NODE pn2[2];
	pn2[0].tableID = 6;
	pn2[0].attributeID = 1;
	pn2[1].tableID = 7;
	pn2[1].attributeID = 2;

	
	JOIN_OPERATION_NODE jpn2[1];
	jpn2[0].rightNode = pn2[0];
	jpn2[0].leftNode = pn2[1];
	
/* Join3 */
	OPERATION_NODE pn3[2];
	pn3[0].tableID = 7;
	pn3[0].attributeID = 1;
	pn3[1].tableID = 8;
	pn3[1].attributeID = 1;

	
	JOIN_OPERATION_NODE jpn3[1];
	jpn3[0].rightNode = pn3[0];
	jpn3[0].leftNode = pn3[1];

/* Join4 */
	OPERATION_NODE pn4[4];
	pn4[0].tableID = 3;
	pn4[0].attributeID = 1;
	pn4[1].tableID = 3;
	pn4[1].attributeID = 4;
	pn4[2].tableID = 8;
	pn4[2].attributeID = 3;
	pn4[3].tableID = 6;
	pn4[3].attributeID = 4;

	
	JOIN_OPERATION_NODE jpn4[2];
	jpn4[0].rightNode = pn4[0];
	jpn4[0].leftNode = pn4[2];
	jpn4[1].rightNode = pn4[1];
	jpn4[1].leftNode = pn4[3];

	
/* exec */
	
	o1 = new ScanDSM(&db_r_2, &attriRec_r[1], 1);
	o2 = new SelectBitOut((Node *)&an1 ,(unsigned int)1);
	o2->setPreOperator(o1);
	o3 = new ScanDSM(&db_r_1, &attriRec_r[0], 1);
	o4 = new BitFilter(o3, o2);

	o5 = new ScanDSM(&db_n_3, &attriRec_n[2], 1);
	o6 = new JoinIndex_OneHash(o4, o5); 

	
	o7 = new ScanDSM(&db_n_1, &attriRec_n[0], 1);
	o8 = new ScanFromJI(o7, o6, &op1);
	o9 = new ScanDSM(&db_n_2, &attriRec_n[1], 1);
	//n_name, n_natonkey, r_regionkey, n_nationkey
	o10 = new ScanFromJI(o9, o8, &op1);
	
	//n_name, n_natonkey
	o11 = new Projection(pro1, 2);
	o11->setPreOperator(o10);

	o12 = new ScanDSM(&db_c_4, &attriRec_c[3], 1);
	o13 = new ScanDSM(&db_c_1, &attriRec_c[0], 1);
	o14 = new ScanFromJI(o13, o12, &op5);
	
	o15 = new OneSideHashJoin(o10, o14 , jpn1, 1);
	//n_name, c_custkey, c_nationkey
	o16 = new Projection(pro4, 3);
	o16->setPreOperator(o15);
	
	/* ======== Nested Loop Join with Index ============ */
	IndexScan *IS_o = new IndexScan((BDBOpe *)sDB_o, attriRec_o, 9);
	o17 = new NestedJoin_Index(IS_o, o16, pn2);
	o18 = new Projection(pro11, 4);
	o18->setPreOperator(o17);

	//o17 = new ScanDSM(&db_o_5, &attriRec_o[4], 1);
	o19 = new Selection((Node *)&an4 ,(unsigned int)2);
	o19->setPreOperator(o18);
	//o19 = new ScanDSM(&db_o_2, &attriRec_o[1], 1);
	//o20 = new BitFilter(o19, o18);
	
	/* ======================================================= */
	
	
	//o21 = new ScanDSM(&db_o_1, &attriRec_o[0], 1);
	//o_order, o_custkey
	//o22 = new ScanFromJI(o21, o20, &op4);
	
	//n_name, c_custkey, c_nationkey, o_order, o_custkey
	//o23 = new OneSideHashJoin(o16, o22 , jpn2, 1);
	
	//n_name, c_nationkey, o_order
	o24 = new Projection(pro5, 3);
	o24->setPreOperator(o19);

	/* ======== Nested Loop Join with Index ============ */

	IndexScan *IS = new IndexScan((BDBOpe *)sDB, attriRec_l, 16);
	o25 = new NestedJoin_Index(IS, o24, pro10);
	o26 = new Projection(pro6, 5);
	o26->setPreOperator(o25);
	
	/* ======================================================= */
	
	//l_orderkey, l_extendedprice, l_discount, l_suppkey

	o33 = new ScanDSM(&db_s_4, &attriRec_s[3], 1);
	o34 = new ScanDSM(&db_s_1, &attriRec_s[0], 1);
	o35 = new ScanFromJI(o34, o33, &op2);

	o36 = new OneSideHashJoin(o35, o26 , jpn4, 2);



	o37 = new Projection(pro3, 3);
	o37->setPreOperator(o36);
	
	o38 = new GroupBy(group, 1, aggre, 1);
	o38->setPreOperator(o37);

	o39 = new Sort(so1, 1);
	o39->setPreOperator(o38);
	
	o40 = new OutPut(TIME_OUT);

	o40->setPreOperator(o39);
	o40->init(env->getEnv());
	cout << "TEST START Q5" << endl;
	
	cout << setprecision(4);
	cout << setiosflags(ios::fixed); 
	o40->exec();
}