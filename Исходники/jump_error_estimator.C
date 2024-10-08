void JumpErrorEstimator::estimate_error (const System& system,
                                         ErrorVector& error_per_cell,
                                         const NumericVector<Number>* solution_vector,
                                         bool estimate_parent_error)
{
  START_LOG("estimate_error()", "JumpErrorEstimator");
  /*

    Conventions for assigning the direction of the normal:

    - e & f are global element ids

    Case (1.) Elements are at the same level, e<f
    Compute the flux jump on the face and
    add it as a contribution to error_per_cell[e]
    and error_per_cell[f]

    ----------------------
    |           |          |
    |           |    f     |
    |           |          |
    |    e      |---> n    |
    |           |          |
    |           |          |
    ----------------------


    Case (2.) The neighbor is at a higher level.
    Compute the flux jump on e's face and
    add it as a contribution to error_per_cell[e]
    and error_per_cell[f]

    ----------------------
    |     |     |          |
    |     |  e  |---> n    |
    |     |     |          |
    |-----------|    f     |
    |     |     |          |
    |     |     |          |
    |     |     |          |
    ----------------------
  */

  // The current mesh
  const MeshBase& mesh = system.get_mesh();

  // The number of variables in the system
  const unsigned int n_vars = system.n_vars();

  // The DofMap for this system
  const DofMap& dof_map = system.get_dof_map();

  // Resize the error_per_cell vector to be
  // the number of elements, initialize it to 0.
  error_per_cell.resize (mesh.max_elem_id());
  std::fill (error_per_cell.begin(), error_per_cell.end(), 0.);

  // Declare a vector of floats which is as long as
  // error_per_cell above, and fill with zeros.  This vector will be
  // used to keep track of the number of edges (faces) on each active
  // element which are either:
  // 1) an internal edge
  // 2) an edge on a Neumann boundary for which a boundary condition
  //    function has been specified.
  // The error estimator can be scaled by the number of flux edges (faces)
  // which the element actually has to obtain a more uniform measure
  // of the error.  Use floats instead of ints since in case 2 (above)
  // f gets 1/2 of a flux face contribution from each of his
  // neighbors
  std::vector<float> n_flux_faces;
  if (scale_by_n_flux_faces)
    n_flux_faces.resize(error_per_cell.size(), 0);

  // Prepare current_local_solution to localize a non-standard
  // solution vector if necessary
  if (solution_vector && solution_vector != system.solution.get())
    {
      NumericVector<Number>* newsol =
        const_cast<NumericVector<Number>*>(solution_vector);
      System &sys = const_cast<System&>(system);
      newsol->swap(*sys.solution);
      sys.update();
    }

  fine_context.reset(new FEMContext(system));
  coarse_context.reset(new FEMContext(system));

  // Loop over all the variables we've been requested to find jumps in, to
  // pre-request
  for (var=0; var<n_vars; var++)
    {
      // Possibly skip this variable
      if (error_norm.weight(var) == 0.0) continue;

      // FIXME: Need to generalize this to vector-valued elements. [PB]
      FEBase* side_fe = NULL;

      const std::set<unsigned char>& elem_dims =
        fine_context->elem_dimensions();

      for (std::set<unsigned char>::const_iterator dim_it =
             elem_dims.begin(); dim_it != elem_dims.end(); ++dim_it)
        {
          const unsigned char dim = *dim_it;

          fine_context->get_side_fe( var, side_fe, dim );

          libmesh_assert_not_equal_to(side_fe->get_fe_type().family, SCALAR);

          side_fe->get_xyz();
        }
    }

  this->init_context(*fine_context);
  this->init_context(*coarse_context);

  // Iterate over all the active elements in the mesh
  // that live on this processor.
  MeshBase::const_element_iterator       elem_it  = mesh.active_local_elements_begin();
  const MeshBase::const_element_iterator elem_end = mesh.active_local_elements_end();

  for (; elem_it != elem_end; ++elem_it)
    {
      // e is necessarily an active element on the local processor
      const Elem* e = *elem_it;
      const dof_id_type e_id = e->id();

#ifdef LIBMESH_ENABLE_AMR
      // See if the parent of element e has been examined yet;
      // if not, we may want to compute the estimator on it
      const Elem* parent = e->parent();

      // We only can compute and only need to compute on
      // parents with all active children
      bool compute_on_parent = true;
      if (!parent || !estimate_parent_error)
        compute_on_parent = false;
      else
        for (unsigned int c=0; c != parent->n_children(); ++c)
          if (!parent->child(c)->active())
            compute_on_parent = false;

      if (compute_on_parent &&
          !error_per_cell[parent->id()])
        {
          // Compute a projection onto the parent
          DenseVector<Number> Uparent;
          FEBase::coarsened_dof_values
            (*(system.solution), dof_map, parent, Uparent, false);

          // Loop over the neighbors of the parent
          for (unsigned int n_p=0; n_p<parent->n_neighbors(); n_p++)
            {
              if (parent->neighbor(n_p) != NULL) // parent has a neighbor here
                {
                  // Find the active neighbors in this direction
                  std::vector<const Elem*> active_neighbors;
                  parent->neighbor(n_p)->
                    active_family_tree_by_neighbor(active_neighbors,
                                                   parent);
                  // Compute the flux to each active neighbor
                  for (unsigned int a=0;
                       a != active_neighbors.size(); ++a)
                    {
                      const Elem *f = active_neighbors[a];
                      // FIXME - what about when f->level <
                      // parent->level()??
                      if (f->level() >= parent->level())
                        {
                          fine_context->pre_fe_reinit(system, f);
                          coarse_context->pre_fe_reinit(system, parent);
                          libmesh_assert_equal_to
                            (coarse_context->get_elem_solution().size(),
                             Uparent.size());
                          coarse_context->get_elem_solution() = Uparent;

                          this->reinit_sides();

                          // Loop over all significant variables in the system
                          for (var=0; var<n_vars; var++)
                            if (error_norm.weight(var) != 0.0)
                              {
                                this->internal_side_integration();

                                error_per_cell[fine_context->get_elem().id()] +=
                                  static_cast<ErrorVectorReal>(fine_error);
                                error_per_cell[coarse_context->get_elem().id()] +=
                                  static_cast<ErrorVectorReal>(coarse_error);
                              }

                          // Keep track of the number of internal flux
                          // sides found on each element
                          if (scale_by_n_flux_faces)
                            {
                              n_flux_faces[fine_context->get_elem().id()]++;
                              n_flux_faces[coarse_context->get_elem().id()] +=
                                this->coarse_n_flux_faces_increment();
                            }
                        }
                    }
                }
              else if (integrate_boundary_sides)
                {
                  fine_context->pre_fe_reinit(system, parent);
                  libmesh_assert_equal_to
                    (fine_context->get_elem_solution().size(),
                     Uparent.size());
                  fine_context->get_elem_solution() = Uparent;
                  fine_context->side = n_p;
                  fine_context->side_fe_reinit();

                  // If we find a boundary flux for any variable,
                  // let's just count it as a flux face for all
                  // variables.  Otherwise we'd need to keep track of
                  // a separate n_flux_faces and error_per_cell for
                  // every single var.
                  bool found_boundary_flux = false;

                  for (var=0; var<n_vars; var++)
                    if (error_norm.weight(var) != 0.0)
                      {
                        if (this->boundary_side_integration())
                          {
                            error_per_cell[fine_context->get_elem().id()] +=
                              static_cast<ErrorVectorReal>(fine_error);
                            found_boundary_flux = true;
                          }
                      }

                  if (scale_by_n_flux_faces && found_boundary_flux)
                    n_flux_faces[fine_context->get_elem().id()]++;
                }
            }
        }
#endif // #ifdef LIBMESH_ENABLE_AMR

      // If we do any more flux integration, e will be the fine element
      fine_context->pre_fe_reinit(system, e);

      // Loop over the neighbors of element e
      for (unsigned int n_e=0; n_e<e->n_neighbors(); n_e++)
        {
          if ((e->neighbor(n_e) != NULL) ||
              integrate_boundary_sides)
            {
              fine_context->side = n_e;
              fine_context->side_fe_reinit();
            }

          if (e->neighbor(n_e) != NULL) // e is not on the boundary
            {
              const Elem* f           = e->neighbor(n_e);
              const dof_id_type f_id = f->id();

              // Compute flux jumps if we are in case 1 or case 2.
              if ((f->active() && (f->level() == e->level()) && (e_id < f_id))
                  || (f->level() < e->level()))
                {
                  // f is now the coarse element
                  coarse_context->pre_fe_reinit(system, f);

                  this->reinit_sides();

                  // Loop over all significant variables in the system
                  for (var=0; var<n_vars; var++)
                    if (error_norm.weight(var) != 0.0)
                      {
                        this->internal_side_integration();

                        error_per_cell[fine_context->get_elem().id()] +=
                          static_cast<ErrorVectorReal>(fine_error);
                        error_per_cell[coarse_context->get_elem().id()] +=
                          static_cast<ErrorVectorReal>(coarse_error);
                      }

                  // Keep track of the number of internal flux
                  // sides found on each element
                  if (scale_by_n_flux_faces)
                    {
                      n_flux_faces[fine_context->get_elem().id()]++;
                      n_flux_faces[coarse_context->get_elem().id()] +=
                        this->coarse_n_flux_faces_increment();
                    }
                } // end if (case1 || case2)
            } // if (e->neigbor(n_e) != NULL)

          // Otherwise, e is on the boundary.  If it happens to
          // be on a Dirichlet boundary, we need not do anything.
          // On the other hand, if e is on a Neumann (flux) boundary
          // with grad(u).n = g, we need to compute the additional residual
          // (h * \int |g - grad(u_h).n|^2 dS)^(1/2).
          // We can only do this with some knowledge of the boundary
          // conditions, i.e. the user must have attached an appropriate
          // BC function.
          else if (integrate_boundary_sides)
            {
              bool found_boundary_flux = false;

              for (var=0; var<n_vars; var++)
                if (error_norm.weight(var) != 0.0)
                  if (this->boundary_side_integration())
                    {
                      error_per_cell[fine_context->get_elem().id()] +=
                        static_cast<ErrorVectorReal>(fine_error);
                      found_boundary_flux = true;
                    }

              if (scale_by_n_flux_faces && found_boundary_flux)
                n_flux_faces[fine_context->get_elem().id()]++;
            } // end if (e->neighbor(n_e) == NULL)
        } // end loop over neighbors
    } // End loop over active local elements


  // Each processor has now computed the error contribuions
  // for its local elements.  We need to sum the vector
  // and then take the square-root of each component.  Note
  // that we only need to sum if we are running on multiple
  // processors, and we only need to take the square-root
  // if the value is nonzero.  There will in general be many
  // zeros for the inactive elements.

  // First sum the vector of estimated error values
  this->reduce_error(error_per_cell, system.comm());

  // Compute the square-root of each component.
  for (std::size_t i=0; i<error_per_cell.size(); i++)
    if (error_per_cell[i] != 0.)
      error_per_cell[i] = std::sqrt(error_per_cell[i]);


  if (this->scale_by_n_flux_faces)
    {
      // Sum the vector of flux face counts
      this->reduce_error(n_flux_faces, system.comm());

      // Sanity check: Make sure the number of flux faces is
      // always an integer value
#ifdef DEBUG
      for (unsigned int i=0; i<n_flux_faces.size(); ++i)
        libmesh_assert_equal_to (n_flux_faces[i], static_cast<float>(static_cast<unsigned int>(n_flux_faces[i])) );
#endif

      // Scale the error by the number of flux faces for each element
      for (unsigned int i=0; i<n_flux_faces.size(); ++i)
        {
          if (n_flux_faces[i] == 0.0) // inactive or non-local element
            continue;

          //libMesh::out << "Element " << i << " has " << n_flux_faces[i] << " flux faces." << std::endl;
          error_per_cell[i] /= static_cast<ErrorVectorReal>(n_flux_faces[i]);
        }
    }

  // If we used a non-standard solution before, now is the time to fix
  // the current_local_solution
  if (solution_vector && solution_vector != system.solution.get())
    {
      NumericVector<Number>* newsol =
        const_cast<NumericVector<Number>*>(solution_vector);
      System &sys = const_cast<System&>(system);
      newsol->swap(*sys.solution);
      sys.update();
    }

  STOP_LOG("estimate_error()", "JumpErrorEstimator");
}