void CGameApp::SaveLevel()
{
	string savebricks;
	Vec2 brickPos;
	brickPos.x = START_BRICK_POS_X;
	brickPos.y = START_BRICK_POS_Y;
	nrBricks = 0;

	for(std::size_t levelbricks = 0; levelbricks < level.bricks.size(); levelbricks++)
	{
		if(level.bricks[nrBricks] == '-')
		{
			if(brickPos.x >= (m_nViewWidth - GET_MAX_BRICK_POS_X) - GET_MAX_BRICK_POS_X)
			{
				savebricks += level.bricks[nrBricks];
				brickPos.x = START_BRICK_POS_X;
				brickPos.y += brickHeight;
				nrBricks++;
				continue;
			}
			else
			{
				savebricks += level.bricks[nrBricks];
				brickPos.x += brickWidth;
				nrBricks++;
				continue;
			}
		}
		else
		{
			bool found = false;
			for(auto it = m_vGameObjects.begin(); it != m_vGameObjects.end(); ++it)
			{
				CGameObject * pGameObj = it->get();
				if(pGameObj->GetObjectType() == GOT_Brick)
				{
					if(pGameObj->myPosition.x == brickPos.x && pGameObj->myPosition.y == brickPos.y)
					{
						found = true;
						break;
					}
				}
			}


			if(found == true)
				if(brickPos.x >= (m_nViewWidth - GET_MAX_BRICK_POS_X) - GET_MAX_BRICK_POS_X)
				{
					savebricks += level.bricks[nrBricks];
					brickPos.x = START_BRICK_POS_X;
					brickPos.y += brickHeight;
					nrBricks++;
				}
				else
				{
					savebricks += level.bricks[nrBricks];
					brickPos.x += brickWidth;
					nrBricks++;
				}

				if(found == false)
					if(brickPos.x >= (m_nViewWidth - GET_MAX_BRICK_POS_X) - GET_MAX_BRICK_POS_X)
					{
						savebricks += "-";
						brickPos.x = START_BRICK_POS_X;
						brickPos.y += brickHeight;
						nrBricks++;
					}
					else
					{
						savebricks += "-";
						brickPos.x += brickWidth;
						nrBricks++;
					}
		}
	}

	char *end;
	end="END";
	FILE *f;
	f=fopen("savelevel.txt","w");
	fprintf(f,"%s\n", level.currentlevel.c_str());
	fprintf(f,"%s\n", savebricks.c_str());
	fprintf(f,"%s\n", level.nextlevel.c_str());
	fprintf(f,"\n%s", end);
	fclose(f);

}