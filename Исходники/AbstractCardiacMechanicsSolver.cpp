void AbstractCardiacMechanicsSolver<ELASTICITY_SOLVER,DIM>::AddActiveStressAndStressDerivative(c_matrix<double,DIM,DIM>& rC,
                                                                                               unsigned elementIndex,
                                                                                               unsigned currentQuadPointGlobalIndex,
                                                                                               c_matrix<double,DIM,DIM>& rT,
                                                                                               FourthOrderTensor<DIM,DIM,DIM,DIM>& rDTdE,
                                                                                               bool addToDTdE)
{
    for(unsigned i=0; i<DIM; i++)
    {
        mCurrentElementFibreDirection(i) = this->mChangeOfBasisMatrix(i,0);
    }

    //Compute the active tension and add to the stress and stress-derivative
    double I4_fibre = inner_prod(mCurrentElementFibreDirection, prod(rC, mCurrentElementFibreDirection));
    double lambda_fibre = sqrt(I4_fibre);

    double active_tension = 0;
    double d_act_tension_dlam = 0.0;     // Set and used if assembleJacobian==true
    double d_act_tension_d_dlamdt = 0.0; // Set and used if assembleJacobian==true

    GetActiveTensionAndTensionDerivs(lambda_fibre, currentQuadPointGlobalIndex, addToDTdE,
                                     active_tension, d_act_tension_dlam, d_act_tension_d_dlamdt);


    double detF = sqrt(Determinant(rC));
    rT += (active_tension*detF/I4_fibre)*outer_prod(mCurrentElementFibreDirection,mCurrentElementFibreDirection);

    // amend the stress and dTdE using the active tension
    double dTdE_coeff1 = -2*active_tension*detF/(I4_fibre*I4_fibre); // note: I4_fibre*I4_fibre = lam^4
    double dTdE_coeff2 = active_tension*detF/I4_fibre;
    double dTdE_coeff_s1 = 0.0; // only set non-zero if we apply cross fibre tension (in 2/3D)
    double dTdE_coeff_s2 = 0.0; // only set non-zero if we apply cross fibre tension (in 2/3D)
    double dTdE_coeff_s3 = 0.0; // only set non-zero if we apply cross fibre tension and implicit (in 2/3D)
    double dTdE_coeff_n1 = 0.0; // only set non-zero if we apply cross fibre tension in 3D
    double dTdE_coeff_n2 = 0.0; // only set non-zero if we apply cross fibre tension in 3D
    double dTdE_coeff_n3 = 0.0; // only set non-zero if we apply cross fibre tension in 3D and implicit

    if(IsImplicitSolver())
    {
        double dt = mNextTime-mCurrentTime;
        //std::cout << "d sigma / d lamda = " << d_act_tension_dlam << ", d sigma / d lamdat = " << d_act_tension_d_dlamdt << "\n" << std::flush;
        dTdE_coeff1 += (d_act_tension_dlam + d_act_tension_d_dlamdt/dt)*detF/(lambda_fibre*I4_fibre); // note: I4_fibre*lam = lam^3
    }

    bool apply_cross_fibre_tension = (this->mrElectroMechanicsProblemDefinition.GetApplyCrossFibreTension()) && (DIM > 1);
    if(apply_cross_fibre_tension)
    {
        double sheet_cross_fraction = mrElectroMechanicsProblemDefinition.GetSheetTensionFraction();

        for(unsigned i=0; i<DIM; i++)
        {
            mCurrentElementSheetDirection(i) = this->mChangeOfBasisMatrix(i,1);
        }

        double I4_sheet = inner_prod(mCurrentElementSheetDirection, prod(rC, mCurrentElementSheetDirection));

        // amend the stress and dTdE using the active tension
        dTdE_coeff_s1 = -2*sheet_cross_fraction*detF*active_tension/(I4_sheet*I4_sheet); // note: I4*I4 = lam^4

        if(IsImplicitSolver())
        {
            double dt = mNextTime-mCurrentTime;
            dTdE_coeff_s3 = sheet_cross_fraction*(d_act_tension_dlam + d_act_tension_d_dlamdt/dt)*detF/(lambda_fibre*I4_sheet); // note: I4*lam = lam^3
        }

        rT += sheet_cross_fraction*(active_tension*detF/I4_sheet)*outer_prod(mCurrentElementSheetDirection,mCurrentElementSheetDirection);

        dTdE_coeff_s2 = active_tension*sheet_cross_fraction*detF/I4_sheet;

        if (DIM>2)
        {
            double sheet_normal_cross_fraction = mrElectroMechanicsProblemDefinition.GetSheetNormalTensionFraction();
            for(unsigned i=0; i<DIM; i++)
            {
                mCurrentElementSheetNormalDirection(i) = this->mChangeOfBasisMatrix(i,2);
            }

            double I4_sheet_normal = inner_prod(mCurrentElementSheetNormalDirection, prod(rC, mCurrentElementSheetNormalDirection));

            dTdE_coeff_n1 =-2*sheet_normal_cross_fraction*detF*active_tension/(I4_sheet_normal*I4_sheet_normal); // note: I4*I4 = lam^4

            rT += sheet_normal_cross_fraction*(active_tension*detF/I4_sheet_normal)*outer_prod(mCurrentElementSheetNormalDirection,mCurrentElementSheetNormalDirection);

            dTdE_coeff_n2 = active_tension*sheet_normal_cross_fraction*detF/I4_sheet_normal;
            if(IsImplicitSolver())
            {
                double dt = mNextTime-mCurrentTime;
                dTdE_coeff_n3 = sheet_normal_cross_fraction*(d_act_tension_dlam + d_act_tension_d_dlamdt/dt)*detF/(lambda_fibre*I4_sheet_normal); // note: I4*lam = lam^3
            }
        }
    }


    if(addToDTdE)
    {
        c_matrix<double,DIM,DIM> invC = Inverse(rC);

        for (unsigned M=0; M<DIM; M++)
        {
            for (unsigned N=0; N<DIM; N++)
            {
                for (unsigned P=0; P<DIM; P++)
                {
                    for (unsigned Q=0; Q<DIM; Q++)
                    {
                        rDTdE(M,N,P,Q) +=   dTdE_coeff1 * mCurrentElementFibreDirection(M)
                                                        * mCurrentElementFibreDirection(N)
                                                        * mCurrentElementFibreDirection(P)
                                                        * mCurrentElementFibreDirection(Q)

                                         +  dTdE_coeff2 * mCurrentElementFibreDirection(M)
                                                        * mCurrentElementFibreDirection(N)
                                                        * invC(P,Q);
                        if(apply_cross_fibre_tension)
                        {
                            rDTdE(M,N,P,Q) += dTdE_coeff_s1 * mCurrentElementSheetDirection(M)
                                                            * mCurrentElementSheetDirection(N)
                                                            * mCurrentElementSheetDirection(P)
                                                            * mCurrentElementSheetDirection(Q)

                                           +  dTdE_coeff_s2 * mCurrentElementSheetDirection(M)
                                                            * mCurrentElementSheetDirection(N)
                                                            * invC(P,Q)

                                           + dTdE_coeff_s3 * mCurrentElementSheetDirection(M)
                                                           * mCurrentElementSheetDirection(N)
                                                           * mCurrentElementFibreDirection(P)
                                                           * mCurrentElementFibreDirection(Q);
                            if (DIM>2)
                            {
                                rDTdE(M,N,P,Q) += dTdE_coeff_n1 * mCurrentElementSheetNormalDirection(M)
                                                                * mCurrentElementSheetNormalDirection(N)
                                                                * mCurrentElementSheetNormalDirection(P)
                                                                * mCurrentElementSheetNormalDirection(Q)

                                                + dTdE_coeff_n2 * mCurrentElementSheetNormalDirection(M)
                                                                * mCurrentElementSheetNormalDirection(N)
                                                                * invC(P,Q)

                                                + dTdE_coeff_n3 * mCurrentElementSheetNormalDirection(M)
                                                                * mCurrentElementSheetNormalDirection(N)
                                                                * mCurrentElementFibreDirection(P)
                                                                * mCurrentElementFibreDirection(Q);
                            }
                        }
                    }
                }
            }
        }
    }

//    ///\todo #2180 The code below applies a cross fibre tension in the 2D case. Things that need doing:
//    // * Refactor the common code between the block below and the block above to avoid duplication.
//    // * Handle the 3D case.
//    if(this->mrElectroMechanicsProblemDefinition.GetApplyCrossFibreTension() && DIM > 1)
//    {
//        double sheet_cross_fraction = mrElectroMechanicsProblemDefinition.GetSheetTensionFraction();
//
//        for(unsigned i=0; i<DIM; i++)
//        {
//            mCurrentElementSheetDirection(i) = this->mChangeOfBasisMatrix(i,1);
//        }
//
//        double I4_sheet = inner_prod(mCurrentElementSheetDirection, prod(rC, mCurrentElementSheetDirection));
//
//        // amend the stress and dTdE using the active tension
//        double dTdE_coeff_s1 = -2*sheet_cross_fraction*detF*active_tension/(I4_sheet*I4_sheet); // note: I4*I4 = lam^4
//
//        ///\todo #2180 The code below is specific to the implicit cardiac mechanics solver. Currently
//        // the cross-fibre code is only tested using the explicit solver so the code below fails coverage.
//        // This will need to be added back in once an implicit test is in place.
//        double lambda_sheet = sqrt(I4_sheet);
//        if(IsImplicitSolver())
//        {
//           double dt = mNextTime-mCurrentTime;
//           dTdE_coeff_s1 += (d_act_tension_dlam + d_act_tension_d_dlamdt/dt)/(lambda_sheet*I4_sheet); // note: I4*lam = lam^3
//        }
//
//        rT += sheet_cross_fraction*(active_tension*detF/I4_sheet)*outer_prod(mCurrentElementSheetDirection,mCurrentElementSheetDirection);
//
//        double dTdE_coeff_s2 = active_tension*detF/I4_sheet;
//        if(addToDTdE)
//        {
//           for (unsigned M=0; M<DIM; M++)
//           {
//               for (unsigned N=0; N<DIM; N++)
//               {
//                   for (unsigned P=0; P<DIM; P++)
//                   {
//                       for (unsigned Q=0; Q<DIM; Q++)
//                       {
//                           rDTdE(M,N,P,Q) +=  dTdE_coeff_s1 * mCurrentElementSheetDirection(M)
//                                                            * mCurrentElementSheetDirection(N)
//                                                            * mCurrentElementSheetDirection(P)
//                                                            * mCurrentElementSheetDirection(Q)
//
//                                           +  dTdE_coeff_s2 * mCurrentElementFibreDirection(M)
//                                                            * mCurrentElementFibreDirection(N)
//                                                            * invC(P,Q);
//
//                       }
//                   }
//               }
//           }
//        }
//    }
}