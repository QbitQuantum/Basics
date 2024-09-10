BOOL MyTreeView::removeItem(HTREEITEM elem){
	if ( elem ){
		//rimuovo l'icona
		TVITEM item;
		item.hItem = elem;
		item.mask = TVIF_IMAGE;
		if ( SendMessage(this->hWnd,TVM_GETITEM,0,(LPARAM)&item) ){
			//rimuovo l'immagine se c'è
			ImageList_Replace(this->imgList,item.iImage,NULL,NULL);
			return SendMessage(this->hWnd,TVM_DELETEITEM,0,(LPARAM)elem);
		}
	}
	return FALSE;
}