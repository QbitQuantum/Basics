////////////////////////////////////////////////////send & recv from server
void sendRecv()
{
	while (1)
	{
		socket.receive(recvChar, 1024, received);
		cout << recvChar << endl;

		if (recvChar[0] != anotherClient)
		{
			for (int i0 = 0; i0 < tank.size(); i0++)
			{
				sendChar[i0] = playerButton[i0];
			}

			for (int i1 = 0; i1 < tank.size(); i1++)
			{
				for (int i2 = 0; i2 < 7; i2++)
				{
					tank[i1].button[i2] = recvChar[7 * i1 + i2];
					cout << tank[i1].button[i2] << endl;
				}
			}
			///making send char for normal use
			sendChar[0] = playerID;
			for (int i0 = 0; i0 < 7; i0++)
			{
				sendChar[i0 + 1] = playerButton[i0];
			}
			socket.send(sendChar, 1024);
		}
		else
		{
			sendChar[0] = wall.size();
			for (int j0 = 0; j0 < wall.size(); j0++)
			{
				sendChar[wall[j0].tedadeVizhegiha*j0 + 1] = wall[j0].ID;
				sendChar[wall[j0].tedadeVizhegiha*j0 + 2] = wall[j0].centerPoint.x;
				sendChar[wall[j0].tedadeVizhegiha*j0 + 3] = wall[j0].centerPoint.y;
				sendChar[wall[j0].tedadeVizhegiha*j0 + 4] = wall[j0].length;
				sendChar[wall[j0].tedadeVizhegiha*j0 + 5] = wall[j0].width;
				sendChar[wall[j0].tedadeVizhegiha*j0 + 6] = wall[j0].leftUpPoint.x;
				sendChar[wall[j0].tedadeVizhegiha*j0 + 7] = wall[j0].leftUpPoint.y;
				sendChar[wall[j0].tedadeVizhegiha*j0 + 8] = wall[j0].rightDownPoint.x;
				sendChar[wall[j0].tedadeVizhegiha*j0 + 9] = wall[j0].rightDownPoint.y;
			}
			sendChar[(wall.size()*wall[0].tedadeVizhegiha) + 1] = bullet.size();
			for (int j0 = wall.size()*wall[0].tedadeVizhegiha + 1; j0 < wall.size()*wall[j0].tedadeVizhegiha + 1 + bullet.size(); j0++)
			{
				sendChar[bullet[j0].tedadeVizhegiha*j0 + 1] = bullet[j0].ID;
				sendChar[bullet[j0].tedadeVizhegiha*j0 + 2] = bullet[j0].tankID;
				sendChar[bullet[j0].tedadeVizhegiha*j0 + 3] = bullet[j0].centerPoint.x;
				sendChar[bullet[j0].tedadeVizhegiha*j0 + 4] = bullet[j0].centerPoint.y;
				sendChar[bullet[j0].tedadeVizhegiha*j0 + 5] = bullet[j0].radius;
				sendChar[bullet[j0].tedadeVizhegiha*j0 + 6] = bullet[j0].velocity.x;
				sendChar[bullet[j0].tedadeVizhegiha*j0 + 7] = bullet[j0].velocity.y;
			}
			sendChar[wall.size()*wall[0].tedadeVizhegiha + (bullet.size()*bullet[0].tedadeVizhegiha) + 2] = tank.size();
			for (int j0 = wall.size()*wall[0].tedadeVizhegiha + (bullet.size()*bullet[0].tedadeVizhegiha) + 2; j0 < wall.size()*wall[0].tedadeVizhegiha + (bullet.size()*bullet[0].tedadeVizhegiha) + tank.size() + 2; j0++)
			{
				sendChar[tank[j0].tedadeVizhegiha*j0 + 1] = tank[j0].forwardVelocity;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 2] = tank[j0].backwardVelocity;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 3] = tank[j0].bodyRotationVelocity;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 4] = tank[j0].pipeRotationVelocity;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 5] = tank[j0].vecForwardVelocity.x;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 6] = tank[j0].vecForwardVelocity.y;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 7] = tank[j0].vecBackwardVelocity.x;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 8] = tank[j0].vecBackwardVelocity.y;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 9] = tank[j0].ID;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 10] = tank[j0].centerPoint.x;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 11] = tank[j0].centerPoint.y;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 12] = tank[j0].length;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 13] = tank[j0].width;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 14] = tank[j0].bodyDegree;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 15] = tank[j0].bodyRotateSpeed;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 16] = tank[j0].pipeDegree;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 17] = tank[j0].pipeRotateSpeed;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 18] = tank[j0].velocity.x;
				sendChar[tank[j0].tedadeVizhegiha*j0 + 19] = tank[j0].velocity.y;
			}
		}

		for (int i = 0; i < recvChar[0]; i++)
		{
			wall[i + 1].ID = recvChar[i*wall[0].tedadeVizhegiha + 1];
			wall[i + 1].centerPoint.x = recvChar[i*wall[0].tedadeVizhegiha + 2];
			wall[i + 1].centerPoint.y = recvChar[i*wall[0].tedadeVizhegiha + 3];
			wall[i + 1].length = recvChar[i*wall[0].tedadeVizhegiha + 4];
			wall[i + 1].width = recvChar[i*wall[0].tedadeVizhegiha + 5];
			wall[i + 1].leftUpPoint.x = recvChar[i*wall[0].tedadeVizhegiha + 6];
			wall[i + 1].leftUpPoint.y = recvChar[i*wall[0].tedadeVizhegiha + 7];
			wall[i + 1].rightDownPoint.x = recvChar[i*wall[0].tedadeVizhegiha + 8];
			wall[i + 1].rightDownPoint.y = recvChar[i*wall[0].tedadeVizhegiha + 9];
		}
		for (int i = (recvChar[0] * wall[0].tedadeVizhegiha) + 1; i < recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1]; i++)
		{
			bullet[i + 1].ID = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (i*bullet[0].tedadeVizhegiha) + 2];
			bullet[i + 1].tankID = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (i*bullet[0].tedadeVizhegiha) + 3];
			bullet[i + 1].centerPoint.x = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (i*bullet[0].tedadeVizhegiha) + 4];
			bullet[i + 1].centerPoint.y = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (i*bullet[0].tedadeVizhegiha) + 5];
			bullet[i + 1].radius = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (i*bullet[0].tedadeVizhegiha) + 6];
			bullet[i + 1].velocity.x = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (i*bullet[0].tedadeVizhegiha) + 7];
			bullet[i + 1].velocity.y = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (i*bullet[0].tedadeVizhegiha) + 8];
		}
		for (int i = (recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2; i < recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 1] - 1; i++)
		{
			tank[i + 1].forwardVelocity = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 3];
			tank[i + 1].backwardVelocity = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 4];
			tank[i + 1].bodyRotationVelocity = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 5];
			tank[i + 1].pipeRotationVelocity = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 6];
			tank[i + 1].vecForwardVelocity.x = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 7];
			tank[i + 1].vecForwardVelocity.y = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 8];
			tank[i + 1].vecBackwardVelocity.x = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 9];
			tank[i + 1].vecBackwardVelocity.y = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 10];
			tank[i + 1].ID = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 11];
			tank[i + 1].centerPoint.x = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 12];
			tank[i + 1].centerPoint.y = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 13];
			tank[i + 1].length = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 14];
			tank[i + 1].width = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 15];
			tank[i + 1].bodyDegree = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 16];
			tank[i + 1].bodyRotateSpeed = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 17];
			tank[i + 1].pipeDegree = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 18];
			tank[i + 1].pipeRotateSpeed = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 19];
			tank[i + 1].velocity.x = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 20];
			tank[i + 1].velocity.y = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + (i*tank[0].tedadeVizhegiha) + 21];

		}
		// tank[(recvChar[0]*wall[0].tedadeVizhegiha)+(recvChar[(recvChar[0]*wall[0].tedadeVizhegiha)+1]*bullet[0].tedadeVizhegiha)+(recvChar[((recvChar[0]*wall[0].tedadeVizhegiha)+(recvChar[(recvChar[0]*wall[0].tedadeVizhegiha)+1]*bullet[0].tedadeVizhegiha)+2)]-1)].push_back();
		//tank[tank.size()-1].vizhegi1 =
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 3].forwardVelocity = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 3];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 4].backwardVelocity = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 4];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 5].bodyRotationVelocity = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 5];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 6].pipeRotationVelocity = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 6];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 7].vecForwardVelocity.x = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 7];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 8].vecForwardVelocity.y = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 8];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 9].vecBackwardVelocity.x = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 9];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 10].vecBackwardVelocity.y = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 10];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 11].ID = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 11];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 12].centerPoint.x = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 12];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 13].centerPoint.y = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 13];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 14].length = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 14];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 15].width = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 15];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 16].bodyDegree = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 16];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 17].bodyRotateSpeed = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 17];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 18].pipeDegree = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 18];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 19].pipeRotateSpeed = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 19];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 20].velocity.x = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 20];
		tank[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 21].velocity.y = recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + ((recvChar[((recvChar[0] * wall[0].tedadeVizhegiha) + (recvChar[(recvChar[0] * wall[0].tedadeVizhegiha) + 1] * bullet[0].tedadeVizhegiha) + 2)] - 1)*tank[0].tedadeVizhegiha) + 21];
		}


}