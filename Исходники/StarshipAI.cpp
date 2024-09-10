void
StarshipAI::FireControl()
{
	// identify unknown contacts:
	if (identify) {
		if (fabs(ship->GetHelmHeading() - ship->CompassHeading()) < 10*DEGREES) {
			Contact* contact = ship->FindContact(target);

			if (contact && !contact->ActLock()) {
				if (!ship->GetProbe()) {
					ship->LaunchProbe();
				}
			}
		}

		return;
	}

	// investigate last known location of enemy ship:
	if (rumor && !target && ship->GetProbeLauncher() && !ship->GetProbe()) {
		// is rumor in basket?
		Point rmr = Transform(rumor->Location());
		rmr.Normalize();

		double dx = fabs(rmr.x);
		double dy = fabs(rmr.y);

		if (dx < 10*DEGREES && dy < 10*DEGREES && rmr.z > 0) {
			ship->LaunchProbe();
		}
	}

	// Corvettes and Frigates are anti-air platforms.  They need to
	// target missile threats even when the threat is aimed at another
	// friendly ship.  Forward facing weapons must be on auto fire,
	// while lateral and aft facing weapons are set to point defense.

	if (ship->Class() == Ship::CORVETTE || ship->Class() == Ship::FRIGATE) {
		ListIter<WeaponGroup> iter = ship->Weapons();
		while (++iter) {
			WeaponGroup* group = iter.value();

			ListIter<Weapon> w_iter = group->GetWeapons();
			while (++w_iter) {
				Weapon* weapon = w_iter.value();

				double az = weapon->GetAzimuth();
				if (fabs(az) < 45*DEGREES) {
					weapon->SetFiringOrders(Weapon::AUTO);
					weapon->SetTarget(target, 0);
				}

				else {
					weapon->SetFiringOrders(Weapon::POINT_DEFENSE);
				}
			}
		}
	}

	// All other starships are free to engage ship targets.  Weapon
	// fire control is managed by the type of weapon.

	else {
		System* subtgt = SelectSubtarget();

		ListIter<WeaponGroup> iter = ship->Weapons();
		while (++iter) {
			WeaponGroup* weapon = iter.value();

			if (weapon->GetDesign()->target_type & Ship::DROPSHIPS) {   // anti-air weapon?
				weapon->SetFiringOrders(Weapon::POINT_DEFENSE);
			}
			else if (weapon->IsDrone()) {                               // torpedoes
				weapon->SetFiringOrders(Weapon::MANUAL);
				weapon->SetTarget(target, 0);

				if (target && target->GetRegion() == ship->GetRegion()) {
					Point  delta = target->Location() - ship->Location();
					double range = delta.length();

					if (range < weapon->GetDesign()->max_range * 0.9 && 
							!AssessTargetPointDefense())
					weapon->SetFiringOrders(Weapon::AUTO);

					else if (range < weapon->GetDesign()->max_range * 0.5)
					weapon->SetFiringOrders(Weapon::AUTO);
				}
			}
			else {                                                      // anti-ship weapon
				weapon->SetFiringOrders(Weapon::AUTO);
				weapon->SetTarget(target, subtgt);
				weapon->SetSweep(subtgt ? Weapon::SWEEP_NONE : Weapon::SWEEP_TIGHT);
			}
		}
	}
}