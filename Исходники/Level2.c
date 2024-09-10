void Ini2(void)
{
	//水果数量
	Fruit_NUM = 0;
	//水果产生时间间隔
	TimeTot = 0;
	//临时定义狗运动时间
	TimeTot1 = 0;
	//捡到的石头数量
	static int StoneCount = 10;

	// 对象1的初始位置
	obj1X = -10.0f;
	obj1Y = 0.0f;
	memset(sGameObjList, 0, sizeof(GameObj)*GAME_OBJ_NUM_MAX);
	GameObj* pObj;
	int i;

	BossBlood = 2;      //初始化BOSS血量

	// 为开始画对象做准备
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// 对象实例化：游戏开始只有小盗和狗和农场主需要实例化
	// 小盗对象实例化
	Burglar = gameObjCreate(TYPE_BURGLAR, BURGLAR_SIZE, 0, 0, 0.0f);
	AE_ASSERT(Burglar);
	Burglar->posCurr.x = AEGfxGetWinMaxX()-20;
	Burglar->posCurr.y = 100.0f;
	Burglar->dirCurr = acosf(Burglar->posCurr.x / ((float)sqrt(Burglar->posCurr.x*Burglar->posCurr.x + Burglar->posCurr.y * Burglar->posCurr.y))) - PI;
	Burglar->scale = 10.0f;

	//初始化静止的石头
	for (i = 0; i < 3; i++)
	{
		pObj = gameObjCreate(TYPE_STONE_STATIC, 3.0f, 0, 0, 0.0f);
		AE_ASSERT(pObj);
		// 实例化
		// 初始化: 坐标位置 朝向和尺寸大小
		switch (i)
		{
		case 0:
			pObj->posCurr.x = 100.0f;
			pObj->posCurr.y = 100.0f;
			break;
		case 1:
			pObj->posCurr.x = 100.0f;
			pObj->posCurr.y = AEGfxGetWinMaxY() - 30;
			break;
		case 2:
			pObj->posCurr.x = AEGfxGetWinMinX() + 40;
			pObj->posCurr.y = 50.0f;
			break;
		}
		pObj->dirCurr = acosf(pObj->posCurr.x / ((float)sqrt(pObj->posCurr.x*pObj->posCurr.x + pObj->posCurr.y * pObj->posCurr.y))) - PI;

		pObj->scale = 5.0f;
	}

	//初始化看不见的陷阱
	for (int a = 0; a < 3; a++)
	{
		pObj = gameObjCreate(TYPE_TRAP_IN, 10.0f, 0, 0, 0.0f);
		AE_ASSERT(pObj);
		//初始化陷阱位置及朝向比例

		pObj->posCurr.x = a*100.0f;
		pObj->posCurr.y = -100.0f;
		pObj->dirCurr = acosf(pObj->posCurr.x / ((float)sqrt(pObj->posCurr.x*pObj->posCurr.x + pObj->posCurr.y * pObj->posCurr.y))) - PI;

		pObj->scale = 10.0f;
	}

	//初始化农场主
	pBoss = gameObjCreate(TYPE_BOSS, 10.0f, 0, 0, 0.0f);
	AE_ASSERT(pBoss);
	//初始化农场主位置及朝向比例
	pBoss->posCurr.x = 100.0f;
	pBoss->posCurr.y = 100;
	pBoss->dirCurr = acosf(pBoss->posCurr.x / ((float)sqrt(pBoss->posCurr.x*pBoss->posCurr.x + pBoss->posCurr.y * pBoss->posCurr.y))) - PI;
	pBoss->scale = 10.0f;

	//狗对象实例化 并 初始化
	for (i = 0; i < DOG_NUM; i++)
	{
		// 实例化
		pObj = gameObjCreate(TYPE_DOG, 10.0f, 0, 0, 0.0f);
		pDog[i] = pObj;//给狗分配指针
		AE_ASSERT(pObj);
		pObj->posCurr.x = 100.0f;
		pObj->posCurr.y = 100.0f;
		
		pObj->dirCurr = acosf(pObj->posCurr.x / ((float)sqrt(pObj->posCurr.x*pObj->posCurr.x + pObj->posCurr.y * pObj->posCurr.y))) - PI;

		pObj->scale = 10.0f;
	}


	//农场主血量初始化
	pObj = gameObjCreate(TYPE_BOSSBLOOD, 10.0f, 0, 0, 0.0f);
	AE_ASSERT(pObj);
	//初始化血量位置
	pObj->posCurr.x = pBoss->posCurr.x;
	pObj->posCurr.y = pBoss->posCurr.y + 35.0f;

	//主角血量初始化
	pObj = gameObjCreate(TYPE_BURGLARBLOOD, 10.0f, 0, 0, 0.0f);
	AE_ASSERT(pObj);
	//初始化血量位置
	pObj->posCurr.x = Burglar->posCurr.x;
	pObj->posCurr.y = Burglar->posCurr.y + 35.0f;

	//地图的引入
	FILE *fp = NULL;
	if ((fp = fopen("wdp.txt", "r")) != NULL)
	{
		int length = 0, width = 0;
		fscanf(fp, "%d%d", &length, &width);
		int i = 0, j = 0;
		for (; i < length; i++)
		{
			for (j = 0; j < width; j++)
			{
				fscanf(fp, "%d", &mapinfo[i][j]);
			}
		}

		//读入地图
		for (i = 0; i < length; i++)
		{
			for (j = 0; j < width; j++)
			{
				if (mapinfo[i][j] == 1)
				{
					//画地图
					pObj = gameObjCreate(TYPE_MAP, 1.0f, 0, 0, 0.0f);
					AE_ASSERT(pObj);
					pObj->posCurr.y = i * 40 - 400.0f;
					pObj->posCurr.x = j*15 - 300.0f;
				}
			}
		}
	}
	else if ((fp = fopen("wdp.txt", "r")) == NULL)
	{
		KeyPressed[KeyESC] = TRUE;
	}

	// 签到
	fprintf(fp, "Level2:Initialize\n");
}