void
MAST::NoniterativeUGFlutterSolver::calculate_sensitivity(MAST::FlutterRootBase& root,
                                                         const libMesh::ParameterVector& params,
                                                         const unsigned int i) {
    // make sure that the aero_structural_model is a valid pointer
    libmesh_assert(aero_structural_model);
    
    libMesh::out
    << " ====================================================" << std::endl
    << "UG Sensitivity Solution" << std::endl
    << "   k_red = " << std::setw(10) << root.k_red << std::endl
    << "   V_ref = " << std::setw(10) << root.V << std::endl;
    
    Complex eig = root.root, sens = 0., k_sens = 0., vref_sens = 0., den = 0.;
    
    // matrix to store the sensitivity of constraint wrt kref and vref
    // first row is constraint  f1(k,v) = g = im(lambda)/re(lambda) = 0
    // second row is constraint f2(k,v) = vref*sqrt(re(lambda))-1.  = 0
    RealMatrixX jac;
    
    // residual vector for the sensitivity problem, and total derivative vec
    // first row is for constraint f1(k,v)
    // first row is for constraint f2(k,v)
    RealVectorX res, dsens;
    jac.setZero(2,2);
    res.setZero(2);
    
    // get the sensitivity of the matrices
    ComplexMatrixX mat_A, mat_B, mat_A_sens, mat_B_sens;
    ComplexVectorX v;
    
    // initialize the baseline matrices
    initialize_matrices(root.k_red_ref, root.V_ref, mat_A, mat_B);
    
    // calculate the eigenproblem sensitivity
    initialize_matrix_sensitivity_for_param(params, i,
                                            root.k_red_ref,
                                            root.V_ref,
                                            mat_A_sens,
                                            mat_B_sens);
    
    // the eigenproblem is     A x - lambda B x = 0
    // therefore, the denominator is obtained from the inner product of
    // x^T B x
    // sensitivity is
    //   -dlambda/dp x^T B x = - x^T (dA/dp - lambda dB/dp)
    // or
    //   dlambda/dp = [x^T (dA/dp - lambda dB/dp)]/(x^T B x)
    
    // now calculate the quotient for sensitivity
    // numerator =  ( dA/dp - lambda dB/dp)
    mat_B_sens *= -eig;
    mat_B_sens += mat_A_sens;
    v = mat_B_sens*root.eig_vec_right;
    den = root.eig_vec_left.dot(mat_B*root.eig_vec_right);
    sens = root.eig_vec_left.dot(v)/den;
    
    // sensitivity of f1(k,v) = im(lambda)/re(lambda) = 0
    res(0) =
    sens.imag()/eig.real() - eig.imag()/pow(eig.real(),2) * sens.real();
    // sensitivity of f2(k,v) = vref*sqrt(real(lambda)) - 1 = 0
    res(1) = root.V_ref*0.5*pow(eig.real(),-0.5)*sens.real();
    
    
    // next we need the sensitivity of k_red before we can calculate
    // the sensitivity of flutter eigenvalue
    initialize_matrix_sensitivity_for_reduced_freq(root.k_red_ref,
                                                   root.V_ref,
                                                   mat_A_sens,
                                                   mat_B_sens);
    
    // now calculate the quotient for sensitivity wrt k_red
    // calculate numerator
    mat_B_sens *= -eig;
    mat_B_sens += mat_A_sens;
    v = mat_B_sens*root.eig_vec_right;
    k_sens = root.eig_vec_left.dot(v) / den;
    
    // use this to calculate the partial derivative of f1 wrt k_red
    jac(0,0) =
    k_sens.imag()/eig.real() - eig.imag()/pow(eig.real(),2)*k_sens.real();
    jac(1,0) = root.V_ref*0.5*pow(eig.real(),-0.5)*k_sens.real();
    
    
    // next we need the sensitivity of Vref constraint before we can calculate
    // the sensitivity of flutter eigenvalue
    initialize_matrix_sensitivity_for_V_ref(root.k_red_ref,
                                            root.V_ref,
                                            mat_A_sens,
                                            mat_B_sens);
    
    // now calculate the quotient for sensitivity wrt k_red
    // calculate numerator
    mat_B_sens *= -eig;
    mat_B_sens += mat_A_sens;
    v = mat_B_sens*root.eig_vec_right;
    vref_sens = root.eig_vec_left.dot(v) / den;
    
    // use this to calculate the partial derivative of f2 wrt vref
    jac(0,1) =
    vref_sens.imag()/eig.real() - eig.imag()/pow(eig.real(),2)*vref_sens.real();
    jac(1,1) =
    sqrt(eig.real()) + root.V_ref*0.5*pow(eig.real(),-0.5)*vref_sens.real();

    // now invert the Jacobian to calculate the sensitivity
    dsens = -jac.inverse()*res;
    
    // finally add the correction to the flutter sensitivity
    sens += k_sens * dsens(0) + vref_sens * dsens(1);
    
    // set value in the return root
    root.has_sensitivity_data = true;
    root.root_sens  = sens;
    root.V_sens     = -.5*sens.real()/pow(eig.real(), 1.5);
    
    libMesh::out
    << "Finished UG Sensitivity Solution" << std::endl
    << " ====================================================" << std::endl;
    
}