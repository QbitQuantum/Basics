std::unique_ptr<Stmt> InstantiationVisitor::clone(Stmt& s)
{
	std::unique_ptr<Stmt> result;
	s.accept(*this);
	swap(result, _stmt);
	return std::move(result);
}