void
MAST::ComplexAssemblyBase::
residual_and_jacobian_blocked (const libMesh::NumericVector<Real>& X,
                               libMesh::NumericVector<Real>& R,
                               libMesh::SparseMatrix<Real>&  J,
                               MAST::Parameter* p) {

    libmesh_assert(_system);
    libmesh_assert(_discipline);
    libmesh_assert(_elem_ops);

    START_LOG("residual_and_jacobian()", "ComplexSolve");
    
    MAST::NonlinearSystem& nonlin_sys = _system->system();
    
    R.zero();
    J.zero();
    
    // iterate over each element, initialize it and get the relevant
    // analysis quantities
    RealVectorX
    sol;
    ComplexVectorX
    delta_sol,
    vec;
    ComplexMatrixX
    mat,
    dummy;

    // get the petsc vector and matrix objects
    Mat
    jac_bmat = dynamic_cast<libMesh::PetscMatrix<Real>&>(J).mat();
    
    PetscInt ierr;
    
    std::vector<libMesh::dof_id_type> dof_indices;
    const libMesh::DofMap& dof_map = nonlin_sys.get_dof_map();
    const std::vector<libMesh::dof_id_type>&
    send_list = nonlin_sys.get_dof_map().get_send_list();
    
    
    
    std::unique_ptr<libMesh::NumericVector<Real> >
    localized_base_solution,
    localized_complex_sol(libMesh::NumericVector<Real>::build(nonlin_sys.comm()).release());
    
    // prepare a send list for localization of the complex solution
    std::vector<libMesh::dof_id_type>
    complex_send_list(2*send_list.size());
    
    for (unsigned int i=0; i<send_list.size(); i++) {
        complex_send_list[2*i  ] = 2*send_list[i];
        complex_send_list[2*i+1] = 2*send_list[i]+1;
    }

    localized_complex_sol->init(2*nonlin_sys.n_dofs(),
                                2*nonlin_sys.n_local_dofs(),
                                complex_send_list,
                                false,
                                libMesh::GHOSTED);
    X.localize(*localized_complex_sol, complex_send_list);
    
    // localize the base solution, if it was provided
    if (_base_sol)
        localized_base_solution.reset(build_localized_vector(nonlin_sys,
                                                             *_base_sol).release());
    
    

    // if a solution function is attached, initialize it
    //if (_sol_function)
    //    _sol_function->init( X);
    
    
    libMesh::MeshBase::const_element_iterator       el     =
    nonlin_sys.get_mesh().active_local_elements_begin();
    const libMesh::MeshBase::const_element_iterator end_el =
    nonlin_sys.get_mesh().active_local_elements_end();
    
    MAST::ComplexAssemblyElemOperations&
    ops = dynamic_cast<MAST::ComplexAssemblyElemOperations&>(*_elem_ops);

    for ( ; el != end_el; ++el) {
        
        const libMesh::Elem* elem = *el;
        
        dof_map.dof_indices (elem, dof_indices);
        
        ops.init(*elem);
        
        // get the solution
        unsigned int ndofs = (unsigned int)dof_indices.size();
        sol.setZero(ndofs);
        delta_sol.setZero(ndofs);
        vec.setZero(ndofs);
        mat.setZero(ndofs, ndofs);
        
        // first set the velocity to be zero
        ops.set_elem_velocity(sol);
        
        // next, set the base solution, if provided
        if (_base_sol)
            for (unsigned int i=0; i<dof_indices.size(); i++)
                sol(i) = (*localized_base_solution)(dof_indices[i]);
        
        ops.set_elem_solution(sol);
        
        // set the value of the small-disturbance solution
        for (unsigned int i=0; i<dof_indices.size(); i++) {
            
            // get the complex block for this dof
            delta_sol(i) = Complex((*localized_complex_sol)(2*dof_indices[i]),
                                   (*localized_complex_sol)(2*dof_indices[i]+1));
        }
        
        ops.set_elem_complex_solution(delta_sol);
        
        
//        if (_sol_function)
//            physics_elem->attach_active_solution_function(*_sol_function);
        
        
        // perform the element level calculations
        ops.elem_calculations(true, vec, mat);
        
        // if sensitivity was requested, then ask the element for sensitivity
        // of the residual
        if (p) {
            
            // set the sensitivity of complex sol to zero
            delta_sol.setZero();
            ops.set_elem_complex_solution_sensitivity(delta_sol);
            vec.setZero();
            ops.elem_sensitivity_calculations(*p, vec);
        }
        
        ops.clear_elem();

        //physics_elem->detach_active_solution_function();
        
        // extract the real or the imaginary part of the matrix/vector
        //  The complex system of equations
        //     (J_R + i J_I) (x_R + i x_I) + (r_R + i r_I) = 0
        //  is rewritten as
        //     [ J_R   -J_I] {x_R}  +  {r_R}  = {0}
        //     [ J_I    J_R] {x_I}  +  {r_I}  = {0}
        //
        DenseRealVector v_R, v_I;
        DenseRealMatrix m_R, m_I1, m_I2;
        std::vector<Real> vals(4);
        
        // copy the real part of the residual and Jacobian
        MAST::copy( m_R, mat.real());
        MAST::copy(m_I1, mat.imag()); m_I1 *= -1.;   // this is the -J_I component
        MAST::copy(m_I2, mat.imag());                // this is the J_I component
        MAST::copy( v_R, vec.real());
        MAST::copy( v_I, vec.imag());
        dof_map.constrain_element_matrix(m_R,  dof_indices);
        dof_map.constrain_element_matrix(m_I1, dof_indices);
        dof_map.constrain_element_matrix(m_I2, dof_indices);
        dof_map.constrain_element_vector(v_R,  dof_indices);
        dof_map.constrain_element_vector(v_I,  dof_indices);
        
        
        for (unsigned int i=0; i<dof_indices.size(); i++) {
            
            R.add(2*dof_indices[i],     v_R(i));
            R.add(2*dof_indices[i]+1,   v_I(i));
            
            for (unsigned int j=0; j<dof_indices.size(); j++) {
                vals[0] = m_R (i,j);
                vals[1] = m_I1(i,j);
                vals[2] = m_I2(i,j);
                vals[3] = m_R (i,j);
                ierr = MatSetValuesBlocked(jac_bmat,
                                           1, (PetscInt*)&dof_indices[i],
                                           1, (PetscInt*)&dof_indices[j],
                                           &vals[0],
                                           ADD_VALUES);
            }
        }
    }
    
    
    // if a solution function is attached, clear it
    //if (_sol_function)
    //    _sol_function->clear();
    
    R.close();
    J.close();
    
    libMesh::out << "R: " << R.l2_norm() << std::endl;
    STOP_LOG("residual_and_jacobian()", "ComplexSolve");
}