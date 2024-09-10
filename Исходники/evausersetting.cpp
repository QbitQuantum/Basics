void EvaUserSetting::loadMsgToSql(const TQString fullName,const bool isQunMsg)
{
	TQFile file(fullName);
	if(!file.open(IO_ReadOnly))
		return ;
	TQString fullNameSql = getEvaUserDir() + "/"+SqlFileName;
	int result;
	char * errmsg = NULL;
	char **dbResult;
	int nRow, nColumn,i=0;
	sqlite3 *db=NULL;
	result=sqlite3_open(fullNameSql.data(),&db);
	if( result != SQLITE_OK ) return;
	TQString sql;
	sqlite3_exec( db,"begin transaction;",0,0,&errmsg);

	TQ_UINT32 r_buddy;
	TQ_UINT32 sender;
	TQString  sNick;
	TQ_UINT32 receiver;
	TQString  rNick;
	TQ_UINT8  type; // 0 auto reply,  1 normal
	TQString  message;
	TQ_UINT32  intTime;
	TQDateTime time;
	TQ_UINT8   fontSize;
	TQ_UINT8   flag; // start from right.  bit 0: u, bit 1: i, bit 2: b
	TQ_UINT8   blue;
	TQ_UINT8   green;
	TQ_UINT8   red;
	TQDataStream stream(&file);
	std::list<chatMessage>srclist;
	while(!stream.atEnd()){
		stream>>r_buddy;
		stream>>sender;
		stream>>sNick;
		stream>>receiver;
		stream>>rNick;
		stream>>type;
		stream>>message;
		stream>>intTime;
		stream>>fontSize;
		stream>>flag;
		stream>>blue;
		stream>>green;
		stream>>red;
		sql.sprintf("select sender from chat where sender=%d and receiver=%d and time=%d and isQunMsg=%d ",sender,receiver,intTime,isQunMsg);
		result = sqlite3_get_table(db,sql.utf8().data(), &dbResult,&nRow, &nColumn, &errmsg);
		if( SQLITE_OK != result ) 
		{
			sqlite3_exec( db,"commit  transaction;",0,0,&errmsg);
			return;
		}
		if(nRow>0) continue; //找到重复的记录
		i++;
		sql.sprintf("insert into chat values (%d,%d,'%s', %d,'%s',%d, '%s', %d,%d, %d, %d,%d,%d,%d)",r_buddy,sender,sNick.local8Bit().data(),receiver,rNick.local8Bit().data(),type,message.local8Bit().data(),intTime,fontSize,flag,blue,green,red,isQunMsg);
		sqlite3_exec( db , sql.utf8().data() , 0 , 0 , &errmsg );
	}
	printf("load %s %i条\n",fullName.data(),i);
	sqlite3_exec( db,"commit transaction;",0,0,&errmsg);
	file.close();
	TQString newfile;
	newfile=fullName+".old";
	unlink(newfile.local8Bit().data());
	rename(fullName.local8Bit().data(),newfile.local8Bit().data());
	return ;
}