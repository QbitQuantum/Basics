void binarySearchforview_networkcontroller(BYTE devLo, BYTE devHi)
{
	//	had_scaned=true;////////////////////////////////////////////////had scan
	if(net_work_is_exist_or_not==true)
		Sleep(200);	    
	else
		Sleep(10);//
	int a=NetController_CheckTstatOnline(devLo,devHi);

	TRACE("L:%d   H:%d  a:%d\n",devLo,devHi,a);
	if(binary_search_crc(a))
		return ;
	char c_array_temp[5]={'0'};
	CString temp="";
	if(a>0)
	{

			///////****************************************************************8888888
			//			TRACE("L:%d   H:%d\n",devLo,devHi);
			//			TRACE("%d\n",a);
		/*
#if 1
			binary_search_result temp;
			temp.baudrate=m_baudrate2;
			temp.id=a;
			temp.product_class_id=read_one(a,7);
			get_serialnumber(temp.serialnumber,temp.id );
			temp.hardware_version=read_one(temp.id ,8);
			m_binary_search_networkcontroller_background_thread.push_back(temp);
			if(read_one(a,7)==NET_WORK_CONT_PRODUCT_MODEL)//net work controller
				keep_back_mac_address(a);
#endif
				*/
			binary_search_result temp;
			temp.baudrate=m_baudrate2;
			unsigned short SerialNum[9];
			memset(SerialNum,0,sizeof(SerialNum));
			int nRet=0;
			temp.id=a;
			nRet=Read_Multi(temp.id,&SerialNum[0],0,9,3);
			if(nRet>0)
			{
				//serial=SerialNum[0]&0x00ff+(SerialNum[0]&0xff00>>8)*256+(SerialNum[1]&0x00ff)*65536
				//	+(SerialNum[1]&0xff00>>8)*16777216;

				if(SerialNum[0]==255&&SerialNum[1]==255&&SerialNum[2]==255&&SerialNum[3]==255)
				{
					srand((unsigned)time(NULL)); 
					SerialNum[0]=rand()%255; 
					SerialNum[1]=rand()%255; 
					SerialNum[2]=rand()%255; 
					SerialNum[3]=rand()%255; 

					write_one(temp.id,0,SerialNum[0]);
					write_one(temp.id,1,SerialNum[1]);
					write_one(temp.id,2,SerialNum[2]);
					write_one(temp.id,3,SerialNum[3]);
				}

				temp.serialnumber=SerialNum[0]+SerialNum[1]*256+SerialNum[2]*256*256+SerialNum[3]*256*256*256;
				temp.product_class_id=SerialNum[7];
				temp.hardware_version=SerialNum[8];
			float tstat_version2;
			tstat_version2=SerialNum[4];//tstat version			
			if(tstat_version2 >=240 && tstat_version2 <250)
				tstat_version2 /=10;
			else 
			{
				tstat_version2 = SerialNum[5]*256+SerialNum[4];	
				tstat_version2 /=10;
			}//tstat_version
			
			temp.software_version=tstat_version2;
					if(read_one(temp.id,185)==0)
						temp.baudrate=9600;
					else
					{
							temp.baudrate=19200;
					}
			temp.nEPsize=read_one(temp.id,326);
			if(temp.serialnumber>0)
			m_binary_search_networkcontroller_background_thread.push_back(temp);
			}

	}
	switch(a)
	{
	case -2:
		//crc error
		if(devLo!=devHi)
		{
			binarySearchforview_networkcontroller(devLo,(devLo+devHi)/2);
			binarySearchforview_networkcontroller((devLo+devHi)/2+1,devHi);
		}
		else
			binarySearchforview_networkcontroller(devLo,devHi);
		break;
	case -3:
		//more than 2 Tstat is connect
		if(devLo!=devHi)
		{
			binarySearchforview_networkcontroller(devLo,(devLo+devHi)/2);
			binarySearchforview_networkcontroller((devLo+devHi)/2+1,devHi);
		}
		else
		{//Two Tstat have the same ID,fewness
			do
			{
				Sleep(20);//////////////////////////////////for running is better
				char c_temp_arr[100]={'\0'};
				if(Read_One(devLo,10)!=-2)//one times
				{
					CString str_temp;
					for(int j=254;j>=1;j--)
						if(j!=devLo)
						{							
							if(!found_same_net_work_controller_by_mac(a))
							{
								bool find=false;//false==no find;true==find
								for(int w=0;w<m_binary_search_product_background_thread.size();w++)
									if(j==m_binary_search_product_background_thread.at(w).id)
									{
										find=true;
										break;
									}
									if(find==false)
									{
										//************************change the Id
										//									Sleep(20);//////////////////////////////////for running is better
										if(Write_One(devLo,10,j)>0)//sometimes write failure ,so inspect,important
											if(j<devLo)
											{
												/*
												#if 1
												binary_search_result temp;
												temp.baudrate=m_baudrate2;
												temp.id=j;
												temp.product_class_id=read_one(j,7);
												get_serialnumber(temp.serialnumber,j);
												temp.hardware_version=read_one(j,8);
												m_binary_search_networkcontroller_background_thread.push_back(temp);
												if(read_one(j,7)==NET_WORK_CONT_PRODUCT_MODEL)//net work controller
													keep_back_mac_address(j);
												#endif
												*/

												binary_search_result temp;
												temp.baudrate=m_baudrate2;
												unsigned short SerialNum[9];
												memset(SerialNum,0,sizeof(SerialNum));
												int nRet=0;
												temp.id=j;
												nRet=Read_Multi(temp.id,&SerialNum[0],0,9,3);
												if(nRet>0)
												{
													//serial=SerialNum[0]&0x00ff+(SerialNum[0]&0xff00>>8)*256+(SerialNum[1]&0x00ff)*65536
													//	+(SerialNum[1]&0xff00>>8)*16777216;

														if(SerialNum[0]==255&&SerialNum[1]==255&&SerialNum[2]==255&&SerialNum[3]==255)
														{
															srand((unsigned)time(NULL)); 
															SerialNum[0]=rand()%255; 
															SerialNum[1]=rand()%255; 
															SerialNum[2]=rand()%255; 
															SerialNum[3]=rand()%255; 
															write_one(temp.id,0,SerialNum[0]);
															write_one(temp.id,1,SerialNum[1]);
															write_one(temp.id,2,SerialNum[2]);
															write_one(temp.id,3,SerialNum[3]);

														}

													temp.serialnumber=SerialNum[0]+SerialNum[1]*256+SerialNum[2]*256*256+SerialNum[3]*256*256*256;
													temp.product_class_id=SerialNum[7];
													temp.hardware_version=SerialNum[8];
														float tstat_version2;
													tstat_version2=SerialNum[4];//tstat version			
													if(tstat_version2 >=240 && tstat_version2 <250)
														tstat_version2 /=10;
													else 
													{
														tstat_version2 = SerialNum[5]*256+SerialNum[4];	
														tstat_version2 /=10;
													}//tstat_version
													
													temp.software_version=tstat_version2;
															if(read_one(temp.id,185)==0)
													temp.baudrate=9600;
												else
												{
														temp.baudrate=19200;
												}
													temp.nEPsize=read_one(temp.id,326);
														
													if(temp.serialnumber>0)
													
													m_binary_search_networkcontroller_background_thread.push_back(temp);
												}



											}
											binarySearchforview_networkcontroller(devLo,devHi);
											return;
									}
							}
							else
							{
								return;
							}
						}
				}
			}while(1);
		}
		break;
	case -4:break;
		//no connection 
	case -5:break;
		//the input error
	}
}