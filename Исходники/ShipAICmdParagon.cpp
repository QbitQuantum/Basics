void AIParagonCmdSteerAround::CalculateEntryPoint()
{
	// Entry point
	if (m_data.ship_to_sbody_distance > m_data.sbody_transit_radius + 5000.0
		&& m_data.ship_to_sbody_distance <= m_data.sbody_transit_radius + 10000.0)
	{
		// - Ship is in transit range or nearby
		// --	Directly above or below to transit range is the entry point (Default)
		m_entryPoint = -m_data.ship_to_sbody_dir * m_data.sbody_transit_radius;
		m_stage = ESS_ENTER;
	} else if (m_data.ship_to_sbody_distance > m_data.sbody_transit_radius + 10000.0) {
		// - Ship is far from transit range
		vector3d intersection_point;
		bool intersection;
		// --	Calculate entry point
		if (m_data.target_to_sbody_distance > m_data.sbody_transit_radius) {
			// -- Target out of planet (WIP)
			// Ship takes a wide angle turn around the planet
			const double angle = DEG2RAD(45.0);
			const double ship_to_entry_distance = sqrt(2.0 * pow(m_data.ship_to_sbody_distance, 2));
			vector3d ship_up = m_ship->GetOrientRelTo(m_data.sframe).VectorY();
			
			// Get direction from ship to nearest entry point on planet hemisphere circular edge

			const vector3d ship_to_entry_dir =
				m_data.ship_to_sbody_dir * matrix4x4d::RotateMatrix(angle, ship_up.x, ship_up.y, ship_up.z);
			m_entryPoint = m_data.ship_pos + (ship_to_entry_dir * ship_to_entry_distance);

			// Planet could intersect path, in which case intersection point is the entry point
			if (LineSphereIntersection(m_data.sbody_pos, m_data.sbody_transit_radius,
				m_data.ship_pos, m_entryPoint, intersection_point)) {
				m_entryPoint = intersection_point;
			}
			m_stage = ESS_ENTER;
		} else {
			// -- Target in planet
			// is target in front or back hemisphere relative to ship?
			if (m_data.target_to_sbody_distance <= DESTINATION_RADIUS ||				
				-m_data.ship_to_sbody_dir.Dot(-m_data.target_to_sbody_dir) >= 0.0) {
				// Front hemisphere
				// Calculate location at which ship will enter transit-around heading towards target
				intersection = LineSphereIntersection(m_data.sbody_pos, m_data.sbody_transit_radius, 
					m_data.ship_pos, m_data.target_to_transit, intersection_point);
				assert(intersection);	// There should always be an intersection otherwise this code path would not run
										// If this exception is hit, it means there is a problem with the code that determines obstacles
				m_entryPoint = intersection_point;
				m_stage = ESS_ENTER;
			} else {
				// Back hemisphere
				// Enter point is the point that is exactly at 90 degrees planet-transit-radius from ship
				// If ship intersects radius before it reaches entry point then intersection point is the entry point
				const double angle = atan2(m_data.ship_to_sbody_distance, m_data.sbody_transit_radius);
				const double ship_to_entry_distance = sqrt(pow(m_data.ship_to_sbody_distance, 2) +
					pow(m_data.sbody_transit_radius, 2));
				const vector3d ship_up = m_ship->GetOrientRelTo(m_data.sframe).VectorY();

				// Get direction from ship to nearest entry point on planet hemisphere-edge
				// Note that entry point can be set anywhere around the planet's diameter from the ship's perspective
				vector3d sbody_to_target = -m_data.target_to_sbody_dir;
				sbody_to_target = sbody_to_target / ship_up.Dot(sbody_to_target);
				vector3d ship_to_entry_dir = (sbody_to_target - ship_up).Normalized();
				m_entryPoint = m_data.ship_pos + (ship_to_entry_dir * ship_to_entry_distance);

				// Planet could intersect path, in which case intersection point is the entry point
				if (LineSphereIntersection(m_data.sbody_pos, m_data.sbody_transit_radius,
					m_data.ship_pos, m_entryPoint, intersection_point)) {
					m_entryPoint = intersection_point;
				}
				m_stage = ESS_ENTER;
			}
		}
	} else {
		// --	Ship is already at entry point
		m_entryPoint = m_data.ship_pos;
		m_stage = ESS_AROUND;
	}
}