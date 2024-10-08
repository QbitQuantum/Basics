int main(){
	chdir(QUERY_DATA_PATH);
	EnvDB *env = new EnvDB();
	env->open();
	
	BDBOpe db1(env->getEnv(), DB1);
	BDBOpe db2(env->getEnv(), DB2);
	BDBOpe db3(env->getEnv(), DB3);
	BDBOpe db4(env->getEnv(), DB4);
	BDBOpe db5(env->getEnv(), DB5);
	BDBOpe db6(env->getEnv(), DB6);
	BDBOpe db7(env->getEnv(), DB7);
	BDBOpe db8(env->getEnv(), DB8);
	BDBOpe db9(env->getEnv(), DB9);
	BDBOpe db10(env->getEnv(), DB10);
	BDBOpe db11(env->getEnv(), DB11);
	BDBOpe db12(env->getEnv(), DB12);
	BDBOpe db13(env->getEnv(), DB13);
	BDBOpe db14(env->getEnv(), DB14);
	BDBOpe db15(env->getEnv(), DB15);
	BDBOpe db16(env->getEnv(), DB16);
	Operator *o1, *o2, *o3, *o4, *o5, *o6, *o7, *o8, *o9, *o10;
	Operator *o11, *o12, *o13, *o14, *o15, *o16, *o17, *o18, *o19, *o20;
	Operator *o21, *o22, *o23, *o24, *o25, *o26, *o27, *o28, *o29, *o30;
	Operator *o31, *o32;
	
	db1.open();
	db2.open();
	db3.open();
	db4.open();
	db5.open();
	db6.open();
	db7.open();
	db8.open();
	db9.open();
	db10.open();
	db11.open();
	db12.open();
	db13.open();
	db14.open();
	db15.open();
	db16.open();
	TABLE_REC tableRec;
	
	tableRec.tableID = DB_tableID;
	tableRec.attriNum = DB_attriNum;
	
	ATTRIBUTE_REC attriRec[tableRec.attriNum];
	AttributeManager AM(env->getEnv());
	AM.getForTableID(tableRec, attriRec);
	
	OPERATION_NODE op1;
	op1.tableID = 16;
	op1.attributeID = 1;
	OPERATION_NODE op2;
	op2.tableID = 16;
	op2.attributeID = 4;
	
	o1 = new ScanDSM(&db1, &attriRec[0], 1);
	o2 = new ScanDSM(&db2, &attriRec[1], 1);
	o3 = new ScanDSM(&db3, &attriRec[2], 1);
	o4 = new ScanDSM(&db4, &attriRec[3], 1);
	o5 = new ScanDSM(&db5, &attriRec[4], 1);
	o6 = new ScanDSM(&db6, &attriRec[5], 1);
	o7 = new ScanDSM(&db7, &attriRec[6], 1);
	o8 = new ScanDSM(&db8, &attriRec[7], 1);
	o9 = new ScanDSM(&db9, &attriRec[8], 1);
	o10 = new ScanDSM(&db10, &attriRec[9], 1);
	o11 = new ScanDSM(&db11, &attriRec[10], 1);
	o12 = new ScanDSM(&db12, &attriRec[11], 1);
	o13 = new ScanDSM(&db13, &attriRec[12], 1);
	o14 = new ScanDSM(&db14, &attriRec[13], 1);
	o15 = new ScanDSM(&db15, &attriRec[14], 1);
	o16 = new ScanDSM(&db16, &attriRec[15], 1);
	
/*	
	o17 = new ScanFromJI(o2, o1, &op1);
	o18 = new ScanFromJI(o3, o17, &op1);
	o19 = new ScanFromJI(o4, o18, &op1);
	o20 = new ScanFromJI(o5, o19, &op1);
	o21 = new ScanFromJI(o6, o20, &op1);
	o22 = new ScanFromJI(o7, o21, &op1);
	o23 = new ScanFromJI(o8, o22, &op1);
	o24 = new ScanFromJI(o9, o23, &op1);
	o25 = new ScanFromJI(o10, o24, &op1);
	o26 = new ScanFromJI(o11, o25, &op1);
	o27 = new ScanFromJI(o12, o26, &op1);
	o28 = new ScanFromJI(o13, o27, &op1);
	o29 = new ScanFromJI(o14, o28, &op1);
	o30 = new ScanFromJI(o15, o29, &op1);
	o31 = new ScanFromJI(o16, o30, &op1);
*/	
	o17 = new OutPut(TIME_OUT);
	o18 = new OutPut(TIME_OUT);
	o19 = new OutPut(TIME_OUT);
	o20 = new OutPut(TIME_OUT);
	o21 = new OutPut(TIME_OUT);
	o22 = new OutPut(TIME_OUT);
	o23 = new OutPut(TIME_OUT);
	o24 = new OutPut(TIME_OUT);
	o25 = new OutPut(TIME_OUT);
	o26 = new OutPut(TIME_OUT);
	o27 = new OutPut(TIME_OUT);
	o28 = new OutPut(TIME_OUT);
	o29 = new OutPut(TIME_OUT);
	o30 = new OutPut(TIME_OUT);
	o31 = new OutPut(TIME_OUT);
	o32 = new OutPut(TIME_OUT);

	o17->setPreOperator(o1);
	o17->init(env->getEnv());
	o17->exec();
	o18->setPreOperator(o2);
	o18->init(env->getEnv());
	o18->exec();
	o19->setPreOperator(o3);
	o19->init(env->getEnv());
	o19->exec();
	o20->setPreOperator(o4);
	o20->init(env->getEnv());
	o20->exec();
	o21->setPreOperator(o5);
	o21->init(env->getEnv());
	o21->exec();
	o22->setPreOperator(o6);
	o22->init(env->getEnv());
	o22->exec();
	o23->setPreOperator(o7);
	o23->init(env->getEnv());
	o23->exec();
	o24->setPreOperator(o8);
	o24->init(env->getEnv());
	o24->exec();
	o25->setPreOperator(o9);
	o25->init(env->getEnv());
	o25->exec();
	o26->setPreOperator(o10);
	o26->init(env->getEnv());
	o26->exec();
	o27->setPreOperator(o11);
	o27->init(env->getEnv());
	o27->exec();
	o28->setPreOperator(o12);
	o28->init(env->getEnv());
	o28->exec();
	o29->setPreOperator(o13);
	o29->init(env->getEnv());
	o29->exec();
	o30->setPreOperator(o14);
	o30->init(env->getEnv());
	o30->exec();
	o31->setPreOperator(o15);
	o31->init(env->getEnv());
	o31->exec();
	o32->setPreOperator(o16);
	o32->init(env->getEnv());
	o32->exec();
}