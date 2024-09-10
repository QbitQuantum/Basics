void SpaceStation::DockingUpdate(const double timeStep)
{
	vector3d p1, p2, zaxis;
	for (Uint32 i=0; i<m_shipDocking.size(); i++) {
		shipDocking_t &dt = m_shipDocking[i];
		if (!dt.ship) continue;
		// docked stage is m_type->NumDockingPorts() + 1 => ship docked
		if (dt.stage > m_type->NumDockingStages()) continue;

		double stageDuration = (dt.stage > 0 ?
				m_type->GetDockAnimStageDuration(dt.stage-1) :
				m_type->GetUndockAnimStageDuration(abs(dt.stage)-1));
		dt.stagePos += timeStep / stageDuration;

		if (dt.stage == 1) {
			// SPECIAL stage! Docking granted but waiting for ship to dock

			m_doorAnimationStep = 0.3; // open door

			if (dt.stagePos >= 1.0) {
				if (dt.ship == Pi::player)
					Pi::game->log->Add(GetLabel(), Lang::DOCKING_CLEARANCE_EXPIRED);
				dt.ship = 0;
				dt.stage = 0;
				m_doorAnimationStep = -0.3; // close door
			}
			continue;
		}

		if (dt.stagePos > 1.0) {
			// use end position of last segment for start position of new segment
			SpaceStationType::positionOrient_t dport;
			PiVerify(m_type->GetDockAnimPositionOrient(i, dt.stage, 1.0f, dt.fromPos, dport, dt.ship));
			matrix3x3d fromRot = matrix3x3d::FromVectors(dport.xaxis, dport.yaxis, dport.zaxis);
			dt.fromRot = Quaterniond::FromMatrix3x3(fromRot);
			dt.fromPos = dport.pos;

			// transition between docking stages
			dt.stagePos = 0;
			if (dt.stage >= 0) dt.stage++;
			else dt.stage--;
		}

		if (dt.stage < -m_type->ShipLaunchStage() && dt.ship->GetFlightState() != Ship::FLYING) {
			// launch ship
			dt.ship->SetFlightState(Ship::FLYING);
			dt.ship->SetAngVelocity(GetAngVelocity());
			if (m_type->IsSurfaceStation()) {
				dt.ship->SetThrusterState(1, 1.0);	// up
			} else {
				dt.ship->SetThrusterState(2, -1.0);	// forward
			}
			LuaEvent::Queue("onShipUndocked", dt.ship, this);
		}
		if (dt.stage < -m_type->NumUndockStages()) {
			// undock animation finished, clear port
			dt.stage = 0;
			dt.ship = 0;
			LockPort(i, false);
			m_doorAnimationStep = -0.3; // close door
		}
		else if (dt.stage > m_type->NumDockingStages()) {
			// set docked
			dt.ship->SetDockedWith(this, i);
			LuaEvent::Queue("onShipDocked", dt.ship, this);
			LockPort(i, false);
			m_doorAnimationStep = -0.3; // close door
		}
	}

	m_doorAnimationState = Clamp(m_doorAnimationState + m_doorAnimationStep*timeStep, 0.0, 1.0);
	if (m_doorAnimation)
		m_doorAnimation->SetProgress(m_doorAnimationState);
}