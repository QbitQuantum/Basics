//------------------------------------------------------------------------------
void
LocalAssembler::assemble(Eigen::MatrixXd& A,
                         UFC& ufc,
                         const std::vector<double>& vertex_coordinates,
                         ufc::cell& ufc_cell,
                         const Cell& cell,
                         const MeshFunction<std::size_t>* cell_domains,
                         const MeshFunction<std::size_t>* exterior_facet_domains,
                         const MeshFunction<std::size_t>* interior_facet_domains)
{
    // Clear tensor
    A.setZero();

    cell.get_cell_data(ufc_cell);

    // Assemble contributions from cell integral
    assemble_cell(A, ufc, vertex_coordinates, ufc_cell, cell, cell_domains);

    // Assemble contributions from facet integrals
    for (FacetIterator facet(cell); !facet.end(); ++facet)
    {
        ufc_cell.local_facet = facet.pos();
        if (facet->num_entities(cell.dim()) == 2)
        {
            assemble_interior_facet(A, ufc, vertex_coordinates, ufc_cell, cell,
                                    *facet, facet.pos(), interior_facet_domains);
        }
        else
        {
            assemble_exterior_facet(A, ufc, vertex_coordinates, ufc_cell, cell,
                                    *facet, facet.pos(), exterior_facet_domains);
        }
    }
}