PObjectBase MenuEditor::GetMenu(long& n, PObjectDatabase base, bool isSubMenu)
{
	// Get item from list control
    wxString label, shortcut, id, name, help, kind;
	PObjectBase menu;
    GetItem(n, label, shortcut, id, name, help, kind, &menu);

	bool createNew = true;
	if ( menu )
	{
		createNew = ( menu->GetClassName() != (isSubMenu ? wxT("submenu") : wxT("wxMenu")) );
	}

    // preserve original menu if the object types match
    // this preserves properties that are not exposed in the menu editor - like C++ scope
    if ( createNew  )
    {
		PObjectInfo info = base->GetObjectInfo(isSubMenu ? wxT("submenu") : wxT("wxMenu") );
		menu = base->NewObject(info);
    }


    label.Trim(true); label.Trim(false);
    menu->GetProperty( wxT("label") )->SetValue(label);
    menu->GetProperty( wxT("name") )->SetValue(name);

    int ident = GetItemIdentation(n);
    n++;
    while (n < m_menuList->GetItemCount() && GetItemIdentation(n) > ident)
    {
    	PObjectBase menuitem;
        GetItem(n, label, shortcut, id, name, help, kind, &menuitem);

		createNew = true;

        label.Trim(true); label.Trim(false);
        if (label == wxT("---"))
        {
        	if ( menuitem )
        	{
        		createNew = ( menuitem->GetClassName() != wxT("separator") );
        	}

        	if ( createNew )
        	{
				PObjectInfo info = base->GetObjectInfo( wxT("separator") );
				menuitem = base->NewObject(info);
        	}
            menu->AddChild(menuitem);
            menuitem->SetParent(menu);
            n++;
        }
        else if (HasChildren(n))
        {
            PObjectBase child = GetMenu(n, base);
            menu->AddChild(child);
            child->SetParent(menu);
        }
        else
        {
        	if ( menuitem )
        	{
        		createNew = ( menuitem->GetClassName() != wxT("wxMenuItem") );
        	}

        	if ( createNew )
        	{
				PObjectInfo info = base->GetObjectInfo( wxT("wxMenuItem") );
				menuitem = base->NewObject(info);
        	}
            menuitem->GetProperty( wxT("label") )->SetValue(label);
            menuitem->GetProperty( wxT("shortcut") )->SetValue(shortcut);
            menuitem->GetProperty( wxT("name") )->SetValue(name);
			menuitem->GetProperty( wxT("help") )->SetValue(help);
            menuitem->GetProperty( wxT("id") )->SetValue(id);
            menuitem->GetProperty( wxT("kind") )->SetValue(kind);
            menu->AddChild(menuitem);
            menuitem->SetParent(menu);
            n++;
        }
    }

    return menu;
}