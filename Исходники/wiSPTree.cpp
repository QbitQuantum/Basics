void wiSPTree::getVisible(Node* node, AABB& frustum, CulledList& objects, int type){
	if(!node) return;
	int contain_type = frustum.intersects(node->box);
	if(!contain_type) 
		return;
	else{
		for(Cullable* object : node->objects)
			if(
				type==SP_TREE_LOOSE_CULL || 
				(type==SP_TREE_STRICT_CULL &&
					contain_type==AABB::INSIDE ||
					(contain_type==INTERSECTS && frustum.intersects(object->bounds))
				)
			){
				//object->lastSquaredDistMulThousand=(long)(wiMath::DistanceEstimated(object->bounds.getCenter(),frustum.getCenter())*1000);
				objects.insert(object);
			}
		if(node->count){
			for (unsigned int i = 0; i<node->children.size(); ++i)
				getVisible(node->children[i],frustum,objects,type);
		}
	}
}