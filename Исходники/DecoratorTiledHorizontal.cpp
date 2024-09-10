// Called on a decorator to generate any required per-element data for a newly decorated element.
DecoratorDataHandle DecoratorTiledHorizontal::GenerateElementData(Element* element)
{
	// Initialise the tiles for this element.
	for (int i = 0; i < 3; i++)
		tiles[i].CalculateDimensions(element, *(GetTexture(tiles[i].texture_index)));

	DecoratorTiledHorizontalData* data = new DecoratorTiledHorizontalData(element);

	Vector2f padded_size = element->GetBox().GetSize(Box::PADDING);

	Vector2f left_dimensions = tiles[LEFT].GetDimensions(element);
	Vector2f right_dimensions = tiles[RIGHT].GetDimensions(element);
	Vector2f centre_dimensions = tiles[CENTRE].GetDimensions(element);

	// Scale the tile sizes by the height scale.
	ScaleTileDimensions(left_dimensions, padded_size.y, 1);
	ScaleTileDimensions(right_dimensions, padded_size.y, 1);
	ScaleTileDimensions(centre_dimensions, padded_size.y, 1);

	// Shrink the x-sizes on the left and right tiles if necessary.
	if (padded_size.x < left_dimensions.x + right_dimensions.x)
	{
		float minimum_width = left_dimensions.x + right_dimensions.x;
		left_dimensions.x = padded_size.x * (left_dimensions.x / minimum_width);
		right_dimensions.x = padded_size.x * (right_dimensions.x / minimum_width);
	}

    int num_indices;

	// Generate the geometry for the left tile.
	num_indices = tiles[LEFT].GenerateGeometry(data->geometry[tiles[LEFT].texture_index]->GetVertices(), element, Vector2f(0, 0), left_dimensions, left_dimensions, color_multiplier);
	data->geometry[tiles[LEFT].texture_index]->IncreaseNumIndices(num_indices);

    // Generate the geometry for the centre tiles.
	num_indices = tiles[CENTRE].GenerateGeometry(data->geometry[tiles[CENTRE].texture_index]->GetVertices(), element, Vector2f(left_dimensions.x, 0), Vector2f(padded_size.x - (left_dimensions.x + right_dimensions.x), centre_dimensions.y), centre_dimensions, color_multiplier);
    data->geometry[tiles[CENTRE].texture_index]->IncreaseNumIndices(num_indices);
	
    // Generate the geometry for the right tile.
	num_indices = tiles[RIGHT].GenerateGeometry(data->geometry[tiles[RIGHT].texture_index]->GetVertices(), element, Vector2f(padded_size.x - right_dimensions.x, 0), right_dimensions, right_dimensions, color_multiplier);
    data->geometry[tiles[RIGHT].texture_index]->IncreaseNumIndices(num_indices);

	// Set the textures on the geometry.
	const Texture* texture = NULL;
	int texture_index = 0;
	while ((texture = GetTexture(texture_index)) != NULL)
		data->geometry[texture_index++]->SetTexture(texture);

	return reinterpret_cast<DecoratorDataHandle>(data);
}