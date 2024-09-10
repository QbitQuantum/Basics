void EmberEntity::accept(std::function<bool(const EmberEntity&)>& visitor) const
{
	if (visitor(*this)) {
		for (unsigned int i = 0; i < numContained(); ++i) {
			EmberEntity* entity = getEmberContained(i);
			if (entity) {
				entity->accept(visitor);
			}
		}
	}
}