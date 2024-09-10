	void Unbind(UJavascriptDelegate* DelegateObject)
	{
		static FName NAME_Fire("Fire");

		if (WeakObject.IsValid())
		{
			if (auto p = Cast<UMulticastDelegateProperty>(Property))
			{
				FScriptDelegate Delegate;
				Delegate.BindUFunction(DelegateObject, NAME_Fire);

				auto Target = p->GetPropertyValuePtr_InContainer(WeakObject.Get());
				Target->Remove(Delegate);
			}
			else if (auto p = Cast<UDelegateProperty>(Property))
			{
				auto Target = p->GetPropertyValuePtr_InContainer(WeakObject.Get());
				Target->Clear();
			}
		}

		DelegateObject->JavascriptDelegate = nullptr;
		DelegateObject->RemoveFromRoot();
		DelegateObjects.Remove(DelegateObject);

		if (!bAbandoned)
		{
			functions.Remove(DelegateObject->UniqueId);
		}
	}