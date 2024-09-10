ContentControl::ContentControl ()
{
	SetContentSetsParent (true);
	SetObjectType (Type::CONTENTCONTROL);

	ManagedTypeInfo *type_info = g_new (ManagedTypeInfo, 1);
	type_info->Initialize (GetObjectType (), "System.Windows.Controls.ContentControl");
	SetDefaultStyleKey (type_info);
	ManagedTypeInfo::Free (type_info);
}