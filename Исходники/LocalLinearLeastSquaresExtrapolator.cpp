void LocalLinearLeastSquaresExtrapolator::extrapolateElement(
    std::size_t const element_index,
    const unsigned num_components,
    ExtrapolatableElementCollection const& extrapolatables,
    const double t,
    GlobalVector const& current_solution,
    LocalToGlobalIndexMap const& dof_table,
    GlobalVector& counts)
{
    auto const& integration_point_values =
        extrapolatables.getIntegrationPointValues(
            element_index, t, current_solution, dof_table,
            _integration_point_values_cache);

    auto const& N_0 = extrapolatables.getShapeMatrix(element_index, 0);
    auto const num_nodes = static_cast<unsigned>(N_0.cols());
    auto const num_values =
        static_cast<unsigned>(integration_point_values.size());

    if (num_values % num_components != 0)
        OGS_FATAL(
            "The number of computed integration point values is not divisable "
            "by the number of num_components. Maybe the computed property is "
            "not a %d-component vector for each integration point.",
            num_components);

    // number of integration points in the element
    const auto num_int_pts = num_values / num_components;

    if (num_int_pts < num_nodes)
        OGS_FATAL(
            "Least squares is not possible if there are more nodes than"
            "integration points.");

    auto const pair_it_inserted = _qr_decomposition_cache.emplace(
        std::make_pair(num_nodes, num_int_pts), CachedData{});

    auto& cached_data = pair_it_inserted.first->second;
    if (pair_it_inserted.second)
    {
        DBUG("Computing new singular value decomposition");

        // interpolation_matrix * nodal_values = integration_point_values
        // We are going to pseudo-invert this relation now using singular value
        // decomposition.
        auto& interpolation_matrix = cached_data.A;
        interpolation_matrix.resize(num_int_pts, num_nodes);

        interpolation_matrix.row(0) = N_0;
        for (unsigned int_pt = 1; int_pt < num_int_pts; ++int_pt)
        {
            auto const& shp_mat =
                extrapolatables.getShapeMatrix(element_index, int_pt);
            assert(shp_mat.cols() == num_nodes);

            // copy shape matrix to extrapolation matrix row-wise
            interpolation_matrix.row(int_pt) = shp_mat;
        }

        // JacobiSVD is extremely reliable, but fast only for small matrices.
        // But we usually have small matrices and we don't compute very often.
        // Cf.
        // http://eigen.tuxfamily.org/dox/group__TopicLinearAlgebraDecompositions.html
        //
        // Decomposes interpolation_matrix = U S V^T.
        Eigen::JacobiSVD<Eigen::MatrixXd> svd(
            interpolation_matrix, Eigen::ComputeThinU | Eigen::ComputeThinV);

        auto const& S = svd.singularValues();
        auto const& U = svd.matrixU();
        auto const& V = svd.matrixV();

        // Compute and save the pseudo inverse V * S^{-1} * U^T.
        auto const rank = svd.rank();
        assert(rank == num_nodes);

        // cf. http://eigen.tuxfamily.org/dox/JacobiSVD_8h_source.html
        cached_data.A_pinv.noalias() = V.leftCols(rank) *
                                       S.head(rank).asDiagonal().inverse() *
                                       U.leftCols(rank).transpose();
    }
    else if (cached_data.A.row(0) != N_0)
    {
        OGS_FATAL("The cached and the passed shapematrices differ.");
    }

    auto const& global_indices =
        _dof_table_single_component(element_index, 0).rows;

    if (num_components == 1)
    {
        auto const integration_point_values_vec =
            MathLib::toVector(integration_point_values);

        // Apply the pre-computed pseudo-inverse.
        Eigen::VectorXd const nodal_values =
            cached_data.A_pinv * integration_point_values_vec;

        // TODO does that give rise to PETSc problems? E.g., writing to ghost
        // nodes? Furthermore: Is ghost nodes communication necessary for PETSc?
        _nodal_values->add(global_indices, nodal_values);
        counts.add(global_indices,
                   std::vector<double>(global_indices.size(), 1.0));
    }
    else
    {
        auto const integration_point_values_mat = MathLib::toMatrix(
            integration_point_values, num_components, num_int_pts);

        // Apply the pre-computed pseudo-inverse.
        Eigen::MatrixXd const nodal_values =
            cached_data.A_pinv * integration_point_values_mat.transpose();

        std::vector<GlobalIndexType> indices;
        indices.reserve(num_components * global_indices.size());

        // _nodal_values is ordered location-wise
        for (unsigned comp = 0; comp < num_components; ++comp)
        {
            for (auto i : global_indices)
            {
                indices.push_back(num_components * i + comp);
            }
        }

        // Nodal_values are passed as a raw pointer, because PETScVector and
        // EigenVector implementations differ slightly.
        _nodal_values->add(indices, nodal_values.data());
        counts.add(indices, std::vector<double>(indices.size(), 1.0));
    }
}