void CBrowserMusicWindow::InitMusicInterface(CGraphic& aGraphic) const
{
	//播放界面
	//播放界面主框
	TPoint nX;
	
	nX.iX=(iMainEngine.ScreenSize().iWidth-iMusicMainImage->SizeInPixels().iWidth)/2;

	nX.iY=iMainEngine.ScreenLayout().GetControlPaneRect().iTl.iY-iMusicMainImage->SizeInPixels().iHeight-2;

	aGraphic.BitBlt(nX,iMusicMainImage);

	//播放进度条
	nX.iY=nX.iY+iMainEngine.ScreenLayout().FontHeight()+iMainEngine.ScreenLayout().FontHeight()/3;
	
	nX.iX=(iMusicMainImage->SizeInPixels().iWidth-iMainEngine.GetBitmapFactory().GetMusicTimeIconBmpSize().iWidth)/2;

	iMainEngine.GetBitmapFactory().DrawMusicTimeIconBmpByID(aGraphic,nX,1);

	TRect nPlayPercent;

	const CFbsBitmap* nMusicPlayPercent = NULL;
	const CFbsBitmap* nMusicPlayPercentMask = NULL;

	nMusicPlayPercent=iMainEngine.GetBitmapFactory().GetMusicTimeIcon(0);
	nMusicPlayPercentMask=iMainEngine.GetBitmapFactory().GetMusicTimeIconMask(0);

	nPlayPercent.iTl=TPoint(0,0);
	nPlayPercent.iBr.iY=nMusicPlayPercent->SizeInPixels().iHeight;
	nPlayPercent.iBr.iX=nMusicPlayPercent->SizeInPixels().iWidth*iPercent/100;
	
	aGraphic.BitBltMasked(nX,nMusicPlayPercent,nMusicPlayPercentMask,nPlayPercent);
	/*aGraphic.BitBlt(nX,nMusicPlayPercent,nPlayPercent);*/

	//显示播放时间
	TPoint nTime;

	nTime=nX;
	nTime.iX=nTime.iX+iMainEngine.ScreenLayout().FontHeight()/2;
	nTime.iY=nTime.iY-iMainEngine.ScreenLayout().FontHeight()*5/4;

	aGraphic.SetPenColor(TRgb(255,255,255));
	aGraphic.SetPenStyle(CFbsBitGc::ESolidPen);
	aGraphic.DrawText(nTime,iCurrentTime);

	nTime.iX=nX.iX+iMainEngine.GetBitmapFactory().GetMusicTimeIconBmpSize(0).iWidth-iMainEngine.ScreenLayout().Font()->TextWidthInPixels(iTotalTime)-iMainEngine.ScreenLayout().FontHeight()/2;
	aGraphic.DrawText(nTime,iTotalTime);

	//播放、上一首、下一首按钮
	TPoint nNum;

	nX.iY=nX.iY+iMainEngine.ScreenLayout().FontHeight();

	iMainEngine.GetBitmapFactory().DrawMusicSelectIconBmpByID(aGraphic,nX,0);
	
	nNum=nX;
	nNum.iX=nNum.iX+iMainEngine.GetBitmapFactory().GetMusicSelectIconBmpSize(0).iWidth;
	nNum.iY=nNum.iY+iMainEngine.GetBitmapFactory().GetMusicSelectIconBmpSize(0).iHeight/2-2;
	aGraphic.DrawText(nNum,_L("4"));

	nX.iY=nX.iY-iMainEngine.ScreenLayout().FontHeight()/4;
	nX.iX=nX.iX+iMainEngine.GetBitmapFactory().GetMusicSelectIconBmpSize(0).iWidth+iMainEngine.ScreenLayout().FontHeight();

	if (iMainEngine.MusicPlayManageEngine().GetIsPlay()==1)
	{
		iMainEngine.GetBitmapFactory().DrawMusicPlayIconBmpByID(aGraphic,nX,2);
	} 
	else
	{
		iMainEngine.GetBitmapFactory().DrawMusicPlayIconBmpByID(aGraphic,nX,0);
	}
	
	nNum.iX=nX.iX+iMainEngine.GetBitmapFactory().GetMusicPlayIconBmpSize(0).iWidth;

	aGraphic.DrawText(nNum,_L("0"));

	nX.iY=nX.iY+iMainEngine.ScreenLayout().FontHeight()/4;
	nX.iX=nX.iX+iMainEngine.GetBitmapFactory().GetMusicPlayIconBmpSize(0).iWidth+iMainEngine.ScreenLayout().FontHeight();

	iMainEngine.GetBitmapFactory().DrawMusicSelectIconBmpByID(aGraphic,nX,2);

	nNum.iX=nX.iX+iMainEngine.GetBitmapFactory().GetMusicSelectIconBmpSize(2).iWidth;
	aGraphic.DrawText(nNum,_L("6"));

	//静音提示
	nX.iX=nX.iX+iMainEngine.GetBitmapFactory().GetMusicSelectIconBmpSize(2).iWidth+iMainEngine.ScreenLayout().FontHeight()*2;
	nX.iY=nX.iY+iMainEngine.ScreenLayout().FontHeight()/4;

	if(iMainEngine.MusicPlayManageEngine().GetIsSlice())
	{
		iMainEngine.GetBitmapFactory().DrawMusicBugleIconBmpByID(aGraphic,nX,1);
	}
	else
	{
		iMainEngine.GetBitmapFactory().DrawMusicBugleIconBmpByID(aGraphic,nX,0);
	}

	//音量大小
	nX.iX=nX.iX+iMainEngine.GetBitmapFactory().GetMusicBugleIconBmpSize(0).iWidth+iMainEngine.ScreenLayout().FontHeight()/2;
	nX.iY=nX.iY-iMainEngine.ScreenLayout().FontHeight()/4;
	
	TRect nVoiceRect;

	nVoiceRect.iTl=TPoint(0,0);
	nVoiceRect.iBr.iY=iMusicVoiceImage->SizeInPixels().iHeight;

	if (iMainEngine.MusicPlayManageEngine().GetMaxVoice()==0)
	{
		nVoiceRect.iBr.iX=iMusicVoiceImage->SizeInPixels().iWidth/2;
	}
	else
	{
		nVoiceRect.iBr.iX=iMusicVoiceImage->SizeInPixels().iWidth*iMainEngine.MusicPlayManageEngine().GetCurVoice()/iMainEngine.MusicPlayManageEngine().GetMaxVoice();
	}

	aGraphic.BitBlt(nX,iMusicVoiceImage,nVoiceRect);
}