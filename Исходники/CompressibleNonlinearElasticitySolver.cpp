void CompressibleNonlinearElasticitySolver<DIM>::AssembleOnElement(
            Element<DIM, DIM>& rElement,
            c_matrix<double, STENCIL_SIZE, STENCIL_SIZE >& rAElem,
            c_matrix<double, STENCIL_SIZE, STENCIL_SIZE >& rAElemPrecond,
            c_vector<double, STENCIL_SIZE>& rBElem,
            bool assembleResidual,
            bool assembleJacobian)
{
    static c_matrix<double,DIM,DIM> jacobian;
    static c_matrix<double,DIM,DIM> inverse_jacobian;
    double jacobian_determinant;

    this->mrQuadMesh.GetInverseJacobianForElement(rElement.GetIndex(), jacobian, jacobian_determinant, inverse_jacobian);

    if (assembleJacobian)
    {
        rAElem.clear();
        rAElemPrecond.clear();
    }

    if (assembleResidual)
    {
        rBElem.clear();
    }

    // Get the current displacement at the nodes
    static c_matrix<double,DIM,NUM_NODES_PER_ELEMENT> element_current_displacements;
    for (unsigned II=0; II<NUM_NODES_PER_ELEMENT; II++)
    {
        for (unsigned JJ=0; JJ<DIM; JJ++)
        {
            element_current_displacements(JJ,II) = this->mCurrentSolution[DIM*rElement.GetNodeGlobalIndex(II) + JJ];
        }
    }

    // Allocate memory for the basis functions values and derivative values
    static c_vector<double, NUM_VERTICES_PER_ELEMENT> linear_phi;
    static c_vector<double, NUM_NODES_PER_ELEMENT> quad_phi;
    static c_matrix<double, DIM, NUM_NODES_PER_ELEMENT> grad_quad_phi;
    static c_matrix<double, NUM_NODES_PER_ELEMENT, DIM> trans_grad_quad_phi;

    // Get the material law
    AbstractCompressibleMaterialLaw<DIM>* p_material_law
       = this->mrProblemDefinition.GetCompressibleMaterialLaw(rElement.GetIndex());


    static c_matrix<double,DIM,DIM> grad_u; // grad_u = (du_i/dX_M)

    static c_matrix<double,DIM,DIM> F;      // the deformation gradient, F = dx/dX, F_{iM} = dx_i/dX_M
    static c_matrix<double,DIM,DIM> C;      // Green deformation tensor, C = F^T F
    static c_matrix<double,DIM,DIM> inv_C;  // inverse(C)
    static c_matrix<double,DIM,DIM> inv_F;  // inverse(F)
    static c_matrix<double,DIM,DIM> T;      // Second Piola-Kirchoff stress tensor (= dW/dE = 2dW/dC)

    static c_matrix<double,DIM,DIM> F_T;    // F*T
    static c_matrix<double,DIM,NUM_NODES_PER_ELEMENT> F_T_grad_quad_phi; // F*T*grad_quad_phi

    c_vector<double,DIM> body_force;

    static FourthOrderTensor<DIM,DIM,DIM,DIM> dTdE;    // dTdE(M,N,P,Q) = dT_{MN}/dE_{PQ}
    static FourthOrderTensor<DIM,DIM,DIM,DIM> dSdF;    // dSdF(M,i,N,j) = dS_{Mi}/dF_{jN}

    static FourthOrderTensor<NUM_NODES_PER_ELEMENT,DIM,DIM,DIM> temp_tensor;
    static FourthOrderTensor<NUM_NODES_PER_ELEMENT,DIM,NUM_NODES_PER_ELEMENT,DIM> dSdF_quad_quad;

    static c_matrix<double, DIM, NUM_NODES_PER_ELEMENT> temp_matrix;
    static c_matrix<double,NUM_NODES_PER_ELEMENT,DIM> grad_quad_phi_times_invF;

    if(this->mSetComputeAverageStressPerElement)
    {
        this->mAverageStressesPerElement[rElement.GetIndex()] = zero_vector<double>(DIM*(DIM+1)/2);
    }

    // Loop over Gauss points
    for (unsigned quadrature_index=0; quadrature_index < this->mpQuadratureRule->GetNumQuadPoints(); quadrature_index++)
    {
        // This is needed by the cardiac mechanics solver
        unsigned current_quad_point_global_index =   rElement.GetIndex()*this->mpQuadratureRule->GetNumQuadPoints()
                                                   + quadrature_index;

        double wJ = jacobian_determinant * this->mpQuadratureRule->GetWeight(quadrature_index);

        const ChastePoint<DIM>& quadrature_point = this->mpQuadratureRule->rGetQuadPoint(quadrature_index);

        // Set up basis function information
        LinearBasisFunction<DIM>::ComputeBasisFunctions(quadrature_point, linear_phi);
        QuadraticBasisFunction<DIM>::ComputeBasisFunctions(quadrature_point, quad_phi);
        QuadraticBasisFunction<DIM>::ComputeTransformedBasisFunctionDerivatives(quadrature_point, inverse_jacobian, grad_quad_phi);
        trans_grad_quad_phi = trans(grad_quad_phi);

        // Get the body force, interpolating X if necessary
        if (assembleResidual)
        {
            switch (this->mrProblemDefinition.GetBodyForceType())
            {
                case FUNCTIONAL_BODY_FORCE:
                {
                    c_vector<double,DIM> X = zero_vector<double>(DIM);
                    // interpolate X (using the vertices and the /linear/ bases, as no curvilinear elements
                    for (unsigned node_index=0; node_index<NUM_VERTICES_PER_ELEMENT; node_index++)
                    {
                        X += linear_phi(node_index)*this->mrQuadMesh.GetNode( rElement.GetNodeGlobalIndex(node_index) )->rGetLocation();
                    }
                    body_force = this->mrProblemDefinition.EvaluateBodyForceFunction(X, this->mCurrentTime);
                    break;
                }
                case CONSTANT_BODY_FORCE:
                {
                    body_force = this->mrProblemDefinition.GetConstantBodyForce();
                    break;
                }
                default:
                    NEVER_REACHED;
            }
        }

        // Interpolate grad_u
        grad_u = zero_matrix<double>(DIM,DIM);
        for (unsigned node_index=0; node_index<NUM_NODES_PER_ELEMENT; node_index++)
        {
            for (unsigned i=0; i<DIM; i++)
            {
                for (unsigned M=0; M<DIM; M++)
                {
                    grad_u(i,M) += grad_quad_phi(M,node_index)*element_current_displacements(i,node_index);
                }
            }
        }

        // Calculate C, inv(C) and T
        for (unsigned i=0; i<DIM; i++)
        {
            for (unsigned M=0; M<DIM; M++)
            {
                F(i,M) = (i==M?1:0) + grad_u(i,M);
            }
        }

        C = prod(trans(F),F);
        inv_C = Inverse(C);
        inv_F = Inverse(F);

        // Compute the passive stress, and dTdE corresponding to passive stress
        this->SetupChangeOfBasisMatrix(rElement.GetIndex(), current_quad_point_global_index);
        p_material_law->SetChangeOfBasisMatrix(this->mChangeOfBasisMatrix);
        p_material_law->ComputeStressAndStressDerivative(C, inv_C, 0.0, T, dTdE, assembleJacobian);

        if(this->mIncludeActiveTension)
        {
            // Add any active stresses, if there are any. Requires subclasses to overload this method,
            // see for example the cardiac mechanics assemblers.
            this->AddActiveStressAndStressDerivative(C, rElement.GetIndex(), current_quad_point_global_index,
                                                     T, dTdE, assembleJacobian);
        }

        if(this->mSetComputeAverageStressPerElement)
        {
            this->AddStressToAverageStressPerElement(T,rElement.GetIndex());
        }

        // Residual vector
        if (assembleResidual)
        {
            F_T = prod(F,T);
            F_T_grad_quad_phi = prod(F_T, grad_quad_phi);

            for (unsigned index=0; index<NUM_NODES_PER_ELEMENT*DIM; index++)
            {
                unsigned spatial_dim = index%DIM;
                unsigned node_index = (index-spatial_dim)/DIM;

                rBElem(index) += - this->mrProblemDefinition.GetDensity()
                                 * body_force(spatial_dim)
                                 * quad_phi(node_index)
                                 * wJ;

                // The T(M,N)*F(spatial_dim,M)*grad_quad_phi(N,node_index) term
                rBElem(index) +=   F_T_grad_quad_phi(spatial_dim,node_index)
                                 * wJ;
            }
        }

        // Jacobian matrix
        if (assembleJacobian)
        {
            // Save trans(grad_quad_phi) * invF
            grad_quad_phi_times_invF = prod(trans_grad_quad_phi, inv_F);

            /////////////////////////////////////////////////////////////////////////////////////////////
            // Set up the tensor dSdF
            //
            // dSdF as a function of T and dTdE (which is what the material law returns) is given by:
            //
            // dS_{Mi}/dF_{jN} = (dT_{MN}/dC_{PQ}+dT_{MN}/dC_{PQ}) F{iP} F_{jQ}  + T_{MN} delta_{ij}
            //
            // todo1: this should probably move into the material law (but need to make sure
            // memory is handled efficiently
            // todo2: get material law to return this immediately, not dTdE
            /////////////////////////////////////////////////////////////////////////////////////////////

            // Set up the tensor 0.5(dTdE(M,N,P,Q) + dTdE(M,N,Q,P))
            for (unsigned M=0; M<DIM; M++)
            {
                for (unsigned N=0; N<DIM; N++)
                {
                    for (unsigned P=0; P<DIM; P++)
                    {
                        for (unsigned Q=0; Q<DIM; Q++)
                        {
                            // this is NOT dSdF, just using this as storage space
                            dSdF(M,N,P,Q) = 0.5*(dTdE(M,N,P,Q) + dTdE(M,N,Q,P));
                        }
                    }
                }
            }

            // This is NOT dTdE, just reusing memory. A^{MdPQ}  = F^d_N * dTdE_sym^{MNPQ}
            dTdE.template SetAsContractionOnSecondDimension<DIM>(F, dSdF);

            // dSdF{MdPe} := F^d_N * F^e_Q * dTdE_sym^{MNPQ}
            dSdF.template SetAsContractionOnFourthDimension<DIM>(F, dTdE);

            // Now add the T_{MN} delta_{ij} term
            for (unsigned M=0; M<DIM; M++)
            {
                for (unsigned N=0; N<DIM; N++)
                {
                    for (unsigned i=0; i<DIM; i++)
                    {
                        dSdF(M,i,N,i) += T(M,N);
                    }
                }
            }

            ///////////////////////////////////////////////////////
            // Set up the tensor
            //   dSdF_quad_quad(node_index1, spatial_dim1, node_index2, spatial_dim2)
            //            =    dS_{M,spatial_dim1}/d_F{spatial_dim2,N}
            //               * grad_quad_phi(M,node_index1)
            //               * grad_quad_phi(P,node_index2)
            //
            //            =    dSdF(M,spatial_index1,N,spatial_index2)
            //               * grad_quad_phi(M,node_index1)
            //               * grad_quad_phi(P,node_index2)
            //
            ///////////////////////////////////////////////////////
            temp_tensor.template SetAsContractionOnFirstDimension<DIM>(trans_grad_quad_phi, dSdF);
            dSdF_quad_quad.template SetAsContractionOnThirdDimension<DIM>(trans_grad_quad_phi, temp_tensor);

            for (unsigned index1=0; index1<NUM_NODES_PER_ELEMENT*DIM; index1++)
            {
                unsigned spatial_dim1 = index1%DIM;
                unsigned node_index1 = (index1-spatial_dim1)/DIM;

                for (unsigned index2=0; index2<NUM_NODES_PER_ELEMENT*DIM; index2++)
                {
                    unsigned spatial_dim2 = index2%DIM;
                    unsigned node_index2 = (index2-spatial_dim2)/DIM;

                    // The dSdF*grad_quad_phi*grad_quad_phi term
                    rAElem(index1,index2) +=   dSdF_quad_quad(node_index1,spatial_dim1,node_index2,spatial_dim2)
                                             * wJ;
                }
            }
        }
    }

    rAElemPrecond.clear();
    if (assembleJacobian)
    {
        rAElemPrecond = rAElem;
    }

    if(this->mSetComputeAverageStressPerElement)
    {
        for(unsigned i=0; i<DIM*(DIM+1)/2; i++)
        {
            this->mAverageStressesPerElement[rElement.GetIndex()](i) /= this->mpQuadratureRule->GetNumQuadPoints();
        }
    }

}