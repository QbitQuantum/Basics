void NodeBasedCellPopulation<DIM>::WriteVtkResultsToFile(const std::string& rDirectory)
{
#ifdef CHASTE_VTK
    std::stringstream time;
    time << SimulationTime::Instance()->GetTimeStepsElapsed();
    VtkMeshWriter<DIM, DIM> mesh_writer(rDirectory, "results_"+time.str(), false);

    // Make sure the nodes are ordered contiguously in memory.
    NodeMap map(1 + this->mpNodesOnlyMesh->GetMaximumNodeIndex());
    this->mpNodesOnlyMesh->ReMesh(map);

    mesh_writer.SetParallelFiles(*mpNodesOnlyMesh);

    unsigned num_nodes = GetNumNodes();
    std::vector<double> cell_types(num_nodes);
    std::vector<double> cell_ancestors(num_nodes);
    std::vector<double> cell_mutation_states(num_nodes);
    std::vector<double> cell_ages(num_nodes);
    std::vector<double> cell_cycle_phases(num_nodes);
    std::vector<double> cell_radii(num_nodes);
    std::vector<std::vector<double> > cellwise_data;
    std::vector<double> rank(num_nodes);

    unsigned num_cell_data_items = 0;
    std::vector<std::string> cell_data_names;

    // We assume that the first cell is representative of all cells
    if (num_nodes > 0)
    {
        num_cell_data_items = this->Begin()->GetCellData()->GetNumItems();
        cell_data_names = this->Begin()->GetCellData()->GetKeys();
    }

    for (unsigned var=0; var<num_cell_data_items; var++)
    {
        std::vector<double> cellwise_data_var(num_nodes);
        cellwise_data.push_back(cellwise_data_var);
    }

    // Loop over cells
    for (typename AbstractCellPopulation<DIM>::Iterator cell_iter = this->Begin();
         cell_iter != this->End();
         ++cell_iter)
    {
        // Get the node index corresponding to this cell
        unsigned global_index = this->GetLocationIndexUsingCell(*cell_iter);

        Node<DIM>* p_node = this->GetNode(global_index);

        unsigned node_index = this->rGetMesh().SolveNodeMapping(global_index);

        if (this-> template HasWriter<CellAncestorWriter>())
        {
            double ancestor_index = (cell_iter->GetAncestor() == UNSIGNED_UNSET) ? (-1.0) : (double)cell_iter->GetAncestor();
            cell_ancestors[node_index] = ancestor_index;
        }
        if (this-> template HasWriter<CellProliferativeTypesWriter>())
        {
            double cell_type = cell_iter->GetCellProliferativeType()->GetColour();
            cell_types[node_index] = cell_type;
        }
        if (this-> template HasWriter<CellMutationStatesCountWriter>())
        {
            double mutation_state = cell_iter->GetMutationState()->GetColour();

            CellPropertyCollection collection = cell_iter->rGetCellPropertyCollection();
            CellPropertyCollection label_collection = collection.GetProperties<CellLabel>();

            if (label_collection.GetSize() == 1)
            {
                boost::shared_ptr<CellLabel> p_label = boost::static_pointer_cast<CellLabel>(label_collection.GetProperty());
                mutation_state = p_label->GetColour();
            }

            cell_mutation_states[node_index] = mutation_state;
        }
        if (this-> template HasWriter<CellAgesWriter>())
        {
            double age = cell_iter->GetAge();
            cell_ages[node_index] = age;
        }
        if (this-> template HasWriter<CellProliferativePhasesWriter>())
        {
            double cycle_phase = cell_iter->GetCellCycleModel()->GetCurrentCellCyclePhase();
            cell_cycle_phases[node_index] = cycle_phase;
        }
        if (this-> template HasWriter<CellVolumesWriter>())
        {
            double cell_radius = p_node->GetRadius();
            cell_radii[node_index] = cell_radius;
        }

        for (unsigned var=0; var<num_cell_data_items; var++)
        {
            cellwise_data[var][node_index] = cell_iter->GetCellData()->GetItem(cell_data_names[var]);
        }

        rank[node_index] = (PetscTools::GetMyRank());
    }

    mesh_writer.AddPointData("Process rank", rank);

    if (this-> template HasWriter<CellProliferativeTypesWriter>())
    {
        mesh_writer.AddPointData("Cell types", cell_types);
    }
    if (this-> template HasWriter<CellAncestorWriter>())
    {
        mesh_writer.AddPointData("Ancestors", cell_ancestors);
    }
    if (this-> template HasWriter<CellMutationStatesCountWriter>())
    {
        mesh_writer.AddPointData("Mutation states", cell_mutation_states);
    }
    if (this-> template HasWriter<CellAgesWriter>())
    {
        mesh_writer.AddPointData("Ages", cell_ages);
    }
    if (this-> template HasWriter<CellProliferativePhasesWriter>())
    {
        mesh_writer.AddPointData("Cycle phases", cell_cycle_phases);
    }
    if (this-> template HasWriter<CellVolumesWriter>())
    {
        mesh_writer.AddPointData("Cell radii", cell_radii);
    }
    if (num_cell_data_items > 0)
    {
        for (unsigned var=0; var<cellwise_data.size(); var++)
        {
            mesh_writer.AddPointData(cell_data_names[var], cellwise_data[var]);
        }
    }

    mesh_writer.WriteFilesUsingMesh(*mpNodesOnlyMesh);

    *(this->mpVtkMetaFile) << "        <DataSet timestep=\"";
    *(this->mpVtkMetaFile) << SimulationTime::Instance()->GetTimeStepsElapsed();
    *(this->mpVtkMetaFile) << "\" group=\"\" part=\"0\" file=\"results_";
    *(this->mpVtkMetaFile) << SimulationTime::Instance()->GetTimeStepsElapsed();
    *(this->mpVtkMetaFile) << ".vtu\"/>\n";
#endif //CHASTE_VTK
}