	void CSelectionPanel::OnSelected(const CRect&rect){//框選
		
		TRACE("CSelection::OnSelected\n");
		CPlayer* player = CPlayer::GetPlayer();
		set<CSprite*>::iterator it;
		//先清除容器內的東西
		panel->UnSelected();
		//所有的玩家
		int count=0;

		//如果物件跟選取框有交集，就算選取
		for(it = player->Sprites().begin();it!=player->Sprites().end();it++){
			CRect ans;
			if(ans.IntersectRect(rect,(*it)->ScreenRect())){
				selectedSprites.insert(*it);
				count++;
				if(count>=30){
					break;
				}
			}
		}
		for(it=selectedSprites.begin();it!=selectedSprites.end();it++){
			(*it)->OnSelected();
		}
		EraseSprites();
		if(selectedSprites.size()==0){
			CPlayer* npc = CPlayer::GetNPC();
			for(it = npc->Sprites().begin();it!=npc->Sprites().end();it++){
				CRect ans;
				CPoint gridPoint = (*it)->GridPoint();
				CMapTile* mapTile = CGameMap::GetMap()->GetMapTile((*it)->GridPoint());
				if(ans.IntersectRect(rect,(*it)->ScreenRect())){
					if(mapTile->IsExplored() && mapTile->VisionCount()!=0){
						selectedSprites.insert(*it);
						(*it)->OnSelected();
						break;
					}
				}
			}
			EraseSprites();
		}
		if(selectedSprites.size()==0){
			CPlayer* nature = CPlayer::GetNPC();
			for(it = nature->Sprites().begin();it!=nature->Sprites().end();it++){
				CRect ans;
				CPoint gridPoint = (*it)->GridPoint();
				CMapTile* mapTile = CGameMap::GetMap()->GetMapTile((*it)->GridPoint());
				if(ans.IntersectRect(rect,(*it)->ScreenRect())){
					if(mapTile->IsExplored() && mapTile->VisionCount()!=0){
						selectedSprites.insert(*it);
						(*it)->OnSelected();
						break;
					}
				}
			}
			EraseSprites();
		}
		//最後
	}