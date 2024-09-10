//重画函数
void CCardControl::OnPaint()
{
	CPaintDC dc(this);

	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//加载位图
	CImage ImageBuffer;
	CImageHandle HandleCard(&m_ImageCard);
	CImageHandle HandleFundus(&m_ImageBack);
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),16);
	if (ImageBuffer.IsNull()==true) return;

	//绘画扑克													                                              
	CDC * pBufferDC=CDC::FromHandle(ImageBuffer.GetDC());

     if(bDrawCard)																	               //add
     {																							   //add
	     for (int i=0;i<m_CardDataArray.GetCount();i++)				   				     
	     {
		   
			 BYTE bCardData=m_CardDataArray[i];
			 m_ImageCard.AlphaDrawImage(pBufferDC,i*CARD_SPACE,0,CARD_WIDTH,CARD_HEIGHT,GetCardXPos(bCardData),GetCardYPos(bCardData),RGB(255,0,255)); //非常好的画图函数
	     }
		    
	 }
    /////////////////////////////////////////////////////////////////////////////////////////begin add
     else																			
     {
		 
	    for(int i=0;i<m_CardDataArray.GetCount();i++)
	    {
			m_ImageBack.AlphaDrawImage(pBufferDC,i*CARD_SPACE,0,CARD_WIDTH,CARD_HEIGHT,3*CARD_WIDTH,4*CARD_HEIGHT,RGB(255,0,255));     //画扑克背面
		}
	 }
    ///////////////////////////////////////////////////////////////////////////////////////////end add
	ImageBuffer.ReleaseDC();
	ImageBuffer.BitBlt(dc,0,0);

	//清理资源
	ImageBuffer.Destroy();

   	return;
}