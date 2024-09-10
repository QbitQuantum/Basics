	SPtr<VertexDeclaration> HardwareBufferManager::createVertexDeclaration(const Vector<VertexElement>& elements,
		GpuDeviceFlags deviceMask)
	{
		VertexDeclarationKey key(elements);

		auto iterFind = mCachedDeclarations.find(key);
		if (iterFind != mCachedDeclarations.end())
			return iterFind->second;

		SPtr<VertexDeclaration> declPtr = createVertexDeclarationInternal(elements, deviceMask);
		declPtr->initialize();

		mCachedDeclarations[key] = declPtr;
		return declPtr;
	}