wxObject* wxFBManager::GetParent( wxObject* wxobject )
{
	CHECK_VISUAL_EDITOR( NULL )

	CHECK_WX_OBJECT( NULL )

	PObjectBase obj = m_visualEdit->GetObjectBase( wxobject );

	CHECK_OBJECT_BASE( NULL )

	return m_visualEdit->GetWxObject( obj->GetParent() );
}