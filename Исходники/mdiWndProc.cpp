DWORD WINAPI MdiMachiningBuildThreadProc(LPVOID lpParam)
{
	LPCmdThreadParam  pData; 
  	
	LPCmdThreadParam  pData_nc;
	DWORD dwThreadID;
	LPNCDATA pDataNcGraphMem;
	FILE *file;
	int nItemCount;
	int reallength;

	TCHAR szBuffer[501]; 
	
	
	int decodeNum,compasateNum,tapeNum,ComputeNum;
	int all_decode_num,all_creat_num;

	nc_data decodeData[2*DECODE_NUM_ONCE];
	nc_data compasateData[2*DECODE_NUM_ONCE];
	nc_data tapeData[2*DECODE_NUM_ONCE];
	nc_data ComputeData[2*DECODE_NUM_ONCE];
	M_data MChild[2*DECODE_NUM_ONCE];
	

	
	
	int  fdEdit;  //译码文件句柄定义
	int end_decode;
	

	double compasate_Start_point_X,compasate_Start_point_Y;
    int compasate_build_c;
	nc_data *compasate_cs;

	double tape_Start_point_X,tape_Start_point_Y;
	double tape_Start_point_B,tape_Start_point_C;
    int tape_build_c,first5152flag;
	nc_data *tape_cs;
	


	int nc_start_flag;

	int i;
	int j = 0,k = 0;
    char ptext[100];
	
	

	
			//以下添加mdi加工程序
			//SuspendThread(MdihThread);
			
			compasate_Start_point_X=0.;
			compasate_Start_point_Y=0.;
			compasate_build_c=0;
			
			tape_Start_point_X=0.;
			tape_Start_point_Y=0.;
			tape_build_c=0;
			
			memset(decodeData,0,2*DECODE_NUM_ONCE*sizeof(nc_data));
			memset(compasateData,0,2*DECODE_NUM_ONCE*sizeof(nc_data));
			memset(ComputeData,0,2*DECODE_NUM_ONCE*sizeof(nc_data));
			memset(MChild,0,2*DECODE_NUM_ONCE*sizeof(M_data)); 
		   
			
			compasate_cs = (nc_data *)malloc(sizeof(nc_data));
			memset(compasate_cs,0,sizeof(nc_data));

			tape_cs = (nc_data *)malloc(sizeof(nc_data));
			memset(tape_cs,0,sizeof(nc_data));
			
			


			pData = (LPCmdThreadParam)lpParam;

			end_decode = 0;
			all_decode_num =0;
			all_creat_num = 0;

			nc_start_flag=1;


			
			//将mdi的nc码放到临时文件中
			
			
			
			if ((file = fopen("MdiTemp.txt", "w+")) == NULL)
			{	
				MessageBox (pData->hWnd,"can not create MdiTemp file in function MdiMachiningBuildThreadProc",NULL,NULL);
				
				return 1;
			}


			nItemCount = SendMessage(GetDlgItem(pData->hWnd,IDC_MDILIST),LB_GETCOUNT,0,0);
			
			if(nItemCount==0)
			{
				MessageBox (pData->hWnd,"there is no NCCODE in function MdiMachiningBuildThreadProc",NULL,NULL);
				
				return 1;
			}
			
			for(i=0;i<nItemCount;i++)
			{
				SendMessage(GetDlgItem(pData->hWnd,IDC_MDILIST),LB_GETTEXT,i,(LPARAM)szBuffer);
				reallength = SendMessage(GetDlgItem(pData->hWnd,IDC_MDILIST),LB_GETTEXTLEN,i,0);
				
				if (fwrite(szBuffer, 1, reallength, file) < 0)
				{
        				MessageBox (pData->hWnd,"write file err in function MdiMachiningBuildThreadProc" ,NULL,NULL);
						return 1;
						
				}
			}
			fclose (file);
			fdEdit = _open("MdiTemp.txt", O_RDONLY);

			do{

				do{
					reallength = _read(fdEdit, ptext+k, 1 );
					if(reallength == 0)
					{
						return 0;
					}
					k++;
				}while(ptext[k-1] != ';');
				ptext[k] = 0;


					if(strstr(ptext+j,"X")) 
					{
						data_coorswitch.x=Gcode2d(ptext+j,"X");
					}
					else 
					{
						data_coorswitch.x = 0;
					}
					if(strstr(ptext+j,"Y")) 
					{
						data_coorswitch.y=Gcode2d(ptext+j,"Y");
					}
					else 
					{
						data_coorswitch.y = 0;
					}
					if(strstr(ptext+j,"Z")) 
					{
						data_coorswitch.z=Gcode2d(ptext+j,"Z");
					}
					else 
					{
						data_coorswitch.z = 0;
					}
					if(strstr(ptext,"B")) 
					{
						data_coorswitch.b=Gcode2d(ptext,"B");
					}
					else 
					{
						data_coorswitch.b = 0;
					}
					if(strstr(ptext+j,"C")) 
					{
						data_coorswitch.c=Gcode2d(ptext+j,"C");
					}
					else 
					{
						data_coorswitch.c = 0;
					}

					if(strstr(ptext+j,"G54:"))
					{
						G54_coordinate = data_coorswitch;

					}
					if(strstr(ptext+j,"G55:"))
					{
						G55_coordinate = data_coorswitch;

					}
					if(strstr(ptext+j,"G56:"))
					{
						G56_coordinate = data_coorswitch;

					}
					if(strstr(ptext+j,"G57:"))
					{
						G57_coordinate = data_coorswitch;

					}
					if(strstr(ptext+j,"G58:"))
					{
						G58_coordinate = data_coorswitch;

					}
					if(strstr(ptext+j,"G59:"))
					{
						G59_coordinate = data_coorswitch;

					}
					if(strstr(ptext+j,"G92:"))
					{
						data_w = data_coorswitch;
						data_r.x = data_m.x - data_w.x;
						data_r.y = data_m.y - data_w.y;
						data_r.z = data_m.z - data_w.z;
						data_r.b = data_m.b - data_w.b;
						data_r.c = data_m.c - data_w.c;



					}
					j = k;
					readbuffer_to_fc(pData->hWnd);
					fc_upday(hWndCoor);
			}while(reallength !=0);
			




			SuspendThread(MdihThread);
			//开设译码绘图内存
			pDataNcGraphMem = (LPNCDATA)HeapAlloc(GetProcessHeap(),
											HEAP_ZERO_MEMORY,
											MAX_NC_MEM*sizeof(nc_data)
											);
			if(pDataNcGraphMem == NULL)
			{
				MessageBox(pData->hWnd,"can not alloc heapmemory in function MdiMachiningBuildThreadProc",NULL,NULL);
				return 1;
			}

			//开设NC代码内存
			lpNcCodeMem = (LPNCCODE)HeapAlloc(GetProcessHeap(),
											HEAP_ZERO_MEMORY,
											MAX_NC_MEM*sizeof(nc_code)
											);
			if(pDataNcGraphMem == NULL)
			{
				MessageBox(pData->hWnd,"can not alloc heapmemory in function AutoMachiningBuildThreadProc",NULL,NULL);
				return 1;
			}

			
			 //为读取文件到内存打开文件
			fdEdit = _open(szBuffer, O_RDONLY);
		 
			if (fdEdit <= 0) 
			{		                        
				MessageBox (pData->hWnd, "can not open file in AutoMachiningBuildThreadProc","Program", MB_OK | MB_ICONSTOP);
				return 1;
			}

			ReadNcCodeFileToMem(pData->hWnd,fdEdit,lpNcCodeMem,&NcCodeNum);
			_close(fdEdit);


			//打开译码文件
			fdEdit = _open("MdiTemp.txt", O_RDONLY);
		 
			if (fdEdit <= 0)
			{		                        
				MessageBox (pData->hWnd, "can not open file in MdiMachiningBuildThreadProc","Program", MB_OK | MB_ICONSTOP);
				return 1;
			}
			ReadNcCodeFileToMem(pData->hWnd,fdEdit,lpNcCodeMem,&NcCodeNum);
			do{
					if(decode(pData->hWnd,lpNcCodeMem,decodeData,&decodeNum,&all_decode_num,&end_decode,MChild)==1) return 1; // 分段译码
				
					if(compensate(pData->hWnd,decodeData,decodeNum,compasateData,&compasateNum,&compasate_Start_point_X,&compasate_Start_point_Y, &compasate_build_c,compasate_cs)==1) return 1;//分段刀具补偿
				  
				  	
					if(tape(pData->hWnd,compasateData,compasateNum,tapeData,&tapeNum,&tape_Start_point_X,&tape_Start_point_Y,&tape_build_c,&first5152flag,tape_cs,&tape_Start_point_B,&tape_Start_point_C)==1,&tape_Start_point_B,&tape_Start_point_C) return 1; //锥面补偿
					if(DSP_Compute(pData->hWnd,tapeData,tapeNum,ComputeData,&ComputeNum)==1) return 1; 			
					
							
					CopyMemory(pDataNcGraphMem+all_creat_num,ComputeData,(ComputeNum*sizeof(nc_data)));
						
				

					memset(compasateData,0,2*DECODE_NUM_ONCE*sizeof(nc_data));
					memset(tapeData,0,2*DECODE_NUM_ONCE*sizeof(nc_data));
					memset(ComputeData,0,2*DECODE_NUM_ONCE*sizeof(nc_data));


					all_creat_num=all_creat_num + ComputeNum;
					ComputeNum = 0;
					compasateNum=0;
					tapeNum=0;
					
					//开设向下位机传送数据线程
					if(nc_start_flag==1)
					{
						pData_nc = (LPCmdThreadParam)HeapAlloc(GetProcessHeap(),
											HEAP_ZERO_MEMORY,
											sizeof(CmdThreadParam)
											);

						if(pData_nc == NULL)
						{
							MessageBox(pData->hWnd,"can not alloc heapmemory in function MdiMachiningBuildThreadProc",NULL,NULL);
							return 1;
						}


						pData_nc->hWnd = pData->hWnd;
						pData_nc->wndCtrl = pData->wndCtrl;
						pData_nc->menuID = pData->menuID;
						pData_nc->notifyCode =pData-> notifyCode;
						pData_nc->ncMem = pDataNcGraphMem;

						NcSendhThread = CreateThread(
								NULL,
								0,
								NcSendThreadProc,
								pData_nc,
								0,
								&dwThreadID
								);

						if( NcSendhThread==NULL)
						{
							MessageBox(pData->hWnd,"can not create Thread in function MdiMachiningBuildThreadProc",NULL,NULL);
							return 1;
						}

						SendNCDriverUserDecodeEvent(pData->hWnd,NcSendhThread);  //向驱动程序下传传送数据线程的句柄
						nc_start_flag = 0;
					}


			}while(end_decode != 1);

			_close(fdEdit);



			
			//find_draw_param(GetDlgItem (pData->hWnd, IDC_AUTOGRAPH),pDataNcGraphMem,&auto_draw_width,&auto_draw_length,&auto_mw, &auto_ml,all_creat_num);//求取画图参数
			

			//draw_all(GetDlgItem (pData->hWnd, IDC_AUTOGRAPH),pDataNcGraphMem,auto_draw_width,auto_draw_length,auto_mw, auto_ml,all_creat_num); //画全部图
			
					
			free(tape_cs);
		    free(compasate_cs);
	

	//取消线程、释放内存
	CloseHandle(MdihThread);
	if(HeapFree(GetProcessHeap(),HEAP_NO_SERIALIZE,pData) == 0){
		MessageBox(pData->hWnd,"can not free heapmemory in function MdiMachiningBuildThreadProc",NULL,NULL);
		return 1;
	}
	return 0;
}