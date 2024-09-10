map<id_t, vector<Mapping>> PathIndex::parse_translation(const Translation& translation) {

    // We take as a precondition that the translation is replacing a set of old
    // nodes each with a nonempty set of new nodes. So we won't have to combine
    // nodes or parts of nodes.
    
#ifdef debug
    cerr << "Partitioning translation: " << pb2json(translation) << endl;
#endif
    
    // We'll populate this with the mappings that partition each old node.
    map<id_t, vector<Mapping>> old_node_to_new_nodes;
    
    // We know the new Mappings are conceptually nested in the old Mappings, so
    // we can use nested loops.

    // How many bases in the old and new paths are accounted for?
    size_t old_bases = 0;
    size_t new_bases = 0;

    // This represents our index in the new path
    size_t j = 0;    
    
    for(size_t i = 0; i < translation.from().mapping_size(); i++) {
        // For every old mapping
        auto& from_mapping = translation.from().mapping(i);
        
        // Count up its bases
        old_bases += mapping_from_length(from_mapping);
        
        // Grab a reference to the list of replacement mappings
        auto& replacements = old_node_to_new_nodes[from_mapping.position().node_id()];
        
        // We know the old mapping must have at least one new mapping in it
        do {
            // For each mapping in the new path, copy it
            auto to_mapping = translation.to().mapping(j);
            
            if (from_mapping.position().is_reverse()) {
                // Flip its strand if the mapping we're partitioning is backward
                to_mapping.mutable_position()->set_is_reverse(!to_mapping.position().is_reverse());
            }
            
            // Account for its bases
            new_bases += mapping_from_length(to_mapping);
            
            // Copy it into the list for just this from node
            replacements.push_back(to_mapping);
            
            // Look at the next to mapping
            j++;
        } while (j < translation.to().mapping_size() && new_bases < old_bases);
        
        if (from_mapping.position().is_reverse()) {
            // Flip the order of the replacement mappings around
            reverse(replacements.begin(), replacements.end());
        }
        
#ifdef debug
        cerr << "Old node " << from_mapping.position().node_id() << " "
            << from_mapping.position().is_reverse() << " becomes: " << endl;
        for(auto& m : old_node_to_new_nodes[from_mapping.position().node_id()]) {
            cerr << "\t" << pb2json(m) << endl;
        }
#endif
    }
    
    return old_node_to_new_nodes;

}