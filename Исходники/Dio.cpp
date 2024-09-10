void Dio::update(char keyboard[],bool& takeinput,bool& newscene)
{
	//ifstream infile;
	//infile.open("Dialogue.txt");
	string tempName;
	if (newscene)
	{
		if (!infile.is_open())
		{
			//cout<<"File not found"<<endl;
			name="File not found";
			//wchar_t buffer[190];
			std::wstring stemp = s2ws(name);
			LPCWSTR result = stemp.c_str();
			swprintf_s(tempname, 190, L"%s",result);
			speaker[0].text=tempname;
		
		}
		else
		{
			if(keyboard[DIK_RETURN]&0x80)
			{
				if(!readname&&!readtext&&takeinput)
				{
					readname=true;
					readtext=true;
					saidtext=true;
				}
				takeinput = false;
			}
			//bool readname=true;
			if (readname)
			{
				//getline(infile,name, '#');
				getline(infile,name, '#');
				if(name[0]==10)
				{
					tempName = "";
					for(int i = 0;i<name.length()-1;++i)
					{
						tempName += name[i+1];
					}
					name = tempName;
				}
				if (name=="Snake")
				{
					//display image snake
					texholder=pics[0];
					//wchar_t buffer[190];
					std::wstring stemp = s2ws(name);
					LPCWSTR result = stemp.c_str();
					swprintf_s(tempname, 190, L"%s",result);
					speaker[0].text=tempname;
					readname=false;
			
				}
				else if (name=="NurseJoy")
				{
					//display image Nurse Joy
					texholder=pics[1];
					//wchar_t buffer[190];
					std::wstring stemp = s2ws(name);
					LPCWSTR result = stemp.c_str();
					swprintf_s(tempname, 190, L"%s",result);
					speaker[0].text=tempname;
					readname=false;
				}
				else if (name=="SolidChu")
				{
					//display image Solid Chu
					texholder=pics[2];
					//wchar_t buffer[190];
					std::wstring stemp = s2ws(name);
					LPCWSTR result = stemp.c_str();
					swprintf_s(tempname, 190, L"%s",result);
					speaker[0].text=tempname;
					readname=false;
				}
				else if (name=="EvilChu")
				{
					//display image Evil chu
					texholder=pics[3];
					//wchar_t buffer[190];
					std::wstring stemp = s2ws(name);
					LPCWSTR result = stemp.c_str();
					swprintf_s(tempname, 190, L"%s",result);
					speaker[0].text=tempname;
					readname=false;
				}
			}
			//bool readtext=true;
			//string holder;
			//text="";
			if (readtext)
			{
			
				// timing logic
				then = now;
				now = clock();
				passed = now - then;
				soon = now + delay;
				//print text
				// throttle code
				while(clock() < soon){Sleep(1);};
				if (keyboard[DIK_LSHIFT]&0x80)
				{	
					bool done=false;
					while(!done)
					{
						getline(infile,name, '#');
						if(name=="endscene")
						{
							done=true;
						}
					}
				}
				else if (saidtext)
				{
					getline(infile,holder,'#');
					saidtext=false;
					for(int i=0;i<holder.size();++i)
					{
						text[i]=holder[i];
					}
					size_of_container=holder.size();
				}
			
				if (name=="endscene")
				{
					readtext=true;
					readname=true;
					saidtext=true;
					texholder.tex=0;
					newscene=false;
					//name="";
					for (int i=0;i<256;i++)
					{
						text[i]=0;
					}
					addedwords.clear();
					c=0;
					std::wstring stemp = s2ws(name);
					LPCWSTR result = stemp.c_str();
					swprintf_s(tempname, 190, L"%s",result);
					speaker[0].text=tempname;
					//text="";
					std::wstring stemp2 = s2ws(text);
					LPCWSTR result2 = stemp2.c_str();
					swprintf_s(temptext, 190, L"%s",result2);
					speaker[1].text=temptext;
							
				}
				else if (holder=="stop")
				{
					readtext=false;
					infile.ignore();
					saidtext=true;
					takeinput=true;
					//infile.close();
					for (int i=0;i<256;i++)
					{
						text[i]=0;
					}
					addedwords.clear();
				}
						
				else if (holder!="endscene")
				{
					//text=text+holder;
					//print text
					//wchar_t buffer2[190];
					//test bellow
					if(keyboard[DIK_SPACE]&0x80)
					{
						saidtext=true;
						c=0;
						std::wstring stemp2 = s2ws(text);
						LPCWSTR result2 = stemp2.c_str();
						swprintf_s(temptext, 190, L"%s",result2);
						speaker[1].text=temptext;
					}
					else
					{
						addedwords=addedwords+text[c];
						std::wstring stemp2 = s2ws(addedwords);
						LPCWSTR result2 = stemp2.c_str();
						swprintf_s(temptext, 190, L"%s",result2);
						speaker[1].text=temptext;
						c++;
						if (c==size_of_container)
						{
							saidtext=true;
							c=0;
						}
					}
					//test above
				/*	std::wstring stemp2 = s2ws(text);
					LPCWSTR result2 = stemp2.c_str();
					swprintf_s(temptext, 190, L"%s",result2);
					speaker[1].text=temptext;*/
				}
			}
		}
	}
	
}