/**
* \author	Paul Henderson (PH, PTJK76)
* \date		August 2006 - Initial Creation, PH
*/
BOOL CALLBACK CSignature::SigProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	
	P_COORDXY		pPoint;
	CSignature		*pObj;
	HDC				hdc;
	PAINTSTRUCT		ps;
	static			bool bOffScreen;

	switch(message)
	{
	
	case WM_LBUTTONDOWN:
		//grab a pointer to the object members
		pObj = (CSignature *)GetWindowLong(hWnd, GWL_USERDATA);
		if(LOWORD(lParam) && HIWORD(lParam) ){
			pObj->m_pPrevPos = pObj->AddCoord(LOWORD(lParam),HIWORD(lParam),true);// the 'true' depicts a start line
			pObj->m_pCurrentVector = pObj->m_pCurrentPos;
		}
		pObj->m_bSigning = TRUE;
		break;
	
	case WM_LBUTTONUP:
		pObj = (CSignature *)GetWindowLong(hWnd, GWL_USERDATA);
		//  Allows signature capture to save the vectors and send them using 'VectorNavigate' 
		pObj->SendVectors();
		pObj->m_bSigning = FALSE;
		break;
		
	case WM_MOUSEOUT:
		pObj = (CSignature *)GetWindowLong(hWnd, GWL_USERDATA);
		//  Only send vectors if we are still signing otherwise we send the 
		//  last recorded vectors whenever the user clicks outside the Window.
		if (pObj->m_bSigning)
		{
			pObj->m_bSigning = FALSE;
			pObj->SendVectors();
		}
		break;

	case WM_MOUSEMOVE:
		pObj = (CSignature *)GetWindowLong(hWnd, GWL_USERDATA);
		if(pObj->m_bSigning == FALSE){ //if we went offscreen
			pObj->m_pPrevPos = pObj->AddCoord(LOWORD(lParam),HIWORD(lParam),true);// the 'true' depicts a start line
			pObj->m_bSigning = TRUE;
		}
		
		//otherwise it is a valid onscreen coordinate
		pPoint = pObj->AddCoord(LOWORD(lParam),HIWORD(lParam),pObj->m_bNewLine);
		
		//check to make sure that we have a line to draw
		if(pPoint == NULL || pObj->m_pPrevPos == NULL)
			break;
		
		if(pPoint->bNewLine)
		{
			pObj->m_pPrevPos = 	pPoint;
			break;
		}

		//Draw the line
		hdc = GetDC(hWnd);
		//select the correct coloured pen
		SelectObject(hdc,CreatePen(PS_SOLID,pObj->m_iLineWidth,pObj->m_crLineColor));
				
		MoveToEx(hdc,pObj->m_pPrevPos->XPos,pObj->m_pPrevPos->YPos,NULL);
		LineTo(hdc,LOWORD(lParam),HIWORD(lParam));
		DeleteObject(SelectObject(hdc,GetStockObject(BLACK_PEN)));
		ReleaseDC(hWnd,hdc);
		pObj->m_pPrevPos = pPoint;
		break;	
			
	case WM_PAINT:
		pObj = (CSignature *)GetWindowLong(hWnd, GWL_USERDATA);
		hdc = BeginPaint(hWnd,&ps);
		pObj->RePaintBox(hdc,TRUE);// second param paint background
		EndPaint(hWnd, &ps);
		break;
	
	case WM_DESTROY:
		pObj = (CSignature *)GetWindowLong(hWnd, GWL_USERDATA);
		pObj->DeleteSigMem();
		break;
	
	 default:
		return DefWindowProc(hWnd,message, wParam, lParam);
		
  }
	return TRUE;
}