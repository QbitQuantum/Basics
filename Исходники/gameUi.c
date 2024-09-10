/*****************************************************************
 * 函数名称：execGame
 * 描述说明：运行连连看游戏
 * 输入参数：p_gameUi:游戏体指针,blockNum:当前关数
 * 输出参数：1:重新开始当前关2:返回3:闯关成功4:超时5:死局
*****************************************************************/
int execGame(gameUi_t *p_gameUi, int blockNum)
{
	int ret = 0;
	struct LcdDot touchXY;

	gameExeFlag = 1;
	restTime = 75;
	noConnectTime = 0;
	initGame(p_gameUi, blockNum);
	showGame(p_gameUi);
	
	while(1){
		while(GetTouch(&touchXY) == 0);

		if(restTime <= 0){
			gameExeFlag = 0;
			return 4;
		}

		if(noConnectTime > 3){
			if(haveConnect(&p_gameUi->m_mat) == 0){
				gameExeFlag = 0;
				return 5;
			}else{
				noConnectTime = 0;
			}
		}

		ret = doGame(&p_gameUi->m_gameMng, &p_gameUi->m_mat, &touchXY);
		if(ret != 0){//按在矩阵内
			if(ret == 2){//点击第二次
				if(seccess(&p_gameUi->m_gameMng)){
					gameExeFlag = 0;
					return 3;
				}else{
					//gameDelay(1000);
					//showGame(p_gameUi);	
				}
			}
		}else{//按在矩阵外
			//showGame(p_gameUi);
			ret = getMenu(&p_gameUi->m_ui, &touchXY);

			if(ret > 0){
				gameExeFlag = 0;
				return ret;
			}
		}
	}

	return 0;
}