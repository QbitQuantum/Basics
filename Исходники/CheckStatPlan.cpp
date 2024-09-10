void CheckStatPlan::startPlan (PlanItem &oPlan, char ** argv)
{
    m_argv = argv;
    
    StatInterface::m_pPlan = &oPlan;
    
    //##置运行状态
    bool bret = updateState (oPlan.m_iPlanID, "RUN", "<Message> 开始执行...");
    
    if (!bret) {
        Log::log (0,"计划执行失败[Plan_ID=%d],因执行 updateState(RUN) 不成功", oPlan.m_iPlanID);
        return;
    }
    
    while (oPlan.m_iDebugFlag == 1)
        waitDebug (oPlan); //等待调试, 置B_Check_Stat_Plan.DEBUG_FLAG=0 后跳出循环
    
    try {
        //置下一次运行时间
        sleep (1);
        
        setNextRunTime (oPlan);
        
        if (oPlan.m_iAppType == 0)
        {
            switch (atoi (oPlan.m_sStatName))
            {
            
            	///////////////////////HSS数据信息点300000/////////////////////////////////////////
            	case 800001://2.2.1	数据接收平衡（AuditId=0001）
            	{
            		CheckStatInfo oReceBalance;		
            		oReceBalance.checkDataRecvBalance("0001",50,MIDL_FREG);
            		break;
            	}	
            	
            	case 800002://2.2.2	数据加载平衡（AuditId=0002）
            	{
            		CheckStatInfo oReceBalance;
            		oReceBalance.checkDataLoadBalance("0002",50,MIDL_FREG);
            		break;
            	}
            	
            	case 800003://2.2.3	数据入库平衡（AuditId=0003）
            	{
            		CheckStatInfo oReceBalance;
            		oReceBalance.checkDataInputBalance("0003",50,MIDL_FREG);
            		break;
            	}
            	
            	case 800004://2.2.4	数据发布平衡（AuditId=0004）
            	{
            		CheckStatInfo oCheckStatInfo;
            		oCheckStatInfo.checkOutputBalance();
            		break;
            	}
            	
            	case 800005://2.2.5	实例数变更（AuditId=0005）
            	{
            		CheckStatInfo oCheckStatInfo;
            		oCheckStatInfo.checkInstanceUpdate();
            		break;
            	}
            	
            	case 800006://2.2.6	进程日志（AuditId=0006）
            	{
                	CheckStatInfo oCheckHSSStatInfo;
                	oCheckHSSStatInfo.checkHSSAlertLog();            		
            		break;
            	}            	            	            	            	            	            	
            	
            	case 800007://2.2.7	鉴权异常（AuditId=0008）
            	{
            		CheckStatInfo oCheckStatInfo;
            		oCheckStatInfo.checkAuthenticationError();
            		break;
            	}   
            	
            	///////////////////////HSS信息点500000/////////////////////////////////////////
            	//2.3.1 接收接口处理（AuditId=0100）
            	case 502311://	省内非计费域接口（AuditId=0101）	性能指标（AuditId=0101,type=40）
            	{	
            		CheckStatInfo oCheckStatInfo;
            		oCheckStatInfo.checkNoBillingCap();
            		break;
            	}
             	case 502312://		集团HSS接口（AuditId=0102）	性能指标	（AuditId=0102,type = 40）
            	{	
            		CheckStatInfo oCheckStatInfo;
            		oCheckStatInfo.checkHssCap();
            		break;
            	}
            	//2.3.2 同步接口处理（AuditId=0200）
             	case 502321://		OFCS接口（AuditId=0201）	性能指标（AuditId=0201,type=40）
            	{	
            		CheckStatInfo oCheckStatInfo;
            		oCheckStatInfo.checkOfcsCap();
            		break;
            	}
             	case 502322://			OCS接口（AuditId=0202）		性能指标（AuditId=0202,type=40）
            	{	
            		CheckStatInfo oCheckStatInfo;
            		oCheckStatInfo.checkOcsCap();
            		break;
            	}           	      	
            	//2.3.4	系统状态（AuditId=0400）
            	case 502341://2.3.4.1	事件信息点（AuditId=0400,type=60）
            	{
            		CheckStatInfo oCheckHSSEventInfo;
            		oCheckHSSEventInfo.checkOcsCap();
            		break;
            	}	
            	
            	case 502342://2.3.4.2	告警信息点（AuditId=0400,type=20）
            	{
            		CheckStatInfo oCheckHSSSystemCaution;
            		oCheckHSSSystemCaution.checkHSSSystemCaution();
            		break;
            	}
            	         	
            	///////////////////////一下为计费信息点，对HSS无用处//////////////////////
              //数据信息点数据提取
               case 100001:  //##2.2.1	计费接收（AuditId=0001，Type=50）
                {
                	CheckStatInfo oCheckStatInfo(MODULE_CHECK_NORMAL_FILE);
                	oCheckStatInfo.checkNormalFile();
                  break;                	     
                }
               case 100002:  //##2.2.2	计费接收异常文件（AuditId=0002，Type=50）
                {
                	CheckStatInfo oCheckStatInfo(MODULE_CHECK_ERR_FILE);
                  oCheckStatInfo.checkErrFile();
                  break;                	     
                }
               case 100003:  //##2.2.3	预处理平衡（AuditId=0003，Type=50）
                {
                	CheckStatInfo oCheckStatInfo(MODULE_CHECK_FILE_PREP_BALANCE);
                  oCheckStatInfo.checkPrepBalance();
                  break;                	     
                }
               case 100004:  //##2.2.4	批价平衡（AuditId=0004，Type=50）
                {
                	CheckStatInfo oCheckStatInfo(MODULE_CHECK_FILE_PRICING_BALANCE);
                  oCheckStatInfo.checkPricingBalance();
                  break;                	     
                }
               case 100005:  //##2.2.5	入库平衡（AuditId=0005，Type=50）
                {
                	CheckStatInfo oCheckStatInfo(MODULE_CHECK_FILE_INSTORE_BALANCE);
                  oCheckStatInfo.checkInStoreBalance();
                  break;                	     
                }
               case 100006:  //##2.2.6	话单日志（AuditId=0006，Type=50）
                {
                	CheckStatInfo oCheckStatInfo;
                  oCheckStatInfo.checkTicketLog();
                  break;                	     
                }
               case 100007:  //##2.2.7	IDEP文件传输（AuditId=0007，Type=50）
                {
                	CheckStatInfo oCheckStatInfo;
                  oCheckStatInfo.checkTransLog();
                  break;                	     
                }
               case 100008:  //##2.2.8	累帐平衡（AuditId=0008，Type=50）
                {
                  //CheckDailyAcctItemAggr oCheckItem;
                  //oCheckItem.checkDailyAcctItemAggrNew();
                  break;                	     
                }                                                                                                                
                   
               case 100009:  //##2.2.9	日帐日志（AuditId=0009，Type=50）
                {
                 
                  break;                	     
                }
               case 100010:  //##2.2.10	月帐日志（AuditId=0010，Type=50）
                {
                  //CheckDailyAcctItemAggr oCheckItem;
                  //oCheckItem.checkMonthAcctItemAggrNew();                	
                  break;                	     
                }
               case 100011:  //##2.2.11	高额签到（AuditId=0011，Type=50）
                {
                	//CheckStatInfo oCheckStatInfo;
                 // oCheckStatInfo.checkSignHighFee();
                  break;                	     
                }
               case 100012:  //##2.2.12	省级高额（AuditId=0012，Type=50）
                {
                	//CheckStatInfo oCheckStatInfo;
                	//oCheckStatInfo.checkHighFeeServ();
                	/*
                	char sValue1[3+1]={0};
                	ParamDefineMgr::getParam("HIGH_FEE_ALARM", "LOG_OR_DB", sValue1);
                	int iValue=atoi(sValue1);
                	if(iValue >= 2)
                     oCheckStatInfo.checkHighFeeServ();
                  else 
                     oCheckStatInfo.checkHighFeeLog();
                   */
                  break;                	     
                }
               case 100013:  //##2.2.13	进程日志（AuditId=0013，Type=50）
                {
                	CheckStatInfo oCheckStatInfo;
                	oCheckStatInfo.checkAlertLog();
                	/*
                	char sValue1[3+1]={0};
                	ParamDefineMgr::getParam("INFO_DATA", "PROCESSLOG", sValue1);
                	int iValue=atoi(sValue1);
                	if(iValue == 1)                	
                    oCheckStatInfo.checkAlertLog();
                   else 
                    oCheckStatInfo.checkProcessLog();
                    */
                  break;                	     
                }
               case 100014:  //##2.2.14	计费处理话单延迟（AuditId=0014，Type=50）
                {
                	CheckStatInfo oCheckStatInfo(MODULE_CHECK_DELAY_FILE);
                  oCheckStatInfo.checkDelayFile();
                  break;                	     
                }
               case 100015:  //##2.2.15	模块处理性能指标（AuditId=0015，Type=50）
                {
                	CheckStatInfo oCheckStatInfo;
                	oCheckStatInfo.prepMouldeCapability();
                	oCheckStatInfo.pricingMouldeCapability();
                  oCheckStatInfo.checkMouldeCapabilityKpi();
                  break;                	     
                }
               case 100016:  //##2.2.16	系统处理损耗指标（AuditId=0016，Type=50）
                {
                	CheckStatInfo oCheckStatInfo;
                  oCheckStatInfo.checkSystemLossKpi()	;		
                  break;                	     
                }
                
                case 100017:  //##JS_20101215_001（AuditId=0060  Type=50）
                {
                	CheckStatInfo oCheckStatInfo;
                  oCheckStatInfo.checkDayAcctFee();		
                  break;                	     
                }
 
            // 信息点数据提取
            // 20000x 性能指标信息点
                case 200001:  //2.3.1.1	计费接收性能指标（AuditId=0100，Type=40）
                {
                	Information oCheckInfor;
                  oCheckInfor.checkGather()	;		
                  break;                	     
                }  
                case 200002:  //2.3.2.1.1	预处理性能指标（AuditId=0201，Type=40）
                {
                	Information oCheckInfor;
                	//oCheckInfor.checkBalance(MODULE_PREP);  //预处理告警中间数据生成
                  oCheckInfor.checkPerp()	;		
                  break;                	     
                }   
                case 200003:  //2.3.2.2.1	批价性能指标（AuditId=0202，Type=40）
                {
                	Information oCheckInfor;
                	//oCheckInfor.checkBalance(MODULE_PRICING) ;//批价告警中间数据生成  
                  oCheckInfor.checkPricing()	;		
                  break;                	     
                }   
                case 200004:  //2.3.2.3.1	入库性能指标（AuditId=0203，Type=40）
                {
                	Information oCheckInfor;
                	//oCheckInfor.checkBalance(MODULE_INSTORE) ;//入库告警中间数据生成
                  oCheckInfor.checkIndb()	;		
                  break;                	     
                }   
                case 200005:  //2.3.3.1.1	销账性能指标（AuditId=0301，Type=40）
                {
	                CheckStatInfo oCheckAddItem ;
                  oCheckAddItem.checkAcctCap("0301",40,MIDL_FREG)	;
                  break;                	     
                }
                case 200006:  //2.3.3.2.1	累帐性能指标（AuditId=0302，Type=40）
                {
                	CheckStatInfo oCheckAddItem ;
                  oCheckAddItem.checkAddItem()	;		
                  break;                	     
                }  
                case 200007:  //2.3.3.4.1	月帐性能指标（AuditId=0304，Type=40）
                {
                	CheckStatInfo oCheckMonthCap ;
                  oCheckMonthCap.checkMonthCap()	;		
                  break;                	     
                }     
                 
                case 200008:  //2.3.4.1.1	银行性能指标（AuditId=0401，Type=40）
                {
	                CheckStatInfo oCheckAddItem ;
                  oCheckAddItem.checkAcctCap("0401",40,MIDL_FREG)	;
                  break;                	     
                }
                case 200009:  //2.3.4.2.1	充值卡性能指标（AuditId=0402，Type=40）
                {
	                CheckStatInfo oCheckAddItem ;
                  oCheckAddItem.checkAcctCap("0402",40,MIDL_FREG)	;
                  break;                	     
                }      
                 case 200010:  //.3.3.5.1 欠费账龄性能指标（AuditId=0305，Type=40）
                {
                CheckStatInfo oCheckAddItem ;
                  oCheckAddItem.checkAcctCap("0305",40,HIGH_FREG) ;
                  break;                      
                } 
                                                                                          
               //20001x  告警指标信息点
               case 200012:  //2.3.2.1.2       ?
                {
                  Information oCheckInfor;
                  //oCheckInfor.checkBalance(MODULE_PREP);  //?¤′|àí???ˉ?D??êy?Yéú3é
                  oCheckInfor.checkPrepAlarm();
                  oCheckInfor.writePrepAlarm()  ;
                  break;
                }
                case 200013:  //2.3.2.2.2       
                {
                  Information oCheckInfor;
                  //oCheckInfor.checkBalance(MODULE_PRICING) ;//?ú?????ˉ?D??êy?Yéú3é
                  oCheckInfor.checkPricingAlarm();
                  oCheckInfor.writePricingAlarm()       ;
                  break;
                }
                case 200014:  //2.3.2.3.2      
                {
                  Information oCheckInfor;
                  //oCheckInfor.checkBalance(MODULE_INSTORE) ;//è??a???ˉ?D??êy?Yéú3é
                  oCheckInfor.checkIndbAlarm()    ;
                  oCheckInfor.writeIndbAlarm()  ;
                  break;
                }        
                
                case 200015:  //2.3.3.2.2	累帐告警指标（AuditId=0302，Type=20）
                {
                	CheckStatInfo oCheckInfor;
                  oCheckInfor.checkAddItemCaution()	;		
                  break;                	     
                }         
                        
                case 200020:  //2.3.3.5.2 欠费账龄告警指标（AuditId=0305，Type=20
                {
                CheckStatInfo oCheckAddItem ;
                  oCheckAddItem.checkAcctCaution("0305",20,HIGH_FREG) ;
                  break;                      
                } 
                /* 核心参数告警信息点*/
                case 300001:  //检查每日话单参数,话单总数，总时长，总流量
                {
                	CheckStatInfo oCheckInfo;
                  oCheckInfo.checkParamBalance()	;		
                  break;                	     
                }  
                
                case 300002:  //检查每日漫入漫出用户数
                {
                	CheckStatInfo oCheckInfo;
                  oCheckInfo.checkRoamServs()	;		
                  break;                	     
                }   
               /*
                case 400001:  //2.3.5.1	事件信息点（AuditId=0900，Type=60）
                {
                	CheckStatInfo checkEventInfo;
                  checkEventInfo.checkEventInfo()	;		
                  break;                	     
                }    
                */
    
                case 400002:  //2.3.4.3.1	产品配置指标（AuditId=0403，Type=30）
                {
                	Information checkInfo;
                  checkInfo.checkAllProductInfo()	;		
                  break;                	     
                }   
                case 400003:  //2.3.4.4.1	商品配置指标（AuditId=0404，Type=30）
                {
                	Information checkInfo;
                	  checkInfo.checkAllProductOfferInfo()	;		
                 	 break;                	     
                }  
                case 400004:  //2.3.4.5.1	定价计划配置指标（AuditId=0405，Type=30）
                {
                	Information checkInfo;
                  	checkInfo.checkAllPricingPlanInfo()	;		
                  break;                	     
                }  
                
                case 900001:  //2.3.5.1	系统状态性能指标（AuditId=0900，Type=40）
                {
	                CheckStatInfo oCheckAddItem ;
                  oCheckAddItem.checkAcctCap("0900",40,MIDL_FREG)	;
                  break;                	     
                }    
                               
                case 900002:  //2.3.5.2	系统状态事件信息点（AuditId=0900，Type=60）
                {
                	CheckStatInfo checkEventInfo;
                  checkEventInfo.checkHSSEventInfo()	;		
                  break;                	     
                }  
                
                case 900003:  //	2.3.5.3	告警信息点（AuditId=0900，Type=20）
                {
                	CheckStatInfo checkEventInfo;
                  	checkEventInfo.checkSystemCaution()	;		
                  break;                	     
                }
                case 900004 ://    2.3.5.4 VC接口性能指标 (AuditId=0203，Type=40)
                {
               		CheckStatInfo oCheckVCinter ;
                	oCheckVCinter.checkVCCable("0203",40,MIDL_FREG)	;
                	break;
                	
            	}
            	case 900005 ://    2.3.5.5 查询接口性能 (AuditId=0300，Type=40)
                {
               		CheckStatInfo oCheckSeekInter ;
                 	oCheckSeekInter.checkSeekInterCap("0300",40,MIDL_FREG);
                 	break;
                	
            	}
            	case 900006 ://    2.3.5.5 查询接口告警 (AuditId=0300，Type=20)
                {
               		CheckStatInfo oCheckSeekInter ;
                 	oCheckSeekInter.checkSeekInterAlarm("0300",20,MIDL_FREG); 
                 	break;            	
            	}
                                                                                                                                                                                                                                                                                                                                                                  
               default:
                {   //## 置未知统计项ID 错误
                   updateState (oPlan.m_iPlanID, "NUL", "<Error> 未知统计项(stat_name),解析错误", true);
                   return;
                }
            }
        }
        else if (oPlan.m_iAppType == 1) //## PLSQL块执行
        {
            DEFINE_QUERY (qry);
            char sql[4096];
            sprintf (sql,"%s", oPlan.m_sStatName);
            qry.setSQL (sql);
            qry.execute();
            qry.commit ();
        }
        else { //## 未知应用类型(app_type)
            updateState (oPlan.m_iPlanID, "NUL", "<Error> 未知应用类型(app_type),解析错误", true);
            return;
        }
    }
    catch (TOCIException &e)
    {
        DB_LINK->rollback ();
        char sMsg[2048];
        sprintf (sMsg, "<Error> %s \n %s", e.getErrMsg(), e.getErrSrc());
        updateState (oPlan.m_iPlanID, "ERR", sMsg, true);
        return;
    }
    //# TException
    catch (TException &e) 
    {
        DB_LINK->rollback ();
        char sMsg[2048];
        sprintf (sMsg, "<Error> %s ", e.GetErrMsg());
        updateState (oPlan.m_iPlanID, "ERR", sMsg, true);
        return;
    }
    catch (Exception &e) 
    {
        DB_LINK->rollback ();
        char sMsg[2048];
        sprintf (sMsg, "<Error> %s \n", e.descript());
        updateState (oPlan.m_iPlanID, "ERR", sMsg, true);
        return;
    }
    //# Other Exception
    catch (...) 
    {
        DB_LINK->rollback ();
        char sMsg[2048];
        sprintf (sMsg, "<Error> 程序异常退出！ \n");
        updateState (oPlan.m_iPlanID, "ERR", sMsg, true);
        return;
    }
        
    updateState (oPlan.m_iPlanID, "END", "<Message> 执行成功!", true);
}