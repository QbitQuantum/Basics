//¿øÇÏ´Â °´Ã¼ÀÇ xÁÂÇ¥¸¦ ³Ñ±â¸é ±× °´Ã¼°¡ ÁöÇüÀ» µû¶ó delta¸¸Å­ ÀÌµ¿ÇÑ´Ù°í ÇßÀ»¶§ÀÇ º¤ÅÍ °ªÀ» ¹ÝÈ¯ÇÑ´Ù.
//delta°ªÀÌ -¸é µÚÂÊÀ¸·Î ÀÌµ¿ÇÑ´Ù°í ÇßÀ»¶§ÀÇ º¤ÅÍ°ªÀ» ¹ÝÈ¯ÇÑ´Ù.
CCPoint GroundManager::getMoveVecFromGround(float objX,int delta)
{
	if(delta == 0) return ccp(0,0);
	
	if(showingGrounds.empty()) return ccp(delta,0);

	if(!itIsInPattern(objX) && !itIsInPattern(objX+delta)) 
		return ccp(delta,0);

	CCPoint objPos = ccp(objX,getYGroundPos(objX));
	CCPoint v;

	list<Ground*>::iterator it;
	CCPoint direction;
	float sumDelta = (float)abs(delta);

	for(it = showingGrounds.begin();it != showingGrounds.end();it++)
	{
		list<CCPoint>::iterator point_it;

		for(point_it = (*it)->points.begin(); point_it != (*it)->points.end(); point_it++)
		{
			patternPoints.push_back(ccp((*point_it).x+((*it)->getPosition().x-(*it)->getWidth()*0.5),
				(*point_it).y+((*it)->getPosition().y-(*it)->getHeight()*0.5)));
		}
	}

	patternPoints.push_front(ccp(patternPoints.front().x-abs(delta)-0.0001,patternPoints.front().y));
	patternPoints.push_back(ccp(patternPoints.back().x+abs(delta)+0.0001,patternPoints.back().y));

	list<CCPoint>::iterator point_it;

	CCPoint before_point = objPos;

	if(delta > 0)
	{
		for(point_it = patternPoints.begin(); point_it != patternPoints.end(); point_it++)
		{
			if((*point_it).x >= objPos.x) //º¯È¯µÈ xÁÂÇ¥°¡ ÇöÀç ÁÂÇ¥º¸´Ù ÀÛ¾ÆÁú¶§ º¤ÅÍÀÇ sumÀ» ½ÃÀÛÇÑ´Ù.
			{
				CCPoint d = (*point_it) - before_point;

				if(sumDelta-d.getLength() <= 0)
				{
					v = v + d.normalize()*sumDelta;
					break;
				}
				else
				{
					v = v + d;
				}
				sumDelta -= d.getLength();

				before_point = (*point_it);
			}
		}
	}
	else
	{
		list<CCPoint>::reverse_iterator point_it;

		for(point_it = patternPoints.rbegin();point_it!=patternPoints.rend();point_it++)
		{
			if((*point_it).x <= objPos.x)
			{
				CCPoint d = before_point - (*point_it);

				if(sumDelta-d.getLength() <= 0)
				{
					v = v + -d.normalize()*sumDelta;
					break;
				}
				else
					v = v-d;
				sumDelta -= d.getLength();

				before_point = (*point_it);
			}
		}
	}
	patternPoints.clear();

	float check_y = getYGroundPos(objPos.x+v.x);

	if(check_y != objPos.y+v.y)
		v.y = check_y - objPos.y;

	return v;
}