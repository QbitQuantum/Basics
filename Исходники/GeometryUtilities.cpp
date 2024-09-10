// Generates a quad from a position, size and colour.
void GeometryUtilities::GenerateQuad(Vertex* vertices, int* indices, const Vector2f& origin, const Vector2f& dimensions, const Colourb& colour, int index_offset)
{
	GenerateQuad(vertices, indices, origin, dimensions, colour, Vector2f(0, 0), Vector2f(1, 1), index_offset);
}