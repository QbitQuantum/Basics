	bool BoundingCircle::isInside2D(const BoundingObject2D& bounding_obj) const {

		switch (bounding_obj.getObjectType()) {
			case BOX:
				return (
					bounding_obj.minU() <= minU() && bounding_obj.maxU() >= maxU() &&
					bounding_obj.minV() <= minV() && bounding_obj.maxV() >= maxV()
					);

			case CIRCLE:
				return (
					(position.distance(bounding_obj.centroid())+
					((const BoundingCircle&)bounding_obj).getRadius()) <= radius
					);

			default:
				break;
		}

		return false;


	}