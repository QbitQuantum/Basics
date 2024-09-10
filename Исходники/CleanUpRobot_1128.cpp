double MyController::onAction(ActionEvent &evt)
{
/*	if(!checkService("RecogTrash")){
		m_srv == NULL;
		m_state = 0;
		return UPDATE_INTERVAL;
	}
	
	if(m_srv == NULL){
		// ゴミ認識サービスが利用可能か調べる
		if(checkService("RecogTrash")){
			// ゴミ認識サービスに接続
			m_srv = connectToService("RecogTrash");
			return UPDATE_INTERVAL;
		}
	}*/


	//if(evt.time() < m_time) printf("state: %d \n", m_state);
	switch(m_state) {
		// 初期状態
		case 0: {
			if(m_srv == NULL){
				// ゴミ認識サービスが利用可能か調べる
				if(checkService("RecogTrash")){
					// ゴミ認識サービスに接続
					m_srv = connectToService("RecogTrash");
				}
			} else if(m_srv != NULL && m_executed == false){  
				//rotate toward upper
				m_my->setJointVelocity("LARM_JOINT4", -m_jvel, 0.0);
				m_my->setJointVelocity("RARM_JOINT4", -m_jvel, 0.0);
				// 50°回転
				m_time = DEG2RAD(ROTATE_ANG) / m_jvel + evt.time();
				m_state = 5;
				m_executed = false;			
			}
			break;
		}

		case 5: {
			if(evt.time() > m_time && m_executed == false) {
				m_my->setJointVelocity("LARM_JOINT4", 0.0, 0.0);
				m_my->setJointVelocity("RARM_JOINT4", 0.0, 0.0);
				sendSceneInfo("Start");				
				printf("Started! \n");
				m_executed = true;
			}
			break;
		}


		case 800: {
			if(evt.time() > m_time && m_executed == false) {
				sendSceneInfo();
				m_executed = true;
			}
			break;
		}

		case 805: {
			if(evt.time() > m_time && m_executed == false) {
				// 送られた座標に移動する
				double range = 0;
				m_time = rotateTowardObj(nextPos, m_rotateVel, evt.time());
				m_state = 807;
				m_executed = false;
			}
			break;
	  }

		case 807: {
			if(evt.time() > m_time && m_executed == false) {
				m_my->setWheelVelocity(0.0, 0.0);				
				printf("移動先 x: %lf, z: %lf \n", nextPos.x(), nextPos.z());				
				m_time = goToObj(nextPos, m_vel*4, m_range, evt.time());
				
				if (m_lookObjFlg == 1.0) {
					printf("looking to Obj \n");				
					m_state = 810;
				} else {
					printf("go to next node \n");				
					m_state = 815;
				}

				m_executed = false;
			}
			break;
		}

		case 810: {
			// 送られた座標に移動中
			if(evt.time() > m_time && m_executed == false) {
				m_my->setWheelVelocity(0.0, 0.0);
				m_time = rotateTowardObj(m_lookingPos, m_rotateVel, evt.time());
				m_executed = false;
				m_state = 815;
			}
			break;
		}
		
		case 815: {
			// 送られた座標に移動中
			if(evt.time() > m_time && m_executed == false) {
				m_my->setWheelVelocity(0.0, 0.0);				
				sendSceneInfo();
				printf("sent data to SIGViewer \n");				
				m_executed = true;
			}
			break;
		}

		case 920: {
			// 送られた座標に回転する
			m_time = rotateTowardObj(nextPos, m_rotateVel, evt.time());
			m_state = 921;
			m_executed = false;
			break;
		}

		case 921: {
			// ロボットが回転中
			if(evt.time() > m_time && m_executed == false) {
				m_my->setWheelVelocity(0.0, 0.0);
				m_executed = false;
			}
			break;
		}

		default: {
			break;
		}

	}

	return UPDATE_INTERVAL;

}  