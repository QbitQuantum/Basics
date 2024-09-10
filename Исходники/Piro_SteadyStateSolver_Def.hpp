void Piro::SteadyStateSolver<Scalar>::evalConvergedModel(
    const Thyra::ModelEvaluatorBase::InArgs<Scalar>& modelInArgs,
    const Thyra::ModelEvaluatorBase::OutArgs<Scalar>& outArgs) const
{
  using Teuchos::RCP;
  using Teuchos::rcp;

  // Solution at convergence is the response at index num_g_
  {
    const RCP<Thyra::VectorBase<Scalar> > gx_out = outArgs.get_g(num_g_);
    if (Teuchos::nonnull(gx_out)) {
      Thyra::copy(*modelInArgs.get_x(), gx_out.ptr());
    }
  }

  // Setup output for final evalution of underlying model
  Thyra::ModelEvaluatorBase::OutArgs<Scalar> modelOutArgs = model_->createOutArgs();
  {
    // Responses
    for (int j = 0; j < num_g_; ++j) {
      const RCP<Thyra::VectorBase<Scalar> > g_out = outArgs.get_g(j);
      // Forward to underlying model
      modelOutArgs.set_g(j, g_out);
    }

    // Jacobian
    {
      bool jacobianRequired = false;
      for (int j = 0; j <= num_g_; ++j) {
        for (int l = 0; l < num_p_; ++l) {
          const Thyra::ModelEvaluatorBase::DerivativeSupport dgdp_support =
            outArgs.supports(Thyra::ModelEvaluatorBase::OUT_ARG_DgDp, j, l);
          if (!dgdp_support.none()) {
            const Thyra::ModelEvaluatorBase::Derivative<Scalar> dgdp_deriv =
              outArgs.get_DgDp(j, l);
            if (!dgdp_deriv.isEmpty()) {
              jacobianRequired = true;
            }
          }
        }
      }
      if (jacobianRequired) {
        const RCP<Thyra::LinearOpWithSolveBase<Scalar> > jacobian =
          model_->create_W();
        modelOutArgs.set_W(jacobian);
      }
    }

    // DfDp derivatives
    for (int l = 0; l < num_p_; ++l) {
      Thyra::ModelEvaluatorBase::DerivativeSupport dfdp_request;
      for (int j = 0; j <= num_g_; ++j) {
        const Thyra::ModelEvaluatorBase::DerivativeSupport dgdp_support =
          outArgs.supports(Thyra::ModelEvaluatorBase::OUT_ARG_DgDp, j, l);
        if (!dgdp_support.none()) {
          const Thyra::ModelEvaluatorBase::Derivative<Scalar> dgdp_deriv =
            outArgs.get_DgDp(j, l);
          if (Teuchos::nonnull(dgdp_deriv.getLinearOp())) {
            dfdp_request.plus(Thyra::ModelEvaluatorBase::DERIV_LINEAR_OP);
          } else if (Teuchos::nonnull(dgdp_deriv.getMultiVector())) {
            dfdp_request.plus(Thyra::ModelEvaluatorBase::DERIV_MV_JACOBIAN_FORM);
          }
        }
      }

      if (!dfdp_request.none()) {
        Thyra::ModelEvaluatorBase::Derivative<Scalar> dfdp_deriv;
        if (dfdp_request.supports(Thyra::ModelEvaluatorBase::DERIV_MV_JACOBIAN_FORM)) {
          dfdp_deriv = Thyra::create_DfDp_mv(*model_, l, Thyra::ModelEvaluatorBase::DERIV_MV_JACOBIAN_FORM);
        } else if (dfdp_request.supports(Thyra::ModelEvaluatorBase::DERIV_LINEAR_OP)) {
          dfdp_deriv = model_->create_DfDp_op(l);
        }
        modelOutArgs.set_DfDp(l, dfdp_deriv);
      }
    }

    // DgDx derivatives
    for (int j = 0; j < num_g_; ++j) {
      Thyra::ModelEvaluatorBase::DerivativeSupport dgdx_request;
      for (int l = 0; l < num_p_; ++l) {
        const Thyra::ModelEvaluatorBase::DerivativeSupport dgdp_support =
          outArgs.supports(Thyra::ModelEvaluatorBase::OUT_ARG_DgDp, j, l);
        if (!dgdp_support.none()) {
          const Thyra::ModelEvaluatorBase::Derivative<Scalar> dgdp_deriv =
            outArgs.get_DgDp(j, l);
          if (!dgdp_deriv.isEmpty()) {
            const bool dgdp_mvGrad_required =
              Teuchos::nonnull(dgdp_deriv.getMultiVector()) &&
              dgdp_deriv.getMultiVectorOrientation() == Thyra::ModelEvaluatorBase::DERIV_MV_GRADIENT_FORM;
            if (dgdp_mvGrad_required) {
              dgdx_request.plus(Thyra::ModelEvaluatorBase::DERIV_MV_GRADIENT_FORM);
            } else {
              dgdx_request.plus(Thyra::ModelEvaluatorBase::DERIV_LINEAR_OP);
            }
          }
        }
      }

      if (!dgdx_request.none()) {
        Thyra::ModelEvaluatorBase::Derivative<Scalar> dgdx_deriv;
        if (dgdx_request.supports(Thyra::ModelEvaluatorBase::DERIV_MV_GRADIENT_FORM)) {
          dgdx_deriv = Thyra::create_DgDx_mv(*model_, j, Thyra::ModelEvaluatorBase::DERIV_MV_GRADIENT_FORM);
        } else if (dgdx_request.supports(Thyra::ModelEvaluatorBase::DERIV_LINEAR_OP)) {
          dgdx_deriv = model_->create_DgDx_op(j);
        }
        modelOutArgs.set_DgDx(j, dgdx_deriv);
      }
    }

    // DgDp derivatives
    for (int l = 0; l < num_p_; ++l) {
      for (int j = 0; j < num_g_; ++j) {
        const Thyra::ModelEvaluatorBase::DerivativeSupport dgdp_support =
          outArgs.supports(Thyra::ModelEvaluatorBase::OUT_ARG_DgDp, j, l);
        if (!dgdp_support.none()) {
          const Thyra::ModelEvaluatorBase::Derivative<Scalar> dgdp_deriv =
            outArgs.get_DgDp(j, l);
          Thyra::ModelEvaluatorBase::Derivative<Scalar> model_dgdp_deriv;
          const RCP<Thyra::LinearOpBase<Scalar> > dgdp_op = dgdp_deriv.getLinearOp();
          if (Teuchos::nonnull(dgdp_op)) {
            model_dgdp_deriv = model_->create_DgDp_op(j, l);
          } else {
            model_dgdp_deriv = dgdp_deriv;
          }
          if (!model_dgdp_deriv.isEmpty()) {
            modelOutArgs.set_DgDp(j, l, model_dgdp_deriv);
          }
        }
      }
    }
  }

  // Evaluate underlying model
  model_->evalModel(modelInArgs, modelOutArgs);

  // Assemble user-requested sensitivities
  if (modelOutArgs.supports(Thyra::ModelEvaluatorBase::OUT_ARG_W)) {
    const RCP<Thyra::LinearOpWithSolveBase<Scalar> > jacobian =
      modelOutArgs.get_W();
    if (Teuchos::nonnull(jacobian)) {
      for (int l = 0; l < num_p_; ++l) {
        const Thyra::ModelEvaluatorBase::DerivativeSupport dfdp_support =
          modelOutArgs.supports(Thyra::ModelEvaluatorBase::OUT_ARG_DfDp, l);
        if (!dfdp_support.none()) {
          const Thyra::ModelEvaluatorBase::Derivative<Scalar> dfdp_deriv =
            modelOutArgs.get_DfDp(l);
          const RCP<Thyra::MultiVectorBase<Scalar> > dfdp_mv =
            dfdp_deriv.getMultiVector();
          RCP<Thyra::LinearOpBase<Scalar> > dfdp_op =
            dfdp_deriv.getLinearOp();
          if (Teuchos::is_null(dfdp_op)) {
            dfdp_op = dfdp_mv;
          }

          const Thyra::ModelEvaluatorBase::Derivative<Scalar> dxdp_deriv =
            outArgs.get_DgDp(num_g_, l);
          const RCP<Thyra::LinearOpBase<Scalar> > dxdp_op =
            dxdp_deriv.getLinearOp();
          const RCP<Thyra::MultiVectorBase<Scalar> > dxdp_mv =
            dxdp_deriv.getMultiVector();

          RCP<const Thyra::LinearOpBase<Scalar> > minus_dxdp_op;
          RCP<Thyra::MultiVectorBase<Scalar> > minus_dxdp_mv;
          if (Teuchos::nonnull(dfdp_mv)) {
            if (Teuchos::nonnull(dxdp_mv)) {
              minus_dxdp_mv = dxdp_mv; // Use user-provided object as temporary
            } else {
              minus_dxdp_mv =
                Thyra::createMembers(model_->get_x_space(), model_->get_p_space(l));
              minus_dxdp_op = minus_dxdp_mv;
            }
          }

          if (Teuchos::is_null(minus_dxdp_op)) {
            const RCP<const Thyra::LinearOpBase<Scalar> > dfdx_inv_op =
              Thyra::inverse<Scalar>(jacobian);
            minus_dxdp_op = Thyra::multiply<Scalar>(dfdx_inv_op, dfdp_op);
          }

          if (Teuchos::nonnull(minus_dxdp_mv)) {
            Thyra::assign(minus_dxdp_mv.ptr(), Teuchos::ScalarTraits<Scalar>::zero());

            const Thyra::SolveCriteria<Scalar> defaultSolveCriteria;
            const Thyra::SolveStatus<Scalar> solveStatus =
              Thyra::solve(
                  *jacobian,
                  Thyra::NOTRANS,
                  *dfdp_mv,
                  minus_dxdp_mv.ptr(),
                  Teuchos::ptr(&defaultSolveCriteria));
            TEUCHOS_TEST_FOR_EXCEPTION(
                solveStatus.solveStatus == Thyra::SOLVE_STATUS_UNCONVERGED,
                std::runtime_error,
                "Jacobian solver failed to converge");
          }

          // Solution sensitivities
          if (Teuchos::nonnull(dxdp_mv)) {
            minus_dxdp_mv = Teuchos::null; // Invalidates temporary
            Thyra::scale(-Teuchos::ScalarTraits<Scalar>::one(), dxdp_mv.ptr());
          } else if (Teuchos::nonnull(dxdp_op)) {
            const RCP<Thyra::DefaultMultipliedLinearOp<Scalar> > dxdp_op_downcasted =
              Teuchos::rcp_dynamic_cast<Thyra::DefaultMultipliedLinearOp<Scalar> >(dxdp_op);
            TEUCHOS_TEST_FOR_EXCEPTION(
                Teuchos::is_null(dxdp_op_downcasted),
                std::invalid_argument,
                "Illegal operator for DgDp(" <<
                "j = " << num_g_ << ", " <<
                "index l = " << l << ")\n");

            const RCP<const Thyra::LinearOpBase<Scalar> > minus_id_op =
              Thyra::scale<Scalar>(-Teuchos::ScalarTraits<Scalar>::one(), Thyra::identity(dfdp_op->domain()));

            dxdp_op_downcasted->initialize(Teuchos::tuple(minus_dxdp_op, minus_id_op));
          }

          // Response sensitivities
          for (int j = 0; j < num_g_; ++j) {
            const Thyra::ModelEvaluatorBase::DerivativeSupport dgdp_support =
              outArgs.supports(Thyra::ModelEvaluatorBase::OUT_ARG_DgDp, j, l);
            if (!dgdp_support.none()) {
              const Thyra::ModelEvaluatorBase::Derivative<Scalar> dgdp_deriv =
                outArgs.get_DgDp(j, l);
              if (!dgdp_deriv.isEmpty()) {
                const Thyra::ModelEvaluatorBase::Derivative<Scalar> dgdx_deriv =
                  modelOutArgs.get_DgDx(j);
                const RCP<const Thyra::MultiVectorBase<Scalar> > dgdx_mv =
                  dgdx_deriv.getMultiVector();
                RCP<const Thyra::LinearOpBase<Scalar> > dgdx_op =
                  dgdx_deriv.getLinearOp();
                if (Teuchos::is_null(dgdx_op)) {
                  dgdx_op = Thyra::adjoint<Scalar>(dgdx_mv);
                }

                const RCP<Thyra::LinearOpBase<Scalar> > dgdp_op =
                  dgdp_deriv.getLinearOp();
                if (Teuchos::nonnull(dgdp_op)) {
                  const RCP<Thyra::DefaultAddedLinearOp<Scalar> > dgdp_op_downcasted =
                    Teuchos::rcp_dynamic_cast<Thyra::DefaultAddedLinearOp<Scalar> >(dgdp_op);
                  TEUCHOS_TEST_FOR_EXCEPTION(
                      Teuchos::is_null(dgdp_op_downcasted),
                      std::invalid_argument,
                      "Illegal operator for DgDp(" <<
                      "j = " << j << ", " <<
                      "index l = " << l << ")\n");

                  dgdp_op_downcasted->uninitialize();

                  const RCP<const Thyra::LinearOpBase<Scalar> > implicit_dgdp_op =
                    Thyra::multiply<Scalar>(
                      Thyra::scale<Scalar>(-Teuchos::ScalarTraits<Scalar>::one(), dgdx_op),
                      minus_dxdp_op);

                  const RCP<const Thyra::LinearOpBase<Scalar> > model_dgdp_op =
                    modelOutArgs.get_DgDp(j, l).getLinearOp();

                  Teuchos::Array<RCP<const Thyra::LinearOpBase<Scalar> > > op_args(2);
                  op_args[0] = model_dgdp_op;
                  op_args[1] = implicit_dgdp_op;
                  dgdp_op_downcasted->initialize(op_args);
                }

                const RCP<Thyra::MultiVectorBase<Scalar> > dgdp_mv =
                  dgdp_deriv.getMultiVector();
                if (Teuchos::nonnull(dgdp_mv)) {
                  if (dgdp_deriv.getMultiVectorOrientation() == Thyra::ModelEvaluatorBase::DERIV_MV_GRADIENT_FORM) {
                    if (Teuchos::nonnull(dxdp_mv)) {
                      Thyra::apply(
                          *dxdp_mv,
                          Thyra::TRANS,
                          *dgdx_mv,
                          dgdp_mv.ptr(),
                          Teuchos::ScalarTraits<Scalar>::one(),
                          Teuchos::ScalarTraits<Scalar>::one());
                    } else {
                      Thyra::apply(
                          *minus_dxdp_mv,
                          Thyra::TRANS,
                          *dgdx_mv,
                          dgdp_mv.ptr(),
                          -Teuchos::ScalarTraits<Scalar>::one(),
                          Teuchos::ScalarTraits<Scalar>::one());
                    }
                  } else {
                    if (Teuchos::nonnull(dxdp_mv)) {
                      Thyra::apply(
                          *dgdx_op,
                          Thyra::NOTRANS,
                          *dxdp_mv,
                          dgdp_mv.ptr(),
                          Teuchos::ScalarTraits<Scalar>::one(),
                          Teuchos::ScalarTraits<Scalar>::one());
                    } else {
                      Thyra::apply(
                          *dgdx_op,
                          Thyra::NOTRANS,
                          *minus_dxdp_mv,
                          dgdp_mv.ptr(),
                          -Teuchos::ScalarTraits<Scalar>::one(),
                          Teuchos::ScalarTraits<Scalar>::one());
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}