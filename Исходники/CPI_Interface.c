void IF_PaintWindow(CPs_InterfaceWindowState* pState, CPs_DrawContext* pContext)
{
	// Walk through list drawing and adding to the valid rects list
	CPs_InterfacePart* pSubPart_Cursor;
	
	for (pSubPart_Cursor = pState->m_pFirstSubPart; pSubPart_Cursor; pSubPart_Cursor = (CPs_InterfacePart*)pSubPart_Cursor->m_hNext)
	{
		if (pSubPart_Cursor->Draw)
		{
			pSubPart_Cursor->Draw(pSubPart_Cursor, pContext);
			ExcludeClipRect(pContext->m_dcDraw,
							pSubPart_Cursor->m_rLocation.left, pSubPart_Cursor->m_rLocation.top,
							pSubPart_Cursor->m_rLocation.right, pSubPart_Cursor->m_rLocation.bottom);
		}
	}
	
	// Perform callback
	
	if (pState->m_hndlr_onDraw)
		pState->m_hndlr_onDraw(pState, pContext);
}