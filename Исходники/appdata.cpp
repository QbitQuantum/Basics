void InsertObjectCmd::DoRestore()
{
	m_parent->RemoveChild(m_object);
	m_object->SetParent(shared_ptr<ObjectBase>());
	m_data->SelectObject(m_oldSelected);
}