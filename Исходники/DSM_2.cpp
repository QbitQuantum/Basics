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
	BDBOpe db_o_1(env->getEnv(), "7.1.DSM");
	BDBOpe db_o_2(env->getEnv(), "7.2.DSM");
	BDBOpe db_o_5(env->getEnv(), "7.5.DSM");
	BDBOpe db_l_1(env->getEnv(), "8.1.DSM");
	BDBOpe db_l_2(env->getEnv(), "8.2.DSM");
	BDBOpe db_l_3(env->getEnv(), "8.3.DSM");
	BDBOpe db_l_6(env->getEnv(), "8.6.DSM");
	BDBOpe db_l_7(env->getEnv(), "8.7.DSM");

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
	db_o_1.open();
	db_o_2.open();
	db_o_5.open();
	
	db_l_1.open();
	db_l_2.open();
	db_l_3.open();
	db_l_6.open();
	db_l_7.open();
	
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
/*	for(int i=0 ; i < (int)tableRec_r.attriNum ; i++){
		cout << attriRec_r[i].attributeName << endl;
	}
*/
	AM.getForTableID(tableRec_n, attriRec_n);
/*	for(int i=0 ; i < (int)tableRec_n.attriNum ; i++){
		cout << attriRec_n[i].attributeName << endl;
	}
*/
	AM.getForTableID(tableRec_s, attriRec_s);
/*	for(int i=0 ; i < (int)tableRec_s.attriNum ; i++){
		cout << attriRec_s[i].attributeName << endl;
	}
*/
	AM.getForTableID(tableRec_p, attriRec_p);
/*	for(int i=0 ; i < (int)tableRec_p.attriNum ; i++){
		cout << attriRec_p[i].attributeName << endl;
	}
*/
	AM.getForTableID(tableRec_c, attriRec_c);
/*	for(int i=0 ; i < (int)tableRec_c.attriNum ; i++){
		cout << attriRec_c[i].attributeName << endl;
	}
*/
	AM.getForTableID(tableRec_o, attriRec_o);
/*	for(int i=0 ; i < (int)tableRec_o.attriNum ; i++){
		cout << attriRec_o[i].attributeName << endl;
	}
*/
	AM.getForTableID(tableRec_l, attriRec_l);
/*	for(int i=0 ; i < (int)tableRec_l.attriNum ; i++){
		cout << attriRec_l[i].attributeName << endl;
	}
*/

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
	jop11.tableID = 6;
	jop11.attributeID = 1;
	jop12.tableID = 7;
	jop12.attributeID = 2;
	
	JOIN_OPERATION_NODE jon6;
	jon6.rightNode = jop11;
	jon6.leftNode = jop12;
	
/*Join7*/
	OPERATION_NODE jop13, jop14;
	jop13.tableID = 3;
	jop13.attributeID = 1;
	jop14.tableID = 8;
	jop14.attributeID = 3;
	
	JOIN_OPERATION_NODE jon7;
	jon7.rightNode = jop13;
	jon7.leftNode = jop14;
	
/*Join8*/
	OPERATION_NODE jop15, jop16;
	jop15.tableID = 2;
	jop15.attributeID = 1;
	jop16.tableID = 3;
	jop16.attributeID = 4;
	
	JOIN_OPERATION_NODE jon8;
	jon8.rightNode = jop15;
	jon8.leftNode = jop16;
	
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
	op3.attributeID = 5;
	
	OPERATION_NODE op4;
	op4.tableID = 8;
	op4.attributeID = 1;
	
	OPERATION_NODE op5;
	op5.tableID = 3;
	op5.attributeID = 4;
	
	OPERATION_NODE op6;
	op6.tableID = 2;
	op6.attributeID = 2;
	
	OPERATION_NODE op7;
	op7.tableID = 8;
	op7.attributeID = 2;


	o1 = new ScanDSM(&db_r_2, &attriRec_r[1], 1);
	
	o2 = new SelectBitOut((Node *)&an1 ,(unsigned int)1);
	o2->setPreOperator(o1);
	
	o3 = new ScanDSM(&db_r_1, &attriRec_r[0], 1); 
	
	o4 = new BitFilter(o3, o2);
	
	o5 = new ScanDSM(&db_n_3, &attriRec_n[2], 1);
	
	o6 = new JoinIndex_OneHash(o4, o5); 
	
	o7 = new ScanDSM(&db_n_1, &attriRec_n[0], 1);
	
	o8 = new ScanFromJI(o7, o6, &op1);

	o9 = new ScanDSM(&db_c_4, &attriRec_c[3], 1);

	o10 = new JoinIndex_OneHash(o8, o9); 
	
	o11 = new ScanDSM(&db_c_1, &attriRec_c[0], 1);
	
	o12 = new ScanFromJI(o11, o10, &op2);
	
	o13 = new Projection(pro1, 1);
	o13->setPreOperator(o12);
	
/*	
	
	o14 = new ScanDSM(&db_o_2, &attriRec_o[1], 1);
//	cout << "OK new o14" << endl;
	
	o15 = new JoinIndex_OneHash(o13, o14); 
//	cout << "OK new o15" << endl;
	
*/
	o14 = new ScanDSM(&db_o_5, &attriRec_o[4], 1);

	o15 = new Selection((Node *)&an4 ,(unsigned int)2);
	o15->setPreOperator(o14);
	
	o16 = new ScanDSM(&db_o_2, &attriRec_o[1], 1);
	
	o17 = new ScanFromJI(o16, o15, &op3);
	
	o18 = new ScanDSM(&db_o_1, &attriRec_o[0], 1);
	
	o19 = new ScanFromJI(o18, o17, &op3);
	
	
	
	o20 = new ScanDSM(&db_p_5, &attriRec_p[4], 1);

	o21 = new SelectBitOut((Node *)&an5 ,1);
	o21->setPreOperator(o20);
	
	o22 = new ScanDSM(&db_p_1, &attriRec_p[0], 1);

	o23 = new BitFilter(o22, o21);
	
	o24 = new ScanDSM(&db_l_2, &attriRec_l[1], 1);
	
	o25 = new JoinIndex_OneHash(o23, o24, &jon5); 



	o26 = new ScanDSM(&db_l_1, &attriRec_l[0], 1);
	o27 = new ScanFromJI(o26, o25, &op7);
	
	
	o28 = new JoinIndex_OneHash(o19, o27, &jon4);
	o29 = new JoinIndex_OneHash(o13, o28, &jon6);
	
	o30 = new ScanDSM(&db_s_4, &attriRec_s[3], 1);
	
	o31 = new ScanDSM(&db_s_1, &attriRec_s[0], 1);
	
	o32 = new ScanFromJI(o31, o30, &op5);
	
	
	
	o33 = new ScanDSM(&db_l_3, &attriRec_l[2], 1);
	o34 = new ScanFromJI(o33, o29, &op7);
	
	o35 = new JoinIndex_OneHash(o32, o34, &jon7);
	
	
	
	o36 = new ScanDSM(&db_n2_1, &attriRec_n[0], 1);
	o37 = new ScanDSM(&db_n2_2, &attriRec_n[1], 1);
	o38 = new ScanFromJI(o36, o37, &op6);
	
	o40 = new JoinIndex_OneHash(o38, o35, &jon8);
	
	
	
	o41 = new ScanDSM(&db_l_6, &attriRec_l[5], 1);
	o42 = new ScanFromJI(o41, o40, &op4);


	o43 = new ScanDSM(&db_l_7, &attriRec_l[6], 1);
	o44 = new ScanFromJI(o43, o42, &op4);

	o45 = new Projection(pro5, 4);
	o45->setPreOperator(o44);
	
	o46 = new Extract(ex, true, false, false);
	o46->setPreOperator(o45);
	
	o47 = new GroupBy(group, 1, aggre, 1);
	o47->setPreOperator(o46);
	
	o48 = new Sort(so1, 1);
	o48->setPreOperator(o47);


	o49 = new OutPut(TIME_OUT);
	o49->setPreOperator(o48);
	o49->init(env->getEnv());
	cout << "TEST START" << endl;
	
	cout << setprecision(2);
	cout << setiosflags(ios::fixed);
	o49->exec();
}