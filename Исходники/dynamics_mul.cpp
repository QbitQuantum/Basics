double dynamics_mul::get_curvature(dsc_obj *obj, HMesh::Walker hew0){
    // Find next edge on the boundary
    auto hew1 = hew0.next().opp();
    while (1) {
        if (s_dsc->is_interface(hew1.halfedge())) {
            hew1 = hew1.opp();
            break;
        }
        
        hew1 = hew1.next().opp();
    }
    
    Vec2 p0 = obj->get_pos(hew0.vertex()) - obj->get_pos(hew0.opp().vertex());
    Vec2 p1 = obj->get_pos(hew1.vertex()) - obj->get_pos(hew1.opp().vertex());
    
    Vec2 norm0(p0[1], -p0[0]); norm0.normalize();
    Vec2 norm1(p1[1], -p1[0]); norm1.normalize();
    Vec2 norm = norm0 + norm1; norm.normalize();
    
    
    double l0 = p0.length();
    double l1 = p1.length();
    double angle = std::atan2(CGLA::cross(p0, p1), DSC2D::Util::dot(p0, p1));
    double curvature = angle / (l0/2.0 + l1/2.0);
    
    return curvature;
}