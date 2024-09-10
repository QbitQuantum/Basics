rigid_body_t::pointer boingRbCmd::getPointerFromName(MString &name)
{
    
    rigid_body_t::pointer rb = 0;
    
    shared_ptr<solver_impl_t> solv = solver_t::get_solver();
    std::set<rigid_body_t::pointer> rbds = solver_t::get_rigid_bodies();
    shared_ptr<bSolverNode> b_solv = bSolverNode::get_bsolver_node();
    MStringArray names = b_solv->get_all_keys();
    for( int i=0; i<names.length(); i++) {
        bSolverNode::m_custom_data * data = b_solv->getdata(names[i]);
        if (NULL != data) {
            if (name == data->name) {
                rb = data->m_rigid_body;
                break;
            }
        } 
    }
    
    return rb;
}