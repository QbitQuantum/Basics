int OnIconLibIconChanged(WPARAM wParam,LPARAM lParam)
{
	HICON hicon;
				hicon=LoadIconFromExternalFile("clisticons.dll",0,TRUE,FALSE,"Email","Contact List",Translate("Email Icon"),-IDI_EMAIL);
				ExtraImageIconsIndex[0]=ImageList_ReplaceIcon(hExtraImageList,ExtraImageIconsIndex[0],hicon );		

				hicon=LoadIconFromExternalFile("clisticons.dll",1,TRUE,FALSE,"Sms","Contact List",Translate("Sms Icon"),-IDI_SMS);
				ExtraImageIconsIndex[1]=ImageList_ReplaceIcon(hExtraImageList,ExtraImageIconsIndex[1],hicon );		

				hicon=LoadIconFromExternalFile("clisticons.dll",4,TRUE,FALSE,"Web","Contact List",Translate("Web Icon"),-IDI_GLOBUS);
				ExtraImageIconsIndex[2]=ImageList_ReplaceIcon(hExtraImageList,ExtraImageIconsIndex[2],hicon );		
				
				LoadClientIcons();
				
				CListIconsChanged(wParam,lParam);
				CluiIconsChanged(wParam,lParam);
				ClcIconsChanged(wParam,lParam);
				NotifyEventHooks(ME_SKIN_ICONSCHANGED,0,0);
				return 0;
};