bool Physics2DDirectSpaceStateSW::intersect_ray(const Vector2& p_from, const Vector2& p_to,RayResult &r_result,const Set<RID>& p_exclude,uint32_t p_layer_mask,uint32_t p_object_type_mask) {



    ERR_FAIL_COND_V(space->locked,false);

    Vector2 begin,end;
    Vector2 normal;
    begin=p_from;
    end=p_to;
    normal=(end-begin).normalized();

    int amount = space->broadphase->cull_segment(begin,end,space->intersection_query_results,Space2DSW::INTERSECTION_QUERY_MAX,space->intersection_query_subindex_results);

    //todo, create another array tha references results, compute AABBs and check closest point to ray origin, sort, and stop evaluating results when beyond first collision

    bool collided=false;
    Vector2 res_point,res_normal;
    int res_shape;
    const CollisionObject2DSW *res_obj;
    real_t min_d=1e10;


    for(int i=0; i<amount; i++) {

        if (!_match_object_type_query(space->intersection_query_results[i],p_layer_mask,p_object_type_mask))
            continue;

        if (p_exclude.has( space->intersection_query_results[i]->get_self()))
            continue;

        const CollisionObject2DSW *col_obj=space->intersection_query_results[i];

        int shape_idx=space->intersection_query_subindex_results[i];
        Matrix32 inv_xform = col_obj->get_shape_inv_transform(shape_idx) * col_obj->get_inv_transform();

        Vector2 local_from = inv_xform.xform(begin);
        Vector2 local_to = inv_xform.xform(end);

        /*local_from = col_obj->get_inv_transform().xform(begin);
        local_from = col_obj->get_shape_inv_transform(shape_idx).xform(local_from);

        local_to = col_obj->get_inv_transform().xform(end);
        local_to = col_obj->get_shape_inv_transform(shape_idx).xform(local_to);*/

        const Shape2DSW *shape = col_obj->get_shape(shape_idx);

        Vector2 shape_point,shape_normal;


        if (shape->intersect_segment(local_from,local_to,shape_point,shape_normal)) {



            Matrix32 xform = col_obj->get_transform() * col_obj->get_shape_transform(shape_idx);
            shape_point=xform.xform(shape_point);

            real_t ld = normal.dot(shape_point);


            if (ld<min_d) {

                min_d=ld;
                res_point=shape_point;
                res_normal=inv_xform.basis_xform_inv(shape_normal).normalized();
                res_shape=shape_idx;
                res_obj=col_obj;
                collided=true;
            }
        }

    }

    if (!collided)
        return false;


    r_result.collider_id=res_obj->get_instance_id();
    if (r_result.collider_id!=0)
        r_result.collider=ObjectDB::get_instance(r_result.collider_id);
    r_result.normal=res_normal;
    r_result.metadata=res_obj->get_shape_metadata(res_shape);
    r_result.position=res_point;
    r_result.rid=res_obj->get_self();
    r_result.shape=res_shape;

    return true;

}