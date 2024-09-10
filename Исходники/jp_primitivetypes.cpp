jobject JPPrimitiveType::convertToJavaObject(HostRef* obj)
{
	JPCleaner cleaner;
	JPTypeName tname = getObjectType();
	JPClass* c = JPTypeManager::findClass(tname);

	jclass jc = c->getClass();
	cleaner.addLocal(jc);

	vector<HostRef*> args(1);
	args[0] = obj;

	JPObject* o = c->newInstance(args);
	jobject res = o->getObject();
	delete o;

	return res;
}