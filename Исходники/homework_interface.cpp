/*修改作业，用到作业号，教师号，修改的作业名，作业答案，作业内容，作业路径，作业选择题数。修改的标志*/
int AmendBasicHomework(unsigned int homeworkid,unsigned int teacherid,string homeworkname, string answer, string homeworkcontent,string teacherpath,unsigned int title_num, int change_item)
{
	MysqlOperation *mysql = homework_cpool.get_connection();
	string query;
	string path;
	string beforepath;
	string commend;
	int i = 0; 
	while(i<4)
	{
		cout<<"amend basic homework\n";
		cout<<(change_item&(1<<i))<<endl;
		if((change_item&(1<<i)) != 0)
		{
			cout<<i<<endl;
			switch(i)
			{
				case NAME_CHANGE:
					query = string("select homeworkpath,homeworkname from Homework where homeworkID=");
					query = query+edwin::Handle::int_to_string(homeworkid)+";";
					cout<<query<<endl;
					if(mysql->select(query.c_str()))
					{
						cout<<"select homeworkname error\n";
						homework_cpool.release_connection(mysql);
						return -2;
					}
					beforepath = beforepath+mysql->res[0][0]+"/"+mysql->res[0][1]+".txt";
					path =path+mysql->res[0][0]+"/"+homeworkname+".txt";
					cout<<beforepath<<endl;
					cout<<path<<endl;
					if(access(beforepath.c_str(), 0))
					{
						commend = "touch "+path;
						system(commend.c_str());
					}
					else
					{
						commend = "mv "+beforepath+" "+path;
						system(commend.c_str());
					}
					query = string("update Homework set homeworkname=");
					query = query+"'"+homeworkname+"'"+"where "+"homeworkID="+edwin::Handle::int_to_string(homeworkid)+";";
					cout<<query<<endl;
					if(mysql->update(query.c_str()))
					{
						cout<<"update homeworkname error\n";
						homework_cpool.release_connection(mysql);
						return -1;
					}
					cout<<"change name\n";
					break;
				case CONTENT_CHANGE:
					query = string("select homeworkpath,homeworkname from Homework where homeworkID=");
					query = query+edwin::Handle::int_to_string(homeworkid)+";";
					cout<<query<<endl;
					if(mysql->select(query.c_str()))
					{
						cout<<"select homeworkname error\n";
						homework_cpool.release_connection(mysql);
						return -2;
					}
					path = path+mysql->res[0][0]+"/"+mysql->res[0][1]+".txt";
					cout<<path<<endl;
					cout<<"change content\n";
					break;
				case PATH_CHANGE:
					query = string("select homeworkpath from Homework where homeworkID=")+edwin::Handle::int_to_string(homeworkid)+";";
					cout<<query<<endl;
					cout<<"path change\n";
					if(mysql->select(query.c_str()))
					{
						cout<<"select homeworkpath error\n";
						homework_cpool.release_connection(mysql);
						return -2;
					}
					beforepath += mysql->res[0][0];
					cout<<beforepath<<endl;
					path = HOMEPATH;
					path = path+edwin::Handle::int_to_string(teacherid)+"/"+teacherpath;
					if(access(path.c_str(), 0))
					{
						commend = "mkdir "+path;
						system(commend.c_str());
					}
					else
					{
						commend = "mv "+beforepath+" "+path+" -r";
						if(system(commend.c_str())<=0)
						{
							commend = "mkdir "+path;
							system(commend.c_str());
						}

					}
					query = string("update Homework set homeworkpath=");
				    query = query+"'"+HOMEPATH+edwin::Handle::int_to_string(teacherid)+"/"+teacherpath+"' "+"where "+"homeworkID="+edwin::Handle::int_to_string(homeworkid)+";";
				    cout<<query<<endl;
					if(mysql->update(query.c_str()))
					{
						cout<<"update homeworkpath error\n";
						homework_cpool.release_connection(mysql);
						return -3;
					}
					cout<<"change path\n";
					break;
				case ANSWER_CHANGE:
					query = string("update Homework set homeworkanswer=");
					query = query+"'"+answer+"' "+"where "+"homeworkID="+edwin::Handle::int_to_string(homeworkid)+";";
					cout<<query<<endl;
					if(mysql->update(query.c_str()))
					{
						cout<<"update homeworkanswer error\n";
						homework_cpool.release_connection(mysql);
						return -4;
					}
					cout<<"change answer\n";
					break;
				default:
					break;
			}
			if(i == 1)
			{
				File fd(path, ios_base::in|ios_base::out|ios_base::trunc);
				fd.open(ios_base::in|ios_base::out|ios_base::trunc);
				fd.write(homeworkcontent);
			}
		}
		i++;
	}
	homework_cpool.release_connection(mysql);
	return 0;
}