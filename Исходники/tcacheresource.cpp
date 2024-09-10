//! Clears the complex on the specified region. Please observe that the actually cleared region
//! consists of all lattice cells intersecting the passed region, therefore resulting in a cleared region
//! typically larger than passed one, up to the lattice granularity.
void TCacheResource::clear(QRegion region)
{
	if (!m_region.intersects(region))
		return;

	//Get the region bbox
	TRect bbox(toTRect(region.boundingRect()));

	//For all cells intersecting the bbox
	TPoint initialPos(getCellPos(bbox.getP00()));
	TPoint pos;
	for (pos.x = initialPos.x; pos.x <= bbox.x1; pos.x += latticeStep)
		for (pos.y = initialPos.y; pos.y <= bbox.y1; pos.y += latticeStep) {
			QRect cellQRect(toQRect(TRect(pos, TDimension(latticeStep, latticeStep))));

			if (region.intersects(cellQRect) && m_region.intersects(cellQRect)) {
				//Release the associated cell from cache and clear the cell from the content region.
				TImageCache::instance()->remove(getCellCacheId(pos));
				m_region -= cellQRect;

				--m_cellsCount;

				//DIAGNOSTICS_GLOADD("crCellsCnt", -1);

				//Release the cell from m_cellDatas
				m_cellDatas[getCellIndex(pos)].m_modified = true;
			}
		}

	if (m_region.isEmpty()) {
		m_tileType = NONE;
		m_locksCount = 0;
	}
}