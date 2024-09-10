Math::Vector3d Command::getObjectPosition(const ResourceReference &targetRef, int32 *floorFace) {
	Object *target = targetRef.resolve<Object>();
	Floor *floor = StarkGlobal->getCurrent()->getFloor();

	Math::Vector3d position;
	switch (target->getType().get()) {
		case Type::kBookmark: {
			Bookmark *bookmark = Object::cast<Bookmark>(target);
			position = bookmark->getPosition();

			if (floorFace) {
				*floorFace = floor->findFaceContainingPoint(position);
			}

	        break;
		}
		case Type::kItem: {
			FloorPositionedItem *item = Object::cast<FloorPositionedItem>(target);
			position = item->getPosition3D();

			if (floorFace) {
				*floorFace = item->getFloorFaceIndex();
			}

			break;
		}
		case Type::kPath: {
			assert(target->getSubType() == Path::kPath3D);

			Path3D *path = Object::cast<Path3D>(target);
			position = path->getVertexPosition3D(0, floorFace);

			break;
		}
		default:
			warning("Unimplemented getObjectPosition target type %s", target->getType().getName());
	}

	return position;
}