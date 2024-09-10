void SceneMgr::loadBlockInfo(xs::Point& ptLeftTop, int nIndex, int nTileRow, int nTileCol)
{
	int row = nTileRow;
	int col = nTileCol;
	if (ptLeftTop.x + GRID_WIDTH > m_nMapWidth)
		nTileCol = Ceil(m_nMapWidth - ptLeftTop.x, 32);
	if (ptLeftTop.y + GRID_HEIGHT > m_nMapHeight)
		nTileRow = Ceil(m_nMapHeight - ptLeftTop.y, 32);
	initBlockInfo(ptLeftTop, nTileRow, nTileCol,row,col);
	m_pStream->seek(m_pMapTable[nIndex]);
	xs::Point ptTileLeftTop;
	m_SceneCo.pixel2Tile(ptLeftTop, ptTileLeftTop);
	_LoadBlock(m_pStream, ptTileLeftTop, nTileRow, nTileCol, m_pItemCF);
	m_pStream->seekToBegin();
}