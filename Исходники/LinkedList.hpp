void LinkedList<T>::Unlink(T &obj)
{
	Unlink(&obj);
	if (obj.m_listManaged) {
		delete &obj;
	}
}