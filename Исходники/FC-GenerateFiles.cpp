void CFCView::GenerateTextFile(CString strFile,CString strTitle)
{
	ofstream fout(strFile);
#ifndef _DEBUG
	tm t;
	_getsystime(&t);
	fout.fill('0');
	fout<<"--  FC可解释执行中间代码文件\n";
	fout<<"--  FC2.32 于 "<<1900+t.tm_year<<"年"<<setw(2)<<1+t.tm_mon<<"月";
	fout<<setw(2)<<t.tm_mday<<"日"<<setw(2)<<t.tm_hour<<':'<<setw(2)<<t.tm_min;
	fout<<" 编译“"<<strTitle<<"”生成\n";
	fout<<"--  版权所有 朱凯峰 2004.02\n";
	fout<<"\n";
#endif
	fout.fill(' ');

	int i,j;
	const ZCode *pCode=m_pCode;
	for(i=0;i<m_nCode;i++)
	{
		if(pCode[i].op == OP_FUNCTIONSTART)
		{
			for(j=0;j<m_nFunction;j++)
				if(m_pFunction[j]->bSolved && m_pFunction[j]->nStartAddress==i)
					break;
			fout<<"-----    "<<m_pFunction[j]->name<<"    -----\n";
		}
		fout.setf(ios::right,ios::adjustfield);
		fout<<setw(5)<<i<<" :  ";
		fout.setf(ios::left,ios::adjustfield);
		fout<<setw(15);
		switch(pCode[i].op)
		{
		case OP_C2D:
			fout<<"C2D"<<pCode[i].sd.iNumber;
			break;
		case OP_C2I:
			fout<<"C2I"<<pCode[i].sd.iNumber;
			break;
		case OP_CALL:
			fout<<"CALL"<<pCode[i].sd.iNumber;
			break;
		case OP_CHANGESIGNALC:
			fout<<"CHANGESIGNALC";
			break;
		case OP_CHANGESIGNALD:
			fout<<"CHANGESIGNALD";
			break;
		case OP_CHANGESIGNALI:
			fout<<"CHANGESIGNALI";
			break;
		case OP_COPYI:
			fout<<"COPYI";
			break;
		case OP_D2C:
			fout<<"D2C"<<pCode[i].sd.iNumber;
			break;
		case OP_D2I:
			fout<<"D2I"<<pCode[i].sd.iNumber;
			break;
		case OP_DELARRAYC:
			fout<<"DELARRAYC"<<pCode[i].sd.iNumber;
			break;
		case OP_DELARRAYD:
			fout<<"DELARRAYD"<<pCode[i].sd.iNumber;
			break;
		case OP_DELARRAYI:
			fout<<"DELARRAYI"<<pCode[i].sd.iNumber;
			break;
		case OP_DELETEC:
			fout<<"DELETEC";
			break;
		case OP_DELETED:
			fout<<"DELETED";
			break;
		case OP_DELETEI:
			fout<<"DELETEI";
			break;
		case OP_EQUALC:
			fout<<"EQUALC"<<pCode[i].sd.iNumber;
			break;
		case OP_EQUALD:
			fout<<"EQUALD"<<pCode[i].sd.iNumber;
			break;
		case OP_EQUALI:
			fout<<"EQUALI"<<pCode[i].sd.iNumber;
			break;
		case OP_EXIT:
			fout<<"EXIT";
			break;
		case OP_FUNCTIONSTART:
			fout<<"FUNCTIONSTART"<<pCode[i].sd.iNumber;
			break;
		case OP_GREATC:
			fout<<"GREATC"<<pCode[i].sd.iNumber;
			break;
		case OP_GREATD:
			fout<<"GREATD"<<pCode[i].sd.iNumber;
			break;
		case OP_GREATEQUALC:
			fout<<"GREATEQUALC"<<pCode[i].sd.iNumber;
			break;
		case OP_GREATEQUALD:
			fout<<"GREATEQUALD"<<pCode[i].sd.iNumber;
			break;
		case OP_GREATEQUALI:
			fout<<"GREATEQUALI"<<pCode[i].sd.iNumber;
			break;
		case OP_GREATI:
			fout<<"GREATI"<<pCode[i].sd.iNumber;
			break;
		case OP_I2C:
			fout<<"I2C"<<pCode[i].sd.iNumber;
			break;
		case OP_I2D:
			fout<<"I2D"<<pCode[i].sd.iNumber;
			break;
		case OP_INPUTARRAYC:
			fout<<"INPUTARRAYC"<<pCode[i].sd.iNumber;
			break;
		case OP_INPUTARRAYD:
			fout<<"INPUTARRAYD"<<pCode[i].sd.iNumber;
			break;
		case OP_INPUTARRAYI:
			fout<<"INPUTARRAYI"<<pCode[i].sd.iNumber;
			break;
		case OP_INPUTC:
			fout<<"INPUTC"<<pCode[i].sd.iNumber;
			break;
		case OP_INPUTCA:
			fout<<"INPUTCA"<<pCode[i].sd.iNumber;
			break;
		case OP_INPUTD:
			fout<<"INPUTD"<<pCode[i].sd.iNumber;
			break;
		case OP_INPUTI:
			fout<<"INPUTI"<<pCode[i].sd.iNumber;
			break;
		case OP_JUMP:
			fout<<"JUMP"<<pCode[i].sd.iNumber;
			break;
		case OP_LESSC:
			fout<<"LESSC"<<pCode[i].sd.iNumber;
			break;
		case OP_LESSD:
			fout<<"LESSD"<<pCode[i].sd.iNumber;
			break;
		case OP_LESSEQUALC:
			fout<<"LESSEQUALC"<<pCode[i].sd.iNumber;
			break;
		case OP_LESSEQUALD:
			fout<<"LESSEQUALD"<<pCode[i].sd.iNumber;
			break;
		case OP_LESSEQUALI:
			fout<<"LESSEQUALI"<<pCode[i].sd.iNumber;
			break;
		case OP_LESSI:
			fout<<"LESSI"<<pCode[i].sd.iNumber;
			break;
		case OP_LOADARRAY:
			fout<<"LOADARRAY"<<pCode[i].sd.iNumber;
			break;
		case OP_LOADARRAYC:
			fout<<"LOADARRAYC"<<pCode[i].sd.iNumber;
			break;
		case OP_LOADARRAYD:
			fout<<"LOADARRAYD"<<pCode[i].sd.iNumber;
			break;
		case OP_LOADARRAYI:
			fout<<"LOADARRAYI"<<pCode[i].sd.iNumber;
			break;
		case OP_LOADCONSTC:
			fout<<"LOADCONSTC"<<"\'"<<DesysString(pCode[i].sd.cNumber)<<"\'";
			break;
		case OP_LOADCONSTD:
			fout<<"LOADCONSTD"<<pCode[i].sd.dNumber;
			break;
		case OP_LOADCONSTI:
			fout<<"LOADCONSTI"<<pCode[i].sd.iNumber;
			break;
		case OP_LOADVARC:
			fout<<"LOADVARC"<<pCode[i].sd.iNumber;
			break;
		case OP_LOADVARD:
			fout<<"LOADVARD"<<pCode[i].sd.iNumber;
			break;
		case OP_LOADVARI:
			fout<<"LOADVARI"<<pCode[i].sd.iNumber;
			break;
		case OP_MINUSC:
			fout<<"MINUSC";
			break;
		case OP_MINUSD:
			fout<<"MINUSD";
			break;
		case OP_MINUSI:
			fout<<"MINUSI";
			break;
		case OP_MODC:
			fout<<"MODC";
			break;
		case OP_MODI:
			fout<<"MODI";
			break;
		case OP_NEWARRAYC:
			fout<<"NEWARRAYC"<<pCode[i].sd.iNumber<<'\t'<<pCode[i].sd.iNumber2;
			break;
		case OP_NEWARRAYD:
			fout<<"NEWARRAYD"<<pCode[i].sd.iNumber<<'\t'<<pCode[i].sd.iNumber2;
			break;
		case OP_NEWARRAYI:
			fout<<"NEWARRAYI"<<pCode[i].sd.iNumber<<'\t'<<pCode[i].sd.iNumber2;
			break;
		case OP_NOTEQUALC:
			fout<<"NOTEQUALC"<<pCode[i].sd.iNumber;
			break;
		case OP_NOTEQUALD:
			fout<<"NOTEQUALD"<<pCode[i].sd.iNumber;
			break;
		case OP_NOTEQUALI:
			fout<<"NOTEQUALI"<<pCode[i].sd.iNumber;
			break;
		case OP_NULL:
			fout<<"NULL";
			break;
		case OP_OUTPUTC:
			fout<<"OUTPUTC";
			break;
		case OP_OUTPUTCA:
			fout<<"OUTPUTCA"<<pCode[i].sd.iNumber;
			break;
		case OP_OUTPUTD:
			fout<<"OUTPUTD";
			break;
		case OP_OUTPUTI:
			fout<<"OUTPUTI";
			break;
		case OP_OUTPUTS:
			fout<<"OUTPUTS"<<"\""<<DesysString(pCode[i].sd.string)<<"\"";
			break;
		case OP_PARAMTRANSA:
			fout<<"PARAMTRANSA"<<pCode[i].sd.iNumber<<'\t'<<pCode[i].sd.iNumber2;
			break;
		case OP_PARAMTRANSC:
			fout<<"PARAMTRANSC"<<pCode[i].sd.iNumber<<'\t'<<pCode[i].sd.iNumber2;
			break;
		case OP_PARAMTRANSD:
			fout<<"PARAMTRANSD"<<pCode[i].sd.iNumber<<'\t'<<pCode[i].sd.iNumber2;
			break;
		case OP_PARAMTRANSI:
			fout<<"PARAMTRANSI"<<pCode[i].sd.iNumber<<'\t'<<pCode[i].sd.iNumber2;
			break;
		case OP_PLUSC:
			fout<<"PLUSC";
			break;
		case OP_PLUSD:
			fout<<"PLUSD";
			break;
		case OP_PLUSI:
			fout<<"PLUSI";
			break;
		case OP_RETURN:
			fout<<"RETURN"<<pCode[i].sd.iNumber;
			break;
		case OP_RETURNC:
			fout<<"RETURNC"<<pCode[i].sd.iNumber;
			break;
		case OP_RETURND:
			fout<<"RETURND"<<pCode[i].sd.iNumber;
			break;
		case OP_RETURNI:
			fout<<"RETURNI"<<pCode[i].sd.iNumber;
			break;
		case OP_SAVEC:
			fout<<"SAVEC"<<pCode[i].sd.iNumber;
			break;
		case OP_SAVEARRAYC:
			fout<<"SAVEARRAYC"<<pCode[i].sd.iNumber;
			break;
		case OP_SAVEARRAYD:
			fout<<"SAVEARRAYD"<<pCode[i].sd.iNumber;
			break;
		case OP_SAVEARRAYI:
			fout<<"SAVEARRAYI"<<pCode[i].sd.iNumber;
			break;
		case OP_SAVED:
			fout<<"SAVED"<<pCode[i].sd.iNumber;
			break;
		case OP_SAVEI:
			fout<<"SAVEI"<<pCode[i].sd.iNumber;
			break;
		case OP_SLASHC:
			fout<<"SLASHC";
			break;
		case OP_SLASHD:
			fout<<"SLASHD";
			break;
		case OP_SLASHI:
			fout<<"SLASHI";
			break;
		case OP_TIMESC:
			fout<<"TIMESC";
			break;
		case OP_TIMESD:
			fout<<"TIMESD";
			break;
		case OP_TIMESI:
			fout<<"TIMESI";
			break;
//***************************************************************************//
		//********** math
		case OP_ABSC:
			fout<<"ABSC";
			break;
		case OP_ABSD:
			fout<<"ABSD";
			break;
		case OP_ABSI:
			fout<<"ABSI";
			break;
		case OP_ARCCOS:
			fout<<"ARCCOS";
			break;
		case OP_ARCCTG:
			fout<<"ARCCTG";
			break;
		case OP_ARCSIN:
			fout<<"ARCSIN";
			break;
		case OP_ARCTG:
			fout<<"ARCTG";
			break;
		case OP_CH:
			fout<<"CH";
			break;
		case OP_COS:
			fout<<"COS";
			break;
		case OP_CTG:
			fout<<"CTG";
			break;
		case OP_CTH:
			fout<<"CTH";
			break;
		case OP_EXP:
			fout<<"EXP";
			break;
		case OP_LG:
			fout<<"LG";
			break;
		case OP_LN:
			fout<<"LN";
			break;
		case OP_POW:
			fout<<"POW";
			break;
		case OP_SH:
			fout<<"SH";
			break;
		case OP_SIN:
			fout<<"SIN";
			break;
		case OP_SQRT:
			fout<<"SQRT";
			break;
		case OP_TG:
			fout<<"TG";
			break;
		case OP_TH:
			fout<<"TH";
			break;
		//********** string
		case OP_STRCMP:
			fout<<"STRCMP"<<pCode[i].sd.iNumber<<'\t'<<pCode[i].sd.iNumber2;
			break;
		case OP_STRCPYCA:
			fout<<"STRCPYCA"<<pCode[i].sd.iNumber<<'\t'<<pCode[i].sd.iNumber2;
			break;
		case OP_STRCPYS:
			fout<<"STRCPYS"<<pCode[i].sd.iNumber<<"\t\""<<DesysString(pCode[i].sd.string2)<<"\"";
			break;
		case OP_STRLENCA:
			fout<<"STRLENCA"<<pCode[i].sd.iNumber;
			break;
		case OP_STRLENS:
			fout<<"STRLENS"<<'\"'<<DesysString(pCode[i].sd.string)<<'\"';
			break;
		case OP_STRLWR:
			fout<<"STRLWR"<<pCode[i].sd.iNumber;
			break;
		case OP_STRUPR:
			fout<<"STRUPR"<<pCode[i].sd.iNumber;
			break;
		//********** array
		case OP_AVERAGEC:
			fout<<"AVERAGEC"<<pCode[i].sd.iNumber;
			break;
		case OP_AVERAGED:
			fout<<"AVERAGED"<<pCode[i].sd.iNumber;
			break;
		case OP_AVERAGEI:
			fout<<"AVERAGEI"<<pCode[i].sd.iNumber;
			break;
		case OP_DOWNSORTC:
			fout<<"DOWNSORTC"<<pCode[i].sd.iNumber;
			break;
		case OP_DOWNSORTD:
			fout<<"DOWNSORTD"<<pCode[i].sd.iNumber;
			break;
		case OP_DOWNSORTI:
			fout<<"DOWNSORTI"<<pCode[i].sd.iNumber;
			break;
		case OP_MAXC:
			fout<<"MAXC"<<pCode[i].sd.iNumber;
			break;
		case OP_MAXD:
			fout<<"MAXD"<<pCode[i].sd.iNumber;
			break;
		case OP_MAXI:
			fout<<"MAXI"<<pCode[i].sd.iNumber;
			break;
		case OP_MINC:
			fout<<"MINC"<<pCode[i].sd.iNumber;
			break;
		case OP_MIND:
			fout<<"MIND"<<pCode[i].sd.iNumber;
			break;
		case OP_MINI:
			fout<<"MINI"<<pCode[i].sd.iNumber;
			break;
		case OP_SUMC:
			fout<<"SUMC"<<pCode[i].sd.iNumber;
			break;
		case OP_SUMD:
			fout<<"SUMD"<<pCode[i].sd.iNumber;
			break;
		case OP_SUMI:
			fout<<"SUMI"<<pCode[i].sd.iNumber;
			break;
		case OP_UPSORTC:
			fout<<"UPSORTC"<<pCode[i].sd.iNumber;
			break;
		case OP_UPSORTD:
			fout<<"UPSORTD"<<pCode[i].sd.iNumber;
			break;
		case OP_UPSORTI:
			fout<<"UPSORTI"<<pCode[i].sd.iNumber;
			break;
		default:
			fout<<"--  未知操作符，请与程序提供者联系！";
			break;
		}
		fout<<'\n';
	}
	fout.close();
}