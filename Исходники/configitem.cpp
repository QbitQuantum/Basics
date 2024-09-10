/**
 * Commits the configuration item by creating a DynamicObject
 * object.
 *
 * @returns The DynamicObject that was created/updated.
 */
DynamicObject::Ptr ConfigItem::Commit(bool discard)
{
	ASSERT(!OwnsLock());

#ifdef _DEBUG
	Log(LogDebug, "ConfigItem")
	    << "Commit called for ConfigItem Type=" << GetType() << ", Name=" << GetName();
#endif /* _DEBUG */

	/* Make sure the type is valid. */
	Type::Ptr type = Type::GetByName(GetType());
	ASSERT(type && Type::GetByName("DynamicObject")->IsAssignableFrom(type));

	if (IsAbstract())
		return DynamicObject::Ptr();

	DynamicObject::Ptr dobj = static_pointer_cast<DynamicObject>(type->Instantiate());

	dobj->SetDebugInfo(m_DebugInfo);
	dobj->SetTypeName(m_Type);
	dobj->SetZone(m_Zone);

	Dictionary::Ptr locals = new Dictionary();
	locals->Set("__parent", m_Scope);
	m_Scope.reset();

	dobj->SetParentScope(locals);
	locals.reset();

	dobj->SetName(m_Name);

	DebugHint debugHints;

	try {
		m_Expression->Evaluate(dobj, &debugHints);
	} catch (const ConfigError& ex) {
		const DebugInfo *di = boost::get_error_info<errinfo_debuginfo>(ex);
		ConfigCompilerContext::GetInstance()->AddMessage(true, ex.what(), di ? *di : DebugInfo());
	} catch (const std::exception& ex) {
		ConfigCompilerContext::GetInstance()->AddMessage(true, DiagnosticInformation(ex));
	}

	if (discard)
		m_Expression.reset();

	dobj->SetParentScope(Object::Ptr());

	String name = m_Name;

	NameComposer *nc = dynamic_cast<NameComposer *>(type.get());

	if (nc) {
		name = nc->MakeName(m_Name, dobj);

		if (name.IsEmpty())
			BOOST_THROW_EXCEPTION(std::runtime_error("Could not determine name for object"));
	}

	if (name != m_Name)
		dobj->SetShortName(m_Name);

	dobj->SetName(name);

	Dictionary::Ptr attrs = Serialize(dobj, FAConfig);

	Dictionary::Ptr persistentItem = new Dictionary();

	persistentItem->Set("type", GetType());
	persistentItem->Set("name", GetName());
	persistentItem->Set("properties", attrs);
	persistentItem->Set("debug_hints", debugHints.ToDictionary());

	ConfigCompilerContext::GetInstance()->WriteObject(persistentItem);
	persistentItem.reset();

	ConfigType::Ptr ctype = ConfigType::GetByName(GetType());

	if (!ctype)
		ConfigCompilerContext::GetInstance()->AddMessage(false, "No validation type found for object '" + GetName() + "' of type '" + GetType() + "'");
	else {
		TypeRuleUtilities utils;

		try {
			attrs->Remove("name");
			ctype->ValidateItem(GetName(), attrs, GetDebugInfo(), &utils);
		} catch (const ConfigError& ex) {
			const DebugInfo *di = boost::get_error_info<errinfo_debuginfo>(ex);
			ConfigCompilerContext::GetInstance()->AddMessage(true, ex.what(), di ? *di : DebugInfo());
		} catch (const std::exception& ex) {
			ConfigCompilerContext::GetInstance()->AddMessage(true, DiagnosticInformation(ex));
		}
	}

	dobj->Register();

	m_Object = dobj;

	return dobj;
}