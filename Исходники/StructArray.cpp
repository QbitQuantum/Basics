void vtStructureArray::GetExtents(DRECT &rect) const
{
	if (GetSize() == 0)
		return;

	rect.SetRect(1E9, -1E9, -1E9, 1E9);

	DRECT rect2;
	int i, size = GetSize();
	for (i = 0; i < size; i++)
	{
		vtStructure *str = GetAt(i);
		if (str->GetExtents(rect2))
			rect.GrowToContainRect(rect2);
	}
}