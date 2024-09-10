void OutGameScreenModel::AddPrimitive(std::shared_ptr<IDrawablePrimitive> primitive) {
	primitive->accept(*this);
}