int _tmain(int argc, _TCHAR* argv[])
{
	
	int nRepeatPerSecond = 0;// 每秒重复次数，表示时间效率
	
	StopWatchWin timer;
	
	{
		// 问题规模档次，7档，64K至256M，4倍递增
		PROBLEM_SIZE  = MEGA_SIZE * PROBLEM_SCALE[iClass] ;
		
		// 数据初始化：坐标、矩阵
		initialize(PROBLEM_SIZE, JOINT_SIZE);
		
		timer.start();

		while ( timer.getTime() < 10000  )
		{
			// 执行运算：坐标矩阵变换
			updateVectorByMatrix(_vertexesStatic.pVertex, PROBLEM_SIZE, _joints.pMatrix, _vertexesDynamic.pVertex);
			nRepeatPerSecond ++;
		}

		timer.stop();
		timer.reset();
		
		// 数据销毁：坐标、矩阵
		unInitialize();

		// 查看时间效率
		printf("%d: F=%d, T=%.1f ms\n", iClass+1, nRepeatPerSecond/10, 10000.0f/nRepeatPerSecond);
	}
	
	// 输出结果：绘制坐标，按照点、线、面的形式
	// ...省略

	return 0;
}