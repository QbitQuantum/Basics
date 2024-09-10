void
MAST::EigenproblemAssembly::assemble() {
    
    libMesh::EigenSystem& eigen_sys =
    dynamic_cast<libMesh::EigenSystem&>(_system->system());
    
    // zero the solution since it is not needed for eigenproblem
    eigen_sys.solution->zero();
    
    libMesh::SparseMatrix<Real>&  matrix_A =
    *(dynamic_cast<libMesh::EigenSystem&>(_system->system()).matrix_A);
    libMesh::SparseMatrix<Real>&  matrix_B =
    *(dynamic_cast<libMesh::EigenSystem&>(_system->system()).matrix_B);
    
    matrix_A.zero();
    matrix_B.zero();
    
    // iterate over each element, initialize it and get the relevant
    // analysis quantities
    RealVectorX sol;
    RealMatrixX mat_A, mat_B;
    std::vector<libMesh::dof_id_type> dof_indices;
    const libMesh::DofMap& dof_map = eigen_sys.get_dof_map();
    std::auto_ptr<MAST::ElementBase> physics_elem;
    
    libMesh::MeshBase::const_element_iterator       el     =
    eigen_sys.get_mesh().active_local_elements_begin();
    const libMesh::MeshBase::const_element_iterator end_el =
    eigen_sys.get_mesh().active_local_elements_end();
    
    for ( ; el != end_el; ++el) {
        
        const libMesh::Elem* elem = *el;
        
        dof_map.dof_indices (elem, dof_indices);
        
        physics_elem.reset(_build_elem(*elem).release());
        
        // get the solution
        unsigned int ndofs = (unsigned int)dof_indices.size();
        sol.setZero(ndofs);
        mat_A.setZero(ndofs, ndofs);
        mat_B.setZero(ndofs, ndofs);
        
        // if the base solution is provided, then tell the element about it
        if (_base_sol.get()) {
            for (unsigned int i=0; i<dof_indices.size(); i++)
                sol(i) = (*_base_sol)(dof_indices[i]);
        }
        
        physics_elem->set_solution(sol);
        
        _elem_calculations(*physics_elem, mat_A, mat_B);

        // copy to the libMesh matrix for further processing
        DenseRealMatrix A, B;
        MAST::copy(A, mat_A);
        MAST::copy(B, mat_B);

        // constrain the element matrices.
        eigen_sys.get_dof_map().constrain_element_matrix(A, dof_indices);
        eigen_sys.get_dof_map().constrain_element_matrix(B, dof_indices);
        
        // add to the global matrices
        if (_if_exchange_A_and_B_matrices)
        {
            matrix_A.add_matrix (B, dof_indices); // load dependent
            matrix_B.add_matrix (A, dof_indices); // load independent
        }
        else
        {
            matrix_A.add_matrix (A, dof_indices); // load independent
            matrix_B.add_matrix (B, dof_indices); // load dependent
        }
    }
    
    
}