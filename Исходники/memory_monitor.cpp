LPCSTR inline file_name()
{
	static string_path			file = " ";
	if(file[0]==' '){
		_mkdir					(output_folder);

		__time64_t				long_time;
		_time64					(&long_time);
		tm						new_time;
		new_time				= *_localtime64(&long_time);
		string256				file_name;
		strftime				(file_name,sizeof(file_name),"%Y.%m.%d.%H.%M.%S",&new_time);
		strconcat				(sizeof(file),file,output_folder,file_name,output_extension);
	}
	return file;
}