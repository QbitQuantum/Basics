int BroadPhaseBasic::cull_aabb(const AABB& p_aabb,CollisionObjectSW** p_results,int p_max_results,int *p_result_indices) {

	int rc=0;

	for (Map<ID,Element>::Element *E=element_map.front();E;E=E->next()) {

		const AABB aabb=E->get().aabb;
		if (aabb.intersects(p_aabb)) {

			p_results[rc]=E->get().owner;
			p_result_indices[rc]=E->get().subindex;
			rc++;
			if (rc>=p_max_results)
				break;
		}
	}

	return rc;
}