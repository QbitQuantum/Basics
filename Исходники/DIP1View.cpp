/*
功能：
	图像向下显示特效
*/
void CDIP1View::OnToDownScan() 
{
	// TODO: Add your command handler code here
	if(alert(1))
		return;
	//******************************刷新屏幕******************************
	CDC *pDC = GetDC();
	CRect rect;
	GetWindowRect(&rect);
	CBrush brush(RGB(255,255,255));//用白色填充屏幕
	pDC->FillRect(&rect,&brush);
	//******************************刷新屏幕******************************
	CDIP1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_dib.IsValid())//判断是否成功加载位图
	{
		//获取图像的宽和高
		int SWidth = m_dib.GetShowWidth();
		int topLeftX = (rect.Width()-m_dib.GetWidth())/2;//图像显示位置左上角X坐标
		int topLeftY = (rect.Height()-m_dib.GetHeight())/2;//图像显示位置左上角Y坐标
		//显示图像
		m_dib.ToDownScan(pDC,CPoint(topLeftX,topLeftY),CSize(SWidth,1));
	}
	//刷新屏幕
	Invalidate(1);
}