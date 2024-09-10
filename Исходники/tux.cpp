bool CCharShape::VisibleNode (int node_name, float level) {
    TCharNode *node;
    if (GetNode (node_name, &node) == false) return false;

	node->visible = (level > 0);

	if (node->visible) {
    	node->divisions = 
			MIN (MAX_SPHERE_DIV, MAX (MIN_SPHERE_DIV, 
			ROUND_TO_NEAREST (param.tux_sphere_divisions * level / 10)));
	    node->radius = 1.0;
	} 
	if (newActions && useActions) AddAction (node_name, 5, NullVec, level);
	return true;
}