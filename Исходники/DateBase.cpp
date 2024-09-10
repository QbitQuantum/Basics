bool CDateBase::InsertData(CString id,CString time,CString data)
{
	

//	AdoInitCommand();
	CreateTable(id);

	id = "tb_"+id;

   /*具体查询*/
	char uid[50];
	strcpy(uid,id.GetBuffer(0));

	char datatime[50];
	strcpy(datatime,time.GetBuffer(0));

	char content[1024];
	strcpy(content,data.GetBuffer(0));
	
	CString szSql;
	szSql.Format("insert into %s (time,content)values('%s','%s')",uid,datatime,content);
	_variant_t vr; 
    try 
    { 
        m_pConnection->Execute((_bstr_t)szSql,&vr,adExecuteNoRecords); 
    } 
    catch(_com_error&  e)          
    {          
//		AfxMessageBox("错误！");  
        AfxMessageBox(e.Description());  
        //ado.AdoClose();
        return false;          
    } 
//	AfxMessageBox("写入数据库正确");

	return true;
}