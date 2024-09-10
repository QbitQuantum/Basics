void UIElement::OnComputedPropertyValueChanging(PropertyValue* pPropertyVal, const Variant& oldValue, const Variant& newValue, bool handled)
{
	if (pPropertyVal->m_dp == get_ShadowTreeProperty())
	{
		// remove old

		UIElement* uielement = get_ShadowTree();

		if (uielement)
		{
			uielement->SetRoot(nullptr);
			uielement->set_Parent(nullptr);
			uielement->set_ParentWindow(nullptr);
		}

		handled = true;
	}

	if (m_elementProvider)
	{
		PROPERTYID propertyId = 0;
		if (pPropertyVal->m_dp == Window::get_TitleTextProperty())
		{
			propertyId = UIA_NamePropertyId;
		}

		HRESULT hr;
		if (propertyId)
		{
			hr = UiaRaiseAutomationPropertyChangedEvent(m_elementProvider, propertyId, oldValue, newValue);
		}
	}

	baseClass::OnComputedPropertyValueChanging(pPropertyVal, oldValue, newValue, handled);
}