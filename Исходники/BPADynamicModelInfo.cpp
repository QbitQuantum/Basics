int BPA_DYNAMICMODELINFO::Area_ReadBPALine(char* PFLine)
{
	int i, k, AreaNo;
	float BaseKv;
	char Name[_MaxNameLen], Zone[_MaxNameLen], tArea[_MaxNameLen];
	GetItemFromLine(PFLine, tArea, AREA_Para[0], AREA_Loca[0]);
	ReplaceName(tArea, _MaxNameLen);
	tArea[_MaxNameLen - 1] = '\0';
	if (strlen(PFLine) > 3 && PFLine[2] == '+')
	{//续卡
		k = cpGetAreaInfo()->iGetAreaNo(tArea);
		if (k >= cpGetAreaInfo()->iGetAreaTotal())
		{
			sprintf(ErrorMessage[0], "A+卡没有对应的A卡 '%s' 不存在, 忽略该卡：", tArea);
			strcpy(ErrorMessage[1], PFLine);
			cpGetErrorInfo()->PrintWarning(0, 2);
			return 0;
		}
		AreaNo = k;
	}
	else{
		AREABASE *tempArea;
		tempArea = new AREABASE;
		tempArea->ZoneTotal = 0;
		GetItemFromLine(PFLine, Name, AREA_Para[1], AREA_Loca[1]);
		GetItemFromLine(PFLine, &BaseKv, AREA_Para[2], AREA_Loca[2]);
		if (BaseKv<0 || BaseKv>99999.)
		{
			sprintf(ErrorMessage[0], " 节点 %s的基准电压为0，程序缺省将其设为100.0KV", Name);
			cpGetErrorInfo()->PrintWarning(0, 1);
			BaseKv = 100.0f;
		}
		ReplaceName(Name, _MaxNameLen);
		ResetBPAName(Name, BaseKv);
		strcpy(tempArea->SlackBusName, Name);
		strcpy(tempArea->AreaName, tArea);
		GetItemFromLine(PFLine, &(tempArea->AreaPower), AREA_Para[3], AREA_Loca[3]);
		AreaNo = cpGetAreaInfo()->AddNewArea(tempArea);
		if (AreaNo < 0)
		{
			sprintf(ErrorMessage[0], "区域数目超过设定值%d，忽略该卡：", _MaxAreaNo);
			strcpy(ErrorMessage[1], PFLine);
			cpGetErrorInfo()->PrintWarning(6, 2);
			return 0;
		}
	}
	i = 0;
	while ((int)(strlen(PFLine)) > (AREA_Loca[4] + 3 * i + 2))
	{//这个地方能不限制长度，只要有就可以继续读入
		GetItemFromLine(PFLine, Zone, AREA_Para[4], AREA_Loca[4] + 3 * i);
		i++;
		if (IsBlank(Zone, _MaxNameLen))continue;
		if (cpGetAreaInfo()->cpGetArea(AreaNo)->ZoneTotal >= _MaxAreaZoneNo)
		{
			sprintf(ErrorMessage[0], "区域%s数目超过设定值%d，忽略多余的Zone：%s", cpGetAreaInfo()->cpGetArea(AreaNo)->ZoneName, _MaxAreaZoneNo, Zone);
			cpGetErrorInfo()->PrintWarning(0, 1);
			continue;
		}
		strcpy(cpGetAreaInfo()->cpGetArea(AreaNo)->ZoneName[cpGetAreaInfo()->cpGetArea(AreaNo)->ZoneTotal], Zone);
		cpGetAreaInfo()->cpGetArea(AreaNo)->ZoneTotal++;
	}
	return 1;
}