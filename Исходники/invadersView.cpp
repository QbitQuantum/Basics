void CinvadersView::OnDraw(CDC* pDC)
{
	CinvadersDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	//drawbackground
	CBitmap bitmap;
	CDC dcMemory;
	if(pDoc->sp.level==1){
		bitmap.LoadBitmapW(IDB_BITMAP1);}
	if(pDoc->sp.level==2){
		bitmap.LoadBitmapW(IDB_BITMAP2);}
	if(pDoc->sp.level==3){
		bitmap.LoadBitmapW(IDB_BITMAP3);}
	if(pDoc->sp.level==4){
		bitmap.LoadBitmapW(IDB_BITMAP4);}
	if(pDoc->sp.level==5){
		bitmap.LoadBitmapW(IDB_BITMAP5);}
	dcMemory.CreateCompatibleDC(pDC);
	dcMemory.SelectObject(bitmap);



	HICON player;
	HICON alien1;
	HICON alien2;
	HICON alien3;
	HICON alien4;
	HICON pRocket;
	HICON aRocket;
	HICON explo;
	player=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	alien1=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON2));
	alien2=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON3));
	alien3=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON4));
	alien4=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON5));
	pRocket=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON6));
	aRocket=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON6));
	explo=LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON7));
	//draw player
	dcMemory.DrawIcon(pDoc->sp.player.left,pDoc->sp.player.top,player);

	//draw rocket
	if(pDoc->sp.pRock==true)dcMemory.DrawIcon(pDoc->sp.pRocket.left,pDoc->sp.pRocket.top,pRocket);
	if(pDoc->sp.aRock==true)dcMemory.DrawIcon(pDoc->sp.aRocket.left,pDoc->sp.aRocket.top,aRocket);

	if(pDoc->sp.exploa==true)dcMemory.DrawIcon(pDoc->sp.pRocket.left,pDoc->sp.pRocket.top,explo);pDoc->sp.exploa=false;
	if(pDoc->sp.explop==true)dcMemory.DrawIcon(pDoc->sp.player.left,pDoc->sp.player.top,explo);pDoc->sp.explop=false;
	//draw invaders
	for(int i=0;i<pDoc->sp.aliens.size();i++){
		if(pDoc->sp.aliens.at(i).i==0){
			dcMemory.DrawIcon(pDoc->sp.aliens.at(i).r.left,pDoc->sp.aliens.at(i).r.top,alien4);}
		if(pDoc->sp.aliens.at(i).i==1){
			dcMemory.DrawIcon(pDoc->sp.aliens.at(i).r.left,pDoc->sp.aliens.at(i).r.top,alien3);}
		if(pDoc->sp.aliens.at(i).i==2){
			dcMemory.DrawIcon(pDoc->sp.aliens.at(i).r.left,pDoc->sp.aliens.at(i).r.top,alien2);}
		if(pDoc->sp.aliens.at(i).i==3){
			dcMemory.DrawIcon(pDoc->sp.aliens.at(i).r.left,pDoc->sp.aliens.at(i).r.top,alien1);}
	}
	//drawscore&level
	dcMemory.TextOutW(200,pDoc->sp.border.bottom-20,pDoc->sp.llvl);
	dcMemory.TextOutW(250,pDoc->sp.border.bottom-20,pDoc->sp.lvl);
	dcMemory.TextOutW(300,pDoc->sp.border.bottom-20,pDoc->sp.lliv);
	dcMemory.TextOutW(350,pDoc->sp.border.bottom-20,pDoc->sp.liv);
	dcMemory.TextOutW(400,pDoc->sp.border.bottom-20,pDoc->sp.str);
	dcMemory.TextOutW(450,pDoc->sp.border.bottom-20,pDoc->sp.scr);
	//drawend
 

	if(pDoc->sp.gameOver==true){
		dcMemory.TextOutW(320,240,pDoc->sp.scr);
	}
	
	pDC->BitBlt(pDoc->sp.border.left,pDoc->sp.border.top,640,480,&dcMemory,0,0,SRCCOPY);	
}