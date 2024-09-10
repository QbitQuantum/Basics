void
create_sphere_node(const std::string& parent_name, const std::string& child_name, float resolution ) 
{
    SceneNode *node;

    create_scene_node(parent_name, child_name, &node);

    node->isSphere = true;
    node->sphere.radius = 1.0;
    node->sphere.divisions = MIN( 
	MAX_SPHERE_DIVISIONS, MAX( 
	    MIN_SPHERE_DIVISIONS, 
	    ROUND_TO_NEAREST(PPConfig.getInt("tux_sphere_divisions") * resolution ) 
	    ) );
	node->sphere.resolution = resolution;
}