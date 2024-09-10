void UniformGrid::refine(KdTree * tree)
{    
	int level1;
	float hh;
    Vector3F sample, subs;
	int u;
	unsigned k;
	BoundingBox box;
	m_cellsToRefine->begin();
	while (!m_cellsToRefine->end()) {
		sdb::CellValue * parentCell = m_cellsToRefine->value();
		if(parentCell->visited > 0) {
        
			k = m_cellsToRefine->key();
			
			level1 = parentCell->level + 1;
			hh = cellSizeAtLevel(level1) * .5f;
			sample = cellCenter(k);
			removeCell(k);
			for(u = 0; u < 8; u++) {
				subs = sample + Vector3F(hh * Cell8ChildOffset[u][0], 
				hh * Cell8ChildOffset[u][1], 
				hh * Cell8ChildOffset[u][2]);
				box.setMin(subs.x - hh, subs.y - hh, subs.z - hh);
                box.setMax(subs.x + hh, subs.y + hh, subs.z + hh);
				if(tree->intersectBox(box)) 
					addCell(subs, level1);
			}
		}
		
		m_cellsToRefine->next();
    }
}