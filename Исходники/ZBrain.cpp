bool ZBrain::EscapeFromStuckIn(list<rvector>& wayPointList)
{
	// 길찾기 코드의 허점이 드러나는 맵 지점들이 있다.. 그런 곳에서는 몹이 이동하지를 못한다
	// 그런곳을 탈출하기 위해 땜빵을 한다. true 리턴하면 웨이포인트를 여기서 지정했다는 의미.
	DWORD currTime = timeGetTime();
	// 오랜시간 같은 곳에 멈춰있다면 아예 워프해버린다
	if (currTime - m_dwExPositionTimeForWarp > 2000)
	{
		rvector diff = m_exPositionForWarp - m_pBody->GetPosition();

		ResetStuckInStateForWarp();

		if (MagnitudeSq(diff) < 100)
		{
			OutputDebugString("NPC NEED WARP....\n");
			RNavigationMesh* pNavMesh = ZGetGame()->GetWorld()->GetBsp()->GetNavigationMesh();
			if (pNavMesh) {
				// 근방의 랜덤지점을 정한다

				// 랜덤 방향 얻기
				float angle = (rand() % (314*2)) * 0.01f;
				D3DXMATRIX matRot;
				D3DXMatrixRotationZ(&matRot, angle);

				rvector dir(200, 0, 0);	// 이동할 거리
				dir = dir * matRot;
				rvector newpos = m_pBody->GetPosition() + dir;

				// 가장 가까운 네비게이션노드의 센터로 옮긴다 (네비게이션노드가 크게 잡혀 있는 맵에선 워프가 심하게 눈에 띌수 있음..)
				RNavigationNode* pNavNode = pNavMesh->FindClosestNode(newpos);
				if (pNavNode) {
					m_pBody->SetPosition( pNavNode->CenterVertex());
					OutputDebugString("NPC WARP DONE!\n");
					return false;
				}
			}
		}
	}

	// 짧은시간 같은 곳에 멈춰있다면 앞으로 한발짝 정도 움직여서 탈출시도
	if (currTime - m_dwExPositionTime > 1000)
	{
		rvector diff = m_exPosition - m_pBody->GetPosition();

		ResetStuckInState();

		if (MagnitudeSq(diff) < 100)
		{
			wayPointList.clear();

			// 기본적으로 앞쪽으로 방향을 잡되 좌우로 랜덤하게 방향을 준다
			rvector dir = m_pBody->GetDirection();
			rmatrix matRot;
			D3DXMatrixRotationZ(&matRot, (rand()%314 - 157) * 0.01f);	// 3.14 즉 반바퀴 범위 내에서 방향을 틀게 함
			Normalize(dir);

			dir *= m_pBody->GetCollRadius() * 0.8f;
			wayPointList.push_back(m_pBody->GetPosition() + dir);

			PushWayPointsToTask();

			return true;
		}
	}

	return false;
}