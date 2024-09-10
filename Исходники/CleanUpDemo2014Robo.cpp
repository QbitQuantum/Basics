double DemoRobotController::onAction(ActionEvent &evt)
{
	switch(m_state) {
		case 0: {
			break;
		}
		case 1: {
			this->stopRobotMove();
			break;
		}
		case 50: {  // detour: rotate toward relay point 1
			if(evt.time() >= m_time) {
				this->stopRobotMove();

				double l_moveTime = rotateTowardObj(m_relayPoint1);

				m_time = l_moveTime+evt.time();
				m_state = 60;
			}
			break;
		}
		case 60: {  // detour: go toward relay point 1
			if(evt.time() >= m_time) {
				this->stopRobotMove();

				double l_moveTime = goToObj(m_relayPoint1, 0.0);

				m_time = l_moveTime+evt.time();
				m_state = 70;
			}
			break;
		}
		case 70: {  // rotate toward the position in front of trash
			if(evt.time() >= m_time) {
				this->stopRobotMove();

				double l_moveTime = rotateTowardObj(m_frontDesk1);

				m_time = l_moveTime+evt.time();
				m_state = 80;
			}
			break;
		}
		case 80: {  // go toward the position in front of trash
			if(evt.time() >= m_time) {
				this->stopRobotMove();

				double l_moveTime = goToObj(m_frontDesk1, 0.0);

				m_time = l_moveTime+evt.time();
				m_state = 90;
			}
			break;
		}
		case 90: {  // rotate toward the trash
			if(evt.time() >= m_time) {
				this->stopRobotMove();

				Vector3d l_tpos;

				if(m_task == 1)
					this->recognizeObjectPosition(l_tpos, m_trashName1);
				else
					this->recognizeObjectPosition(l_tpos, m_trashName2);

				double l_moveTime = rotateTowardObj(l_tpos);

				m_time = l_moveTime+evt.time();
				m_state = 100;
			}
			break;
		}
		case 100: {  // prepare the robot arm to grasping the trash
			if(evt.time() >= m_time) {
				this->stopRobotMove();
				this->neutralizeArms(evt.time());

				m_state = 105;
			}
			break;
		}
		case 105: {  // fix robot direction for grasping
			if(evt.time() >= m_time1) m_robotObject->setJointVelocity("RARM_JOINT1", 0.0, 0.0);
			if(evt.time() >= m_time4) m_robotObject->setJointVelocity("RARM_JOINT4", 0.0, 0.0);
			if(evt.time() >= m_time1 && evt.time() >= m_time4) {
				Vector3d l_tpos;
				if(m_task == 1)
					this->recognizeObjectPosition(l_tpos, m_trashName1);
				else
					this->recognizeObjectPosition(l_tpos, m_trashName2);
				double l_moveTime = rotateTowardObj(l_tpos);

				m_time = l_moveTime+evt.time();

				m_state = 110;
			}
			break;
		}
		case 110: {  // approach to the trash
			if(evt.time() >= m_time) {
				this->stopRobotMove();

				Vector3d l_tpos;
				
				if(m_task == 1)
					this->recognizeObjectPosition(l_tpos, m_trashName1);
				else
					this->recognizeObjectPosition(l_tpos, m_trashName2);

				double l_moveTime = goToObj(l_tpos, 30.0);
				m_time = l_moveTime+evt.time();

				m_state = 120;
			}
			break;
		}
		case 120: {  // try to grasp trash
			if(evt.time() >= m_time) {
				this->stopRobotMove();
				
				Vector3d l_tpos;

				if(m_task == 1)
					this->recognizeObjectPosition(l_tpos, m_trashName1);
				else
					this->recognizeObjectPosition(l_tpos, m_trashName2);
					
				double l_moveTime = goGraspingObject(l_tpos);
				m_time = l_moveTime+evt.time();

				m_state = 125;
			}
			break;
		}
		case 125: {
			if(evt.time() >= m_time) {
				m_robotObject->setJointVelocity("RARM_JOINT4", 0.0, 0.0);
				this->neutralizeArms(evt.time());

				m_state = 130;
			}
			break;
		}
		case 130: {
			if(evt.time() >= m_time1) m_robotObject->setJointVelocity("RARM_JOINT1", 0.0, 0.0);
			if(evt.time() >= m_time4) m_robotObject->setJointVelocity("RARM_JOINT4", 0.0, 0.0);
			if(evt.time() >= m_time1 && evt.time() >= m_time4) {

				m_robotObject->setWheelVelocity(-m_angularVelocity, -m_angularVelocity);
				m_time = 20./m_movingSpeed + evt.time();

				m_state = 150;
			}
			break;
		}
		case 150: {
			if(evt.time() >= m_time) {
				this->stopRobotMove();
				double l_moveTime;
				if(m_task == 1)
					l_moveTime = rotateTowardObj(m_frontTrashBox1);
				else
					l_moveTime = rotateTowardObj(m_frontTrashBox2);

				m_time = l_moveTime + evt.time();
				m_state = 160;
			}
			break;
		}
		case 160: {
			if(evt.time() >= m_time) {
				this->stopRobotMove();
				double l_moveTime;
				if(m_task == 1)
					l_moveTime = goToObj(m_frontTrashBox1,0.0);
				else
					l_moveTime = goToObj(m_frontTrashBox2,0.0);
				m_time = l_moveTime + evt.time();
				m_state = 161;
			}
			break;
		}
		case 161: {
			if(evt.time() >= m_time) {
				this->stopRobotMove();
				this->prepareThrowing(evt.time());

				m_state = 165;
			}
			break;
		}
		case 165: {
			if(evt.time() >= m_time1) m_robotObject->setJointVelocity("RARM_JOINT1", 0.0, 0.0);
			if(evt.time() >= m_time4) m_robotObject->setJointVelocity("RARM_JOINT4", 0.0, 0.0);
			if(evt.time() >= m_time1 && evt.time() >= m_time4) {

				Vector3d l_tpos;
				if(m_task == 1)
					this->recognizeObjectPosition(l_tpos, m_trashBoxName1);
				else
					this->recognizeObjectPosition(l_tpos, m_trashBoxName2);
				double l_moveTime = rotateTowardObj(l_tpos);
				m_time = l_moveTime + evt.time();

				m_state = 170;
			}
			break;
		}
		case 170: {
			if(evt.time() >= m_time) {

				this->stopRobotMove();
				Vector3d l_tpos;
				if(m_task == 1)
					this->recognizeObjectPosition(l_tpos, m_trashBoxName1);
				else
					this->recognizeObjectPosition(l_tpos, m_trashBoxName2);
				double l_moveTime = goToObj(l_tpos, 50.0);
				m_time = l_moveTime + evt.time();

				m_state = 180;
			}
			break;
		}
		case 180: {
			if(evt.time() >= m_time) {
				this->stopRobotMove();
				Vector3d l_tpos;
				if(m_task == 1)
					this->recognizeObjectPosition(l_tpos, m_trashBoxName1);
				else
					this->recognizeObjectPosition(l_tpos, m_trashBoxName2);
				double l_moveTime = rotateTowardObj(l_tpos);
				m_time = l_moveTime + evt.time();

				m_state = 200;
			}
			break;
		}
		case 200: {  // throw trash and get back a bit
			if(evt.time() >= m_time) {
				this->stopRobotMove();
				this->throwTrash();

				sleep(1);

				m_robotObject->setWheelVelocity(-m_angularVelocity, -m_angularVelocity);
				m_time = 50.0/m_movingSpeed + evt.time();

				m_state = 225;
			}
			break;
		}
		case 225: {  // recover robot arms
			if(evt.time() >= m_time) {
				this->stopRobotMove();
				this->neutralizeArms(evt.time());

				m_state = 240;
			}
			break;
		}
		case 240: {  // go next
			if(evt.time() >= m_time1) m_robotObject->setJointVelocity("RARM_JOINT1", 0.0, 0.0);
			if(evt.time() >= m_time4) m_robotObject->setJointVelocity("RARM_JOINT4", 0.0, 0.0);
			if(evt.time() >= m_time1 && evt.time() >= m_time4) {
				this->stopRobotMove();

				broadcastMsg("Task_finished");
				//broadcastMsg("Give_up");
				m_state = 0;
			}
			break;
		}

	}
	return refreshRateOnAction;
}