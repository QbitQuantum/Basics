UndoStep* DeleteObjectsUndoStep::undo()
{
	int const part_index = getPartIndex();
	
	AddObjectsUndoStep* undo_step = new AddObjectsUndoStep(map);
	undo_step->setPartIndex(part_index);
	
	// Make sure to delete the objects in the right order so the other objects' indices stay valid
	std::sort(modified_objects.begin(), modified_objects.end(), std::greater<int>());
	
	MapPart* part = map->getPart(part_index);
	int size = (int)modified_objects.size();
	for (int i = 0; i < size; ++i)
	{
		undo_step->addObject(modified_objects[i], part->getObject(modified_objects[i]));
		part->deleteObject(modified_objects[i], true);
	}
	
	return undo_step;
}