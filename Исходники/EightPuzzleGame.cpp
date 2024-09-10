VOID CEightPuzzleGame::PaintBegStatus ( CClientDC* pdc )
{
	CDC		MemoryDC, TempDC ;
	MemoryDC.CreateCompatibleDC ( pdc ) ;
	TempDC.CreateCompatibleDC ( pdc ) ;
	TempDC.SelectObject ( &this->DigitBmp ) ;

	CBitmap BegBmp ;
	BegBmp.CreateCompatibleBitmap ( pdc, DEF_BMP_SIZE * 3, DEF_BMP_SIZE * 3 ) ;

	// 绘制初始状态图
	MemoryDC.SelectObject ( &BegBmp ) ;	
	for ( int i = 0; i < 3; i++ )
	{
		for ( int j = 0; j < 3; j++ )
		{
			MemoryDC.StretchBlt ( DEF_BMP_SIZE*j, DEF_BMP_SIZE*i, DEF_BMP_SIZE, DEF_BMP_SIZE, \
				&TempDC, DEF_BMP_SIZE*this->bBegMetrix[i][j], 0, DEF_BMP_SIZE, DEF_BMP_SIZE, SRCCOPY ) ;
		}
	}
	pdc->BitBlt ( 240, 25, DEF_BMP_SIZE*3, DEF_BMP_SIZE*3, &MemoryDC, 0, 0, SRCCOPY ) ;

	TempDC.DeleteDC () ;
	MemoryDC.DeleteDC() ;
	BegBmp.DeleteObject() ;
}