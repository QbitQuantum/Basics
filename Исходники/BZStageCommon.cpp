string BZStageCommon::status() 
{ 
	string ret = "";

	if (!_debug_info)
		return ret;

	ret += "game:";
	char sz[1024];
	sprintf(sz, "fps:%.1f;", this->fps());
	//ret += sz;
#if defined(_DEBUG)
	char szMem[128];
	unsigned int alloced = gGetMemSizeAlloced();
	unsigned int maxalloced = gGetMemMaxSizeAlloced();
	sprintf(szMem, " mem:%d/%d", alloced, maxalloced);
	strcat(sz, szMem);
#endif
	ret += sz;
	ret += "\n";

	CAStageLayer* player = getFocus();
	if (null != player)
	{
		ret += player->_sprite_container_debug_log(player->name().c_str(), false);
		ret += player->debuglog();
	}

	return ret;
}