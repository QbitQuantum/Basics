	HManagedResource ManagedResource::create(MonoObject* managedResource)
	{
		SPtr<ManagedResource> newRes = bs_core_ptr<ManagedResource>(new (bs_alloc<ManagedResource>()) ManagedResource(managedResource));
		newRes->_setThisPtr(newRes);
		newRes->initialize();

		HManagedResource handle = static_resource_cast<ManagedResource>(gResources()._createResourceHandle(newRes));
		newRes->setHandle(managedResource, handle);

		return handle;
	}