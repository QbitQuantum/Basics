/*
김연아 선수의 모션을 취하는 함수
*/
void Show()
{
	sndPlaySound(TEXT("C:\\sample4.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity(); //CTM 초기화

	/*
	로봇의 기본적인 관절의 움직임 범위를 제한하는 곳
	*/
	L_Arm_x = (-40) + sin(time2) * 60;//왼쪽 어깨의 각도시작은 -40상태에서 sin()함수를 사용하여 주기적인 움직임 설정
	R_Arm_x = (-80) - L_Arm_x;       //우측 어깨의 각도시작은 -80상태에서 왼쪽어깨 움직임의 반대로 설정
	R_Arm_y = -abs(cos(time2) * 10);  //우측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)
	L_Arm_y = -abs(-cos(time2) * 10); //좌측팔뚝 각도조절(팔을 뻗는 움직임표현을위하여 어깨의 sin()함수와 반대인 cos()함수 사용)

	R_Leg_y = abs(-sin(time) * 30 - 30); //우측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	L_Leg_y = abs(sin(time) * 30 - 30);  //좌측종아리 각도조절(abs절대값을 줌으로써 종아리가 앞으로 꺾이지 않는 한계점을 설정)
	R_Leg_x = sin(time) * 60;          //우측다리는 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정
	L_Leg_x = -R_Leg_x;             //좌측다리는 우측다리반대로 60도 각도까지 움직이되 sin()함수를 사용하여 주기적인 움직임 설정

	////////////////display////////////////

	cyl = gluNewQuadric(); //실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //초기화
	glMatrixMode(GL_MODELVIEW); //모드 설정

	DrawGround(); //지면 호출
	glLoadIdentity(); //CTM 초기화
	glRotatef(-230.0, 0, 1, 0); //y축기준으로 회전

	/*
	로봇이 피겨동작시 몸이 틀어지는 것을 표현
	*/
	glRotatef(sin(time) * 7, 0, 0, 1); //z축기준으로 7도 까지 각도틀어짐 (sin()함수를 사용하여 주기적인 움직임 설정)
	glRotatef(sin(time) * 7, 0, 1, 0); //y축으로 7도 까지 각도틀어짐 (sin()함수를 사용하여 주기적인 움직임 설정)

	//로봇 몸체 각도 조절
	glTranslatef(0.0, 0.18, 0.0); //y축으로 이동
	glRotatef(80, 1, 0, 0);        //x축 기준으로 회전

	glTranslatef(0.0, 0.5, 0.0);//최초 위치 

	glPushMatrix(); // 처음 저장 위치

	DrawBody(0, 0, 0, 0); // 몸통 함수 호출

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	Drawneck(); // 목함수 호출

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	//머리 위치 설정
	glRotatef(-75, 1, 0, 0); //x축기준으로 회전(머리를 위쪽으로 돌리기)
	glTranslatef(0.0, -0.02, 0.0); //y축으로 이동 (머리 시작점)

	DrawHead(); // 머리 호출

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	//우측전체팔 위치 설정


	DrawR_Arm((R_Arm_y + 30), 1, 0, 0);  //우측팔호출
	DrawR_Hand(-(R_Arm_y - 15), 1, 0, 0); //우측팔뚝

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	//좌측전체팔 위치 설정
	glTranslatef(0.0, -0.16, -0.04);//y축,z축으로 이동(좌측팔 시작점)
	glRotatef(40, 0, 0, 1);     //z축 기준으로 회전

	DrawL_Arm((L_Arm_y + 30), 1, 0, 0);   //좌측팔호출	
	DrawL_Hand(-(L_Arm_y - 15), 1, 0, 0);  //좌측팔뚝

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	//좌측전체 다리 위치 설정
	glTranslatef(0.0, -0.45, -0.25);//y축,z축으로 이동(좌측다리 시작점)
	glRotatef(-90, 1, 0, 0);  //x축 기준으로 회전

	DrawL_Legs(-30, 1, 0, 0);  //좌측다리
	DrawL_foot(10, 1, 0, 0);  //좌측종아리		 

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.
	glPushMatrix();// 처음 저장 좌표 다시 저장

	//우측전체 다리 위치 설정
	glTranslatef(0.0, -0.5, -0.5);//y축,z축으로 이동(우측다리 시작점)
	glRotatef(-90, 1, 0, 0); //x축 기준으로 회전

	DrawR_Legs(160, 1, 0, 0);  //우측다리
	DrawR_foot(R_Leg_y, 1, 0, 0);  //우측종아리		

	glPopMatrix(); // 처음 저장 좌표로 돌아 간다.

	glutSwapBuffers();
}