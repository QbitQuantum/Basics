Fvector CALifeMonsterDetailPathManager::draw_level_position	() const
{
	if (path().empty())
		return						(object().Position());

	u32								path_size = path().size();
	if (path_size == 1)
		return						(object().Position());

	VERIFY							(m_path.back() == object().m_tGraphID);

	const GameGraph::CVertex		*current = ai().game_graph().vertex(object().m_tGraphID);
	const GameGraph::CVertex		*next = ai().game_graph().vertex(m_path[path_size - 2]);
	if (current->level_id() != next->level_id())
		return						(object().Position());

	Fvector							current_vertex = current->level_point();
	Fvector							next_vertex = next->level_point();
	Fvector							direction = Fvector().sub(next_vertex,current_vertex);
	direction.normalize				();
	return							(current_vertex.mad(direction,walked_distance()));
}