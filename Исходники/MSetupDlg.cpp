void CMSetupDlg::ThreadFunc()
{
	
	int iCount	=	0;
	while(!m_pClient->IsConnected()){
		if(m_pClient!=NULL){
			Air::Common::NetClient::Info	info;
			info.pListener	=	this;
			info.strIP		=	"10.240.38.103";
			info.usPort		=	54322;
			if(m_pLog!=NULL){
				m_pLog->InsertString(0,L"连接服务器中");
			}
			if(m_pClient->Connect(info)){
				if(m_pLog!=NULL){
					m_pLog->InsertString(0,L"连接服务器成功");
					m_pLog->InsertString(0,L"开始下载裸客户端");
				}
				enNetType	t=	enNT_FS_Hello;
				m_pClient->Send(&t,sizeof(t));
			}
		}
		Sleep(1000);
	}
	SYSTEMTIME startTime;
	GetLocalTime(&startTime);
	CProgressCtrl* pMain	=	(CProgressCtrl*)GetDlgItem(IDC_PROGRESS_MAIN);
	CProgressCtrl* pSub		=	(CProgressCtrl*)GetDlgItem(IDC_PROGRESS_SUB);

	U32			begin=timeGetTime();
	//SetEvent(m_Event);
	//下载客户端
	while(1){
		if(m_pNakedClinet==NULL){
			break;
		}else{
			U32		end		=	timeGetTime();
			U32	usedTime	=	(end	-	begin)*0.001f;
			U32	usedHour	=	usedTime/3600;
			U32	usedMin		=	(usedTime%3600)/60;
			U32	usedSec		=	(usedTime%3600)%60;

			

			wchar_t strTime[1024];
			if(m_Complated==0){
				swprintf_s(strTime,L"0/2 已使用%02d:%02d:%02d 剩余??:??:??",usedHour,usedMin,usedSec);
			}else{
				double	needTime	=	usedTime*((double)m_Total/(double)m_Complated) - usedTime;
				U32	uiNeedTime		=	needTime;
				U32	needHour		=	uiNeedTime/3600;
				U32	needMin			=	(uiNeedTime%3600)/60;
				U32	needSec			=	(uiNeedTime%3600)%60;
				swprintf_s(strTime,L"0/2 已使用%02d:%02d:%02d 剩余%02d:%02d:%02d",usedHour,usedMin,usedSec,needHour,needMin,needSec);
			}
			//float	f	=	m_Complated
			GetDlgItem(IDC_STATIC_TIME)->SetWindowTextW(strTime);

			CProgressCtrl* pSub	=	(CProgressCtrl*)GetDlgItem(IDC_PROGRESS_SUB);
			float	fPercent	=	100*(float)m_Complated/(float)m_Total;
			pSub->SetPos((U32)fPercent);
		}
		Sleep(100);
	}
	pSub->SetPos(100);
	pMain->SetPos(25);


	//下载客户端
}