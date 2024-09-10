void tar_cmd_parser(LPCSTR szCmdLine,CTar32CmdInfo &cmdinfo)
{
	std::vector<std::string> args;	// command line array
	if(!split_cmdline_with_response(szCmdLine,args)){
		throw CTar32Exception("commandline split error", ERROR_COMMAND_NAME);
	}

	char command = 0;	// main command. ('x','c','l')
	//std::string current_directory; -> into CTar32CmdInfo
	std::vector<std::string>::iterator argi = args.begin();
	bool option_end = false;

	while(argi != args.end()){
		//string::iterator stri = (*argi).begin();
		const char *stri = (*argi).c_str();
		if(argi==args.begin() || (*stri == '-' && *(stri+1) != '\0' && option_end == false)){
			if(*stri == '-'){
				stri++;
			}
			if(*stri == '-' && *(stri+1) != '\0'){
				stri++;
				const std::string long_option = (*argi).substr(stri - (*argi).c_str());
				std::string key = long_option;
				std::string val;
				int len;
				if((len = long_option.find('=')) != std::string::npos){
					key = long_option.substr(0, len);
					val = long_option.substr(len + 1);
				}
				if(key == "use-directory"){
					cmdinfo.b_use_directory = ((val=="") ? true : (0!=atoi(val.c_str())));
				}else if(key == "absolute-paths"){
					cmdinfo.b_absolute_paths = ((val=="") ? true : (0!=atoi(val.c_str())));
				}else if(key == "display-dialog"){
					cmdinfo.b_display_dialog = ((val=="") ? true : (0!=atoi(val.c_str())));
				}else if(key == "message-loop"){
					cmdinfo.b_message_loop = ((val=="") ? true : (0!=atoi(val.c_str())));
				}else if(key == "inverse-procresult"){
					cmdinfo.b_inverse_procresult = ((val=="") ? true : (0!=atoi(val.c_str())));
				}else if(key == "bzip2" || key == "bzip"){
					cmdinfo.archive_type = ARCHIVETYPE_BZ2;
					cmdinfo.compress_level = atoi(val.c_str());
					if(cmdinfo.compress_level<1) cmdinfo.compress_level = 9;
					if(cmdinfo.compress_level>9) cmdinfo.compress_level = 9;
				}else if(key == "gzip"){
					cmdinfo.archive_type = ARCHIVETYPE_GZ;
					cmdinfo.compress_level = atoi(val.c_str());
					if(cmdinfo.compress_level<1) cmdinfo.compress_level = 5;
					if(cmdinfo.compress_level>9) cmdinfo.compress_level = 5;
				}else if(key == "lzma"){
					cmdinfo.archive_type = ARCHIVETYPE_LZMA;
					cmdinfo.compress_level = atoi(val.c_str());
					if(cmdinfo.compress_level<0) cmdinfo.compress_level = 6;
					if(cmdinfo.compress_level>9) cmdinfo.compress_level = 6;
				}else if(key == "xz"){
					cmdinfo.archive_type = ARCHIVETYPE_XZ;
					cmdinfo.compress_level = atoi(val.c_str());
					if(cmdinfo.compress_level<0) cmdinfo.compress_level = 6;
					if(cmdinfo.compress_level>9) cmdinfo.compress_level = 6;
				}else if(key == "confirm-overwrite"){
					cmdinfo.b_confirm_overwrite = ((val=="") ? true : (0!=atoi(val.c_str())));
				}else if(key == "convert-charset"){
					if(val=="")cmdinfo.archive_charset = CHARSET_UNKNOWN;
					else if(stricmp(val.c_str(),"none")==0)cmdinfo.archive_charset  = CHARSET_DONTCARE;
					else if(stricmp(val.c_str(),"auto")==0)cmdinfo.archive_charset  = CHARSET_UNKNOWN;
					else if(stricmp(val.c_str(),"sjis")==0)cmdinfo.archive_charset  = CHARSET_SJIS;
					else if(stricmp(val.c_str(),"eucjp")==0)cmdinfo.archive_charset = CHARSET_EUCJP;
					else if(stricmp(val.c_str(),"utf8")==0)cmdinfo.archive_charset  = CHARSET_UTF8;
					else cmdinfo.archive_charset = CHARSET_DONTCARE;
				}else if(key == "sort-by-ext"){
					cmdinfo.b_sort_by_ext = ((val=="") ? true : (0!=atoi(val.c_str())));
				}else if(key == "sort-by-path"){
					cmdinfo.b_sort_by_path = ((val=="") ? true : (0!=atoi(val.c_str())));
				}else{
					/* igonore */;
				}
				argi++;
				continue;
			}
			std::vector<std::string>::iterator cur_argi = argi;
			//while(stri != (*cur_argi).end()){
			while(stri != (*cur_argi).c_str()+(*cur_argi).length()){
				switch(*stri){
				case 'x':
					command = 'x';break;
				case 'c':
					command = 'c';break;
				case 'l':
				case 't': // どんぞ：追加
					command = 'l';break;
				case 'p':
					command = 'x';
					cmdinfo.b_print = true;
					break;
				case 'f':
					if(++argi == args.end()){
						throw CTar32Exception("'f' follow no directory name", ERROR_COMMAND_NAME);
					}
					cmdinfo.arcfile = *argi;
					break;
				case 'o':
					if(++argi == args.end()){
						throw CTar32Exception("'o' follow no directory name", ERROR_COMMAND_NAME);
					}
					cmdinfo.current_directory = *argi;
					// stri = argi->end()-1;
					break;
				case 'z':
					cmdinfo.archive_type = ARCHIVETYPE_GZ;
					if(isdigit(*(stri+1))){
						stri++;
						cmdinfo.compress_level = ((char)*stri) - '0';
					}else{
						cmdinfo.compress_level = 6;
					}
					break;
				case 'B':
				case 'j':
					cmdinfo.archive_type = ARCHIVETYPE_BZ2;
					if(isdigit(*(stri+1))){
						stri++;
						cmdinfo.compress_level = ((char)*stri) - '0';
					}else{
						cmdinfo.compress_level = 9;
					}
					break;
				case 'J':
					cmdinfo.archive_type = ARCHIVETYPE_XZ;
					if(isdigit(*(stri+1))){
						stri++;
						cmdinfo.compress_level = ((char)*stri) - '0';
					}else{
						cmdinfo.compress_level = 6;
					}
					break;
				case 'Z':
					cmdinfo.archive_type = ARCHIVETYPE_Z;
					if(isdigit(*(stri+1))){
						stri++;
						cmdinfo.compress_level = ((char)*stri) - '0';
					}else{
						cmdinfo.compress_level = 6;
					}
					break;
				case 'G':
					cmdinfo.b_archive_tar = false;
					if(cmdinfo.archive_type == ARCHIVETYPE_NORMAL){
						cmdinfo.archive_type = ARCHIVETYPE_GZ;
						cmdinfo.compress_level = 6;
					}
					break;
				case 'P':
					cmdinfo.b_absolute_paths = true;
					break;
				case 'a':
				case 'v':
				case 'V':
				case 'I':
				case 'i':
				case 'e':
				case 'g':
				case 'S':
				case 'R':	// added by tsuneo 2001.05.14
					/*ignore*/
					break;
				case 'A':
					stri++;
					/*ignore*/
					break;
				case 'b':
				case 'N':
					argi++;
					//stri = argi->end()-1;
					stri = (*argi).c_str()+(*argi).length()-1;
					/*ignore*/
					break;

				case 'U':
					if(isdigit(*(stri+1))){
						stri++;
					}
					/*ignore*/
					break;
				case '-':	// added by tsuneo on 2006/08/04. Patch is provided by Niiyama(HEROPA)-san. Special Thanks to Niiyama(HEROPA)-san.
					option_end = true;
					break;
				default:
					throw CTar32Exception("Invalid Arguments", ERROR_COMMAND_NAME);
				}
				stri++;
			}
			argi++;
		}else{
			const char *file = (*argi).c_str();
			if(*file && ((char*)_mbsrchr((const unsigned char*)file, '\\') == file + strlen(file) - 1)){
				cmdinfo.current_directory = (char*)file;
			}else if(cmdinfo.arcfile.length() == 0){
				cmdinfo.arcfile = *argi;
			}else{
				std::string file = *argi;
				cmdinfo.argfiles.push_back(CTar32CmdInfo::CArgs(file,cmdinfo.current_directory));
			}
			argi++;
		}
	}

	cmdinfo.command = command;
}