/* 描画のコールバック関数 */
void display(void)
{
	float ftime;
	int triangles;
	GLint texLoc;
	char str[256];

	QueryPerformanceCounter(&startTime);

	/* 基本的なステート */
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	/* モデルビュー行列のセットアップ */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* 視点 */
	gluLookAt(0.0f, 0.0f, 120.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f);

	/* 光源設定(ワールド座標設定) */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	FUTL_SetLight(GL_LIGHT0, &light);

	/* 背景 */
	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);//origin
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ポリゴン描画モード */
	if (pmode == 0)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if (pmode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	glPushMatrix();

	/* マウス操作によるモデルの回転 */
	glMultMatrixf((float *)(&mdlRot));

	/* シェーダプログラムの適用 */
	glUseProgram(shdProg);

	/* テクスチャユニット0を指定 */
	texLoc = glGetUniformLocation(shdProg, "toontex");
	glUniform1i(texLoc, 0);

	/* トーラスの描画 */
	if (drawVBO)
	{
		triangles = FUTL_DrawTorusVBO(count);
		vtxStr = vtxBufStr;
	}
	else
	{
		triangles = FUTL_DrawTorus(count);
		vtxStr = vtxAryStr;
	}

	/* ドラッグ中でなく、一時停止中でもない場合、トーラスは自転 */
	if (drag == 0 && move != 0)
	{
		count++;
	}

	glPopMatrix();

	/* トーラスの描画時間を計測（計測用文字描画を含めない） */
	QueryPerformanceCounter(&endTime);
	ftime = FUTL_SubPCounter(&endTime, &startTime);
	drawFPS = 1.0f / ftime;

	sprintf_s(str, sizeof(str), 
			"%s : Frame=%4.0f[fps]: Draw=%7.0f[fps]: Perf=%.0f[Kt/s]\n", 
			vtxStr, frameFPS, drawFPS, triangles / (1000.0f * ftime));

	/* 左下原点の座標系で描画 */
	FUTL_DrawString(gpuStr, 4, (screenHeight - 1)- 15);
	FUTL_DrawString(str, 4, (screenHeight - 1) - 2 * 15);

	glutSwapBuffers();

	/* 1フレームの間隔を測定 */
	QueryPerformanceCounter(&cycleTime);
	ftime = FUTL_SubPCounter(&cycleTime, &preCycleTime);
	frameFPS = 1.0f / ftime;
	preCycleTime = cycleTime;
}