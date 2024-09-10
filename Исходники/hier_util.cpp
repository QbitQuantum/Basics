void traverse_dag_sub( scene_node_t *node, material_t *mat )
{
    scene_node_t *child;
    glm::mat4 matrix;
    int i,j;
    
    check_assertion( node != NULL, "node is NULL" );
    hier_push_mat();
    
    for( i = 0; i < 4; i++ )
    {
        for( j = 0; j < 4; j++ )
            matrix[i][j] = node->trans[i][j];
    }
    hier_mult_mat(matrix);
    
    if ( node->mat != NULL ) {
        mat = node->mat;
    }
    
    if ( node->geom == Sphere ) {
        
        //FIXME
        draw_sphere(std::min(MAX_SPHERE_DIVISIONS, std::max(MIN_SPHERE_DIVISIONS, ROUND_TO_NEAREST(node->param.sphere.divisions))), mat);
    }
    
    child = node->child;
    while (child != NULL) {
        traverse_dag_sub( child, mat );
        child = child->next;
    }
    
    hier_pop_mat();
}