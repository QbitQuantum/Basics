void UNIX_ApplicationSystemDirectoryFixture::Run()
{
	CIMName className("UNIX_ApplicationSystemDirectory");
	CIMNamespaceName nameSpace("root/cimv2");
	UNIX_ApplicationSystemDirectory _p;
	UNIX_ApplicationSystemDirectoryProvider _provider;
	Uint32 propertyCount;
	CIMOMHandle omHandle;
	_provider.initialize(omHandle);
	_p.initialize();

	for(int pIndex = 0; _p.load(pIndex); pIndex++)
	{
		CIMInstance instance = _provider.constructInstance(className,
					nameSpace,
					_p);
		CIMObjectPath path = instance.getPath();
		cout << path.toString() << endl;
		propertyCount = instance.getPropertyCount();
		for(Uint32 i = 0; i < propertyCount; i++)
		{

			CIMProperty propertyItem = instance.getProperty(i);
			if (propertyItem.getType() == CIMTYPE_REFERENCE) {
				CIMValue subValue = propertyItem.getValue();
				CIMInstance subInstance;
				subValue.get(subInstance);
				CIMObjectPath subPath = subInstance.getPath();
				cout << "	Name: " << propertyItem.getName().getString() << ": " << subPath.toString() << endl;
				Uint32 subPropertyCount = subInstance.getPropertyCount();
				for(Uint32 j = 0; j < subPropertyCount; j++)
				{
					CIMProperty subPropertyItem = subInstance.getProperty(j);
					cout << "		Name: " << subPropertyItem.getName().getString() << " - Value: " << subPropertyItem.getValue().toString() << endl;
				}
			}
			else {
				cout << "	Name: " << propertyItem.getName().getString() << " - Value: " << propertyItem.getValue().toString() << endl;
			}

		}
		cout << "------------------------------------" << endl;
		cout << endl;
	}

	_p.finalize();
	
}