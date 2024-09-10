static T	*DupSerializable(const T *in) throw(NLMISC::EStream)
{
	NLMISC::CMemStream ms;
	nlassert(!ms.isReading());
	T *nonConstIn = const_cast<T *>(in);
	TSerializePolicy::serial(nonConstIn, ms);
	std::vector<uint8> datas(ms.length());
	std::copy(ms.buffer(), ms.buffer() + ms.length(), datas.begin());
	ms.resetPtrTable();
	ms.invert();
	ms.fill(&datas[0], (uint)datas.size());
	nlassert(ms.isReading());
	T *newObj = NULL;
	TSerializePolicy::serial(newObj, ms);
	return newObj;
}