	void addParkingSpaces(Vec2f from, Vec2f direction, size_t count, bool entryFromLeft = true, float width = 30.f, float length = 75.f) {
		direction.normalize();
		Vec2f entryVec = direction;
		entryVec.rotate(static_cast<float>(entryFromLeft ? M_PI / 2.f : -M_PI / 2.f));

		for (size_t i = 0; i < count; ++i) {			
			addSingleParkingSpace(ParkingSpace(width, length, from, entryVec));
			from += direction * width;
		}
	}