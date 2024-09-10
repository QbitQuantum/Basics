IShape* NodeFactory::CreateRectBorder(const Size2F& rectSize, const Color4F& color)
{
	auto mesh = MeshFactory::Instance().CreateShapeQuadMesh(rectSize, color);
	RETURN_NULL_IF_NULL(mesh);
	auto material = MaterialFactory::Instance().CreateShape(MEDUSA_PREFIX(Shape_WireFrame));
	material->SetDrawMode(GraphicsDrawMode::LineStrip);

	IShape* sprite = new IShape();
	sprite->Initialize();
	sprite->SetSizeToContent(SizeToContent::Mesh);

	sprite->SetMesh(mesh);
	sprite->SetMaterial(material);
	sprite->SetSize(rectSize);
	return sprite;
}