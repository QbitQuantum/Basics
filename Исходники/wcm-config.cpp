void SaveStringList(const char *section, ccollect< carray<char> > &list)
{
	try {
		SysTextFileOut out;
				
		FSPath path = configDirPath;
		path.Push(CS_UTF8, carray_cat<char>(section, ".cfg").ptr());
		out.Open( (sys_char_t*)path.GetString(sys_charset_id) );
		
		for (int i = 0; i<list.count(); i++)
		{
			if (list[i].ptr() && list[i][0])
			{
				out.Put(list[i].ptr());
				out.PutC('\n');
			}
		}
		
		out.Flush();
		out.Close();
		
	} catch (cexception *ex) {
		ex->destroy();
		return ;
	}
}