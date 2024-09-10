    void DiscreteProblemFormAssembler<Scalar>::assemble_matrix_form(MatrixForm<double, Scalar>* form, int order, Func<double>** base_fns, Func<double>** test_fns, Func<Scalar>** ext, Func<Scalar>** u_ext,
      AsmList<Scalar>* current_als_i, AsmList<Scalar>* current_als_j, Traverse::State* current_state, int n_quadrature_points, Geom<double>* geometry, double* jacobian_x_weights)
    {
      bool surface_form = (dynamic_cast<MatrixFormVol<Scalar>*>(form) == nullptr);

      double block_scaling_coefficient = this->block_scaling_coeff(form);

      bool tra = (form->i != form->j) && (form->sym != 0);
      bool sym = (form->i == form->j) && (form->sym == 1);

      // Assemble the local stiffness matrix for the form form.
      Scalar **local_stiffness_matrix = new_matrix<Scalar>(std::max(current_als_i->cnt, current_als_j->cnt));

      Func<Scalar>** local_ext = ext;
      // If the user supplied custom ext functions for this form.
      if(form->ext.size() > 0)
      {
        int local_ext_count = form->ext.size();
        local_ext = malloc_with_check(local_ext_count, this);
        for(int ext_i = 0; ext_i < local_ext_count; ext_i++)
          if(form->ext[ext_i])
            local_ext[ext_i] = current_state->e[ext_i] == nullptr ? nullptr : init_fn(form->ext[ext_i].get(), order);
          else
            local_ext[ext_i] = nullptr;
      }

      // Account for the previous time level solution previously inserted at the back of ext.
      if(rungeKutta)
        u_ext += form->u_ext_offset;

      // Actual form-specific calculation.
      for (unsigned int i = 0; i < current_als_i->cnt; i++)
      {
        if(current_als_i->dof[i] < 0)
          continue;

        if((!tra || surface_form) && current_als_i->dof[i] < 0)
          continue;
        if(std::abs(current_als_i->coef[i]) < Hermes::HermesSqrtEpsilon)
          continue;
        if(!sym)
        {
          for (unsigned int j = 0; j < current_als_j->cnt; j++)
          {
            if(current_als_j->dof[j] >= 0)
            {
              // Is this necessary, i.e. is there a coefficient smaller than Hermes::HermesSqrtEpsilon?
              if(std::abs(current_als_j->coef[j]) < Hermes::HermesSqrtEpsilon)
                continue;

              Func<double>* u = base_fns[j];
              Func<double>* v = test_fns[i];

              if(surface_form)
                local_stiffness_matrix[i][j] = 0.5 * block_scaling_coefficient * form->value(n_quadrature_points, jacobian_x_weights, u_ext, u, v, geometry, local_ext) * form->scaling_factor * current_als_j->coef[j] * current_als_i->coef[i];
              else
                local_stiffness_matrix[i][j] = block_scaling_coefficient * form->value(n_quadrature_points, jacobian_x_weights, u_ext, u, v, geometry, local_ext) * form->scaling_factor * current_als_j->coef[j] * current_als_i->coef[i];
            }
          }
        }
        // Symmetric block.
        else
        {
          for (unsigned int j = 0; j < current_als_j->cnt; j++)
          {
            if(j < i && current_als_j->dof[j] >= 0)
              continue;
            if(current_als_j->dof[j] >= 0)
            {
              // Is this necessary, i.e. is there a coefficient smaller than Hermes::HermesSqrtEpsilon?
              if(std::abs(current_als_j->coef[j]) < Hermes::HermesSqrtEpsilon)
                continue;

              Func<double>* u = base_fns[j];
              Func<double>* v = test_fns[i];

              Scalar val = block_scaling_coefficient * form->value(n_quadrature_points, jacobian_x_weights, u_ext, u, v, geometry, local_ext) * form->scaling_factor * current_als_j->coef[j] * current_als_i->coef[i];

              local_stiffness_matrix[i][j] = local_stiffness_matrix[j][i] = val;
            }
          }
        }
      }

      // Insert the local stiffness matrix into the global one.
      current_mat->add(current_als_i->cnt, current_als_j->cnt, local_stiffness_matrix, current_als_i->dof, current_als_j->dof);

      // Insert also the off-diagonal (anti-)symmetric block, if required.
      if(tra)
      {
        if(form->sym < 0)
          chsgn(local_stiffness_matrix, current_als_i->cnt, current_als_j->cnt);
        transpose(local_stiffness_matrix, current_als_i->cnt, current_als_j->cnt);

        current_mat->add(current_als_j->cnt, current_als_i->cnt, local_stiffness_matrix, current_als_j->dof, current_als_i->dof);
      }

      if(form->ext.size() > 0)
      {
        for(int ext_i = 0; ext_i < form->ext.size(); ext_i++)
          if(form->ext[ext_i])
          {
            local_ext[ext_i]->free_fn();
            delete local_ext[ext_i];
          }
          free_with_check(local_ext);
      }

      if(rungeKutta)
        u_ext -= form->u_ext_offset;

      // Cleanup.
      free_with_check(local_stiffness_matrix);
    }