void IBFEPostProcessor::interpolateVariables(const double data_time)
{
    Pointer<PatchHierarchy<NDIM> > hierarchy = d_fe_data_manager->getPatchHierarchy();
    const std::pair<int, int> patch_level_range = d_fe_data_manager->getPatchLevels();
    const int coarsest_ln = patch_level_range.first;
    const int finest_ln = patch_level_range.second - 1;

    const unsigned int num_eulerian_vars = d_scalar_interp_var_systems.size();

    // Set up Eulerian scratch space and fill ghost cell values.
    Pointer<RefineAlgorithm<NDIM> > refine_alg = new RefineAlgorithm<NDIM>();
    Pointer<RefineOperator<NDIM> > refine_op = NULL;
    std::set<int> scratch_idxs;
    for (unsigned int k = 0; k < num_eulerian_vars; ++k)
    {
        int& data_idx = d_scalar_interp_data_idxs[k];
        int& scratch_idx = d_scalar_interp_scratch_idxs[k];
        if (data_idx < 0 || scratch_idx < 0)
        {
            TBOX_ASSERT(data_idx < 0 || scratch_idx < 0);
            VariableDatabase<NDIM>* var_db = VariableDatabase<NDIM>::getDatabase();
            Pointer<hier::Variable<NDIM> > data_var = d_scalar_interp_vars[k];
            Pointer<VariableContext> data_ctx = d_scalar_interp_ctxs[k];
            data_idx = var_db->mapVariableAndContextToIndex(data_var, data_ctx);
            TBOX_ASSERT(data_idx >= 0);
            Pointer<VariableContext> scratch_ctx = var_db->getContext(d_name + "::SCRATCH");
            const FEDataManager::InterpSpec& interp_spec = d_scalar_interp_specs[k];
            const int ghost_width = LEInteractor::getMinimumGhostWidth(interp_spec.kernel_fcn);
            scratch_idx =
                var_db->registerVariableAndContext(data_var, scratch_ctx, ghost_width);
            scratch_idxs.insert(scratch_idx);
        }
        refine_alg->registerRefine(scratch_idx, data_idx, scratch_idx, refine_op);
    }
    CartExtrapPhysBdryOp refine_phys_bdry_op(scratch_idxs);
    for (int ln = coarsest_ln; ln <= finest_ln; ++ln)
    {
        Pointer<PatchLevel<NDIM> > level = hierarchy->getPatchLevel(ln);
        for (unsigned int k = 0; k < num_eulerian_vars; ++k)
        {
            const int scratch_idx = d_scalar_interp_scratch_idxs[k];
            if (!level->checkAllocated(scratch_idx))
                level->allocatePatchData(scratch_idx, data_time);
        }
        refine_alg->createSchedule(level, ln - 1, hierarchy, &refine_phys_bdry_op)
            ->fillData(data_time);
    }

    // Interpolate variables.
    NumericVector<double>* X_ghost_vec =
        d_fe_data_manager->buildGhostedCoordsVector(/*localize_data*/ true);
    for (unsigned int k = 0; k < num_eulerian_vars; ++k)
    {
        System* system = d_scalar_interp_var_systems[k];
        const std::string& system_name = system->name();
        const int scratch_idx = d_scalar_interp_scratch_idxs[k];
        d_fe_data_manager->interp(scratch_idx,
                                  *system->solution,
                                  *X_ghost_vec,
                                  system_name,
                                  d_scalar_interp_specs[k]);
    }

    // Deallocate Eulerian scratch space.
    for (int ln = coarsest_ln; ln <= finest_ln; ++ln)
    {
        Pointer<PatchLevel<NDIM> > level = hierarchy->getPatchLevel(ln);
        for (unsigned int k = 0; k < num_eulerian_vars; ++k)
        {
            const int scratch_idx = d_scalar_interp_scratch_idxs[k];
            level->deallocatePatchData(scratch_idx);
        }
    }
    return;
} // interpolateVariables