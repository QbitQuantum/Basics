void CutTool::pathFinished(PathObject* split_path)
{
	Map* map = this->map();
	
	// Get path endpoint and check if it is on the area boundary
	const MapCoordVector& path_coords = split_path->getRawCoordinateVector();
	MapCoord path_end = path_coords.at(path_coords.size() - 1);
	
	PathObject* edited_path = reinterpret_cast<PathObject*>(edit_object);
	PathCoord end_path_coord;
	float distance_sq;
	edited_path->calcClosestPointOnPath(MapCoordF(path_end), distance_sq, end_path_coord);
	
	float click_tolerance_map = 0.001 * edit_widget->getMapView()->pixelToLength(clickTolerance());
	if (distance_sq > click_tolerance_map*click_tolerance_map)
	{
		QMessageBox::warning(window(), tr("Error"), tr("The split line must end on the area boundary!"));
		pathAborted();
		return;
	}
	else if (drag_part_index != edited_path->findPartIndexForIndex(end_path_coord.index))
	{
		QMessageBox::warning(window(), tr("Error"), tr("Start and end of the split line are at different parts of the object!"));
		pathAborted();
		return;
	}
	else if (drag_start_len == end_path_coord.clen)
	{
		QMessageBox::warning(window(), tr("Error"), tr("Start and end of the split line are at the same position!"));
		pathAborted();
		return;
	}
	
	Q_ASSERT(split_path->parts().size() == 1);
	split_path->parts().front().setClosed(false);
	split_path->setCoordinate(split_path->getCoordinateCount() - 1, MapCoord(end_path_coord.pos));
	
	// Do the splitting
	const double split_threshold = 0.01;
	
	MapPart* part = map->getCurrentPart();
	AddObjectsUndoStep* add_step = new AddObjectsUndoStep(map);
	add_step->addObject(part->findObjectIndex(edited_path), edited_path);
	map->removeObjectFromSelection(edited_path, false);
	map->deleteObject(edited_path, true);
	map->setObjectsDirty();
	
	DeleteObjectsUndoStep* delete_step = new DeleteObjectsUndoStep(map);
	
	PathObject* holes = nullptr; // if the edited path contains holes, they are saved in this temporary object
	if (edited_path->parts().size() > 1)
	{
		holes = edited_path->duplicate()->asPath();
		holes->deletePart(0);
	}
	
	bool ok; Q_UNUSED(ok); // "ok" is only used in Q_ASSERT.
	PathObject* parts[2] = { new PathObject { edited_path->parts().front() }, nullptr };
	const PathPart& drag_part = edited_path->parts()[drag_part_index];
	if (drag_part.isClosed())
	{
		parts[1] = new PathObject { *parts[0] };
		
		parts[0]->changePathBounds(drag_part_index, drag_start_len, end_path_coord.clen);
		ok = parts[0]->connectIfClose(split_path, split_threshold);
		Q_ASSERT(ok);

		parts[1]->changePathBounds(drag_part_index, end_path_coord.clen, drag_start_len);
		ok = parts[1]->connectIfClose(split_path, split_threshold);
		Q_ASSERT(ok);
	}
	else
	{
		float min_cut_pos = qMin(drag_start_len, end_path_coord.clen);
		float max_cut_pos = qMax(drag_start_len, end_path_coord.clen);
		float path_len = drag_part.path_coords.back().clen;
		if (min_cut_pos <= 0 && max_cut_pos >= path_len)
		{
			ok = parts[0]->connectIfClose(split_path, split_threshold);
			Q_ASSERT(ok);
			
			parts[1] = new PathObject { *split_path };
			parts[1]->setSymbol(edited_path->getSymbol(), false);
		}
		else if (min_cut_pos <= 0 || max_cut_pos >= path_len)
		{
			float cut_pos = (min_cut_pos <= 0) ? max_cut_pos : min_cut_pos;
			parts[1] = new PathObject { *parts[0] };
			
			parts[0]->changePathBounds(drag_part_index, 0, cut_pos);
			ok = parts[0]->connectIfClose(split_path, split_threshold);
			Q_ASSERT(ok);
			
			parts[1]->changePathBounds(drag_part_index, cut_pos, path_len);
			ok = parts[1]->connectIfClose(split_path, split_threshold);
			Q_ASSERT(ok);
		}
		else
		{
			parts[1] = new PathObject { *parts[0] };
			PathObject* temp_path = new PathObject { *parts[0] };
			
			parts[0]->changePathBounds(drag_part_index, min_cut_pos, max_cut_pos);
			ok = parts[0]->connectIfClose(split_path, split_threshold);
			Q_ASSERT(ok);
			
			parts[1]->changePathBounds(drag_part_index, 0, min_cut_pos);
			ok = parts[1]->connectIfClose(split_path, split_threshold);
			Q_ASSERT(ok);
			
			temp_path->changePathBounds(drag_part_index, max_cut_pos, path_len);
			ok = parts[1]->connectIfClose(temp_path, split_threshold);
			Q_ASSERT(ok);
			
			delete temp_path;
		}
	}
	
	// If the object had holes, check into which parts they go
	if (holes)
	{
		for (const auto& hole : holes->parts())
		{
			PathPartVector::size_type part_index = (parts[0]->isPointOnPath(MapCoordF(holes->getCoordinate(hole.first_index)), 0, false, false) != Symbol::NoSymbol) ? 0 : 1;
			parts[part_index]->getCoordinate(parts[part_index]->getCoordinateCount() - 1).setHolePoint(true);
			parts[part_index]->appendPathPart(hole);
		}
	}
	
	for (auto& object : parts)
	{
		map->addObject(object);
		delete_step->addObject(part->findObjectIndex(object));
		map->addObjectToSelection(object, false);
	}
	
	CombinedUndoStep* undo_step = new CombinedUndoStep(map);
	undo_step->push(add_step);
	undo_step->push(delete_step);
	map->push(undo_step);
	map->setObjectsDirty();
	
	pathAborted();
}