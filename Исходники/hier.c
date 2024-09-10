const char*
create_sphere_node(const char *parent_name, const char *child_name, scalar_t resolution ) 
{
    scene_node_t *node;
    char *msg;

    msg = create_scene_node(parent_name, child_name, &node);
    if ( msg != NULL ) {
        return msg;
    } 

    node->geom = Sphere;
    node->param.sphere.radius = 1.0;

#ifdef __APPLE__
    node->param.sphere.resolution = resolution;
#else
    node->param.sphere.divisions = min( 
	MAX_SPHERE_DIVISIONS, max( 
	    MIN_SPHERE_DIVISIONS, 
	    ROUND_TO_NEAREST( getparam_tux_sphere_divisions() * resolution ) 
	    ) );
#endif

    return NULL;
}