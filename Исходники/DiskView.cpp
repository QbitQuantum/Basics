	virtual bool Visit(BPartition* partition, int32 level)
	{
		if (!partition->Parent()
			|| !fViewMap.ContainsKey(partition->Parent()->ID()))
			return false;

		// calculate size factor within parent frame
		off_t offset = partition->Offset();
//		off_t parentOffset = partition->Parent()->Offset();
		off_t size = partition->Size();
		off_t parentSize = partition->Parent()->Size();
		double scale = (double)size / parentSize;

		BString name = partition->ContentName();
		if (name.Length() == 0) {
			if (partition->CountChildren() > 0)
				name << partition->Type();
			else {
				char buffer[64];
				snprintf(buffer, 64, B_TRANSLATE("Partition %ld"),
					partition->ID());
				name << buffer;
			}
		}
		partition_id id = partition->ID();
		PartitionView* view = new PartitionView(name.String(), scale, offset,
			level, id);
		view->SetSelected(id == fSelectedPartition);
		PartitionView* parent = fViewMap.Get(partition->Parent()->ID());
		BGroupLayout* layout = parent->GroupLayout();
		layout->AddView(_FindInsertIndex(view, layout), view, scale);

		fViewMap.Put(partition->ID(), view);
		_AddSpaces(partition, view);

		return false;
	}