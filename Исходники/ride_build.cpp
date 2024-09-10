void RideBuildWindow::SelectorMouseButtonEvent(uint8 state)
{
	if (!IsLeftClick(state)) return;

	if (this->selector.area.width != 1 || this->selector.area.height != 1) return;

	ShopInstance *si = static_cast<ShopInstance *>(this->instance);
	SmallRideInstance inst_number = static_cast<SmallRideInstance>(this->instance->GetIndex());
	uint8 entrances = si->GetEntranceDirections(si->vox_pos);

	Voxel *v = _world.GetCreateVoxel(si->vox_pos, true);
	assert(v != nullptr && v->GetInstance() == SRI_FREE);
	v->SetInstance(inst_number);
	v->SetInstanceData(entrances);

	_rides_manager.NewInstanceAdded(inst_number);
	AddRemovePathEdges(si->vox_pos, PATH_EMPTY, entrances, false, PAS_QUEUE_PATH);

	this->instance = nullptr; // Delete this window, and
	si = nullptr; // (Also clean the copy of the pointer.)
	delete this;

	ShowShopManagementGui(inst_number); // Open gui for the new shop.
}