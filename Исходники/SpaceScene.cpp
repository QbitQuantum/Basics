void SpaceScene::Tick(float deltaTime) {
	camera->Update(deltaTime);
	canvas->Update(deltaTime);

	//Simulate gravity
	for (std::unique_ptr<CelestialBody>& source : universe->bodies) {
		//Apply the bodies force of gravity to other bodies
		for (std::unique_ptr<CelestialBody>& target : universe->bodies) {
			if (source == target) continue;

			Vector3 displacement = (target->position - source->position);
			float length = displacement.Length();
			float r2 = length * length;
			float totalMass = (source->data.mass + target->data.mass);

			float magnitude = (universe->G * (totalMass / r2));

			Vector3 force(-magnitude, 0, 0);
			force = force * displacement.Normalize();

			Vector3 velocity = (force / target->data.mass, 0, 0);
			target->position += (velocity * deltaTime);
		}
		//Apply the bodies linear velocity
		source->position += (source->linearVelocity * deltaTime);
	}
}