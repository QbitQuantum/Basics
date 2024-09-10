MappingPath<EdgeId> GetRCToMappingPath(Graph &g, MappingPath<EdgeId> map_path, size_t seq_size){
	vector<EdgeId> rc_path_seq;
	vector<MappingRange> rc_map_ranges;
	for(size_t i = 0; i < map_path.size(); i++){
		// computing edges sequence
		EdgeId cur_edge = map_path[i].first;
		rc_path_seq.insert(rc_path_seq.begin(), g.conjugate(cur_edge));

		// computing initial ranges
		Range init_range = map_path[i].second.initial_range;
		Range rc_init_range(seq_size - init_range.end_pos, seq_size - init_range.start_pos);

		// computing mapped ranges
		size_t edge_length = g.length(cur_edge);
		Range map_range = map_path[i].second.mapped_range;
		Range rc_map_range(edge_length - map_range.end_pos, edge_length - map_range.start_pos);

		rc_map_ranges.insert(rc_map_ranges.begin(), MappingRange(rc_init_range, rc_map_range));
	}

	return MappingPath<EdgeId>(rc_path_seq, rc_map_ranges);
}