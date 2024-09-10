static void Main_OnMouseMove(HWND hwndParent, HWND hwndTV, LONG xCur, LONG yCur) 
{ 
    HTREEITEM htiTarget;  // handle to target item 
    TVHITTESTINFO tvht;  // hit test information 
    //POINT Pos;
	INT iIndex;
	struct OBJ *poj;

	// xCur,yCur sono della parent
    // Drag the item to the current position of the mouse cursor. 
    // Muove l'immagine del Drag nella posizione del cursore
    iIndex=TVFind(TV_FINDHWND,hwndTV);
	poj=TVList[iIndex].lpObj;
	xCur-=poj->px; yCur-=poj->py;
	//GetCursorPos(&Pos);
	//ImageList_DragMove(Pos.x,Pos.y); 
	ImageList_DragMove(xCur+12,yCur+12); 
        
	// Find out if the cursor is on the item. If it is, highlight 
    // the item as a drop target. 
	ZeroFill(tvht);
	tvht.pt.x=xCur; tvht.pt.y=yCur; 
	tvht.flags=TVHT_ONITEM|TVHT_ONITEMLABEL;
    if ((hDropItem = htiTarget = TreeView_HitTest(hwndTV, &tvht)) != NULL) 
	{ 
		ImageList_DragShowNolock(FALSE);
		TreeView_SelectDropTarget(hwndTV, htiTarget); 
		//hDropItem=htiTarget;
		ImageList_DragShowNolock(TRUE);
    }  
    return; 
} 