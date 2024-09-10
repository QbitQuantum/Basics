int BroadPhase2DBasic::cull_aabb(const Rect2 &p_aabb, CollisionObject2DSW **p_results, int p_max_results, int *p_result_indices) {

	int rc = 0;

	for (Map<ID, Element>::Element *E = element_map.front(); E; E = E->next()) {

		const Rect2 aabb = E->get().aabb;
		if (aabb.intersects(p_aabb)) {

			p_results[rc] = E->get().owner;
			p_result_indices[rc] = E->get().subindex;
			rc++;
			if (rc >= p_max_results)
				break;
		}
	}

	return rc;
}