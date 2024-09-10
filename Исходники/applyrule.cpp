bool ApplyRule::EvaluateFilter(const Dictionary::Ptr& scope) const
{
	scope->Set("__parent", m_Scope);
	bool result = m_Filter->Evaluate(scope);
	scope->Remove("__parent");
	return result;
}