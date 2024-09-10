void CDiagramEntityContainer::RightAlignSelected()
{
	if( GetSelectCount() > 1 )
	{
		CDiagramEntity* obj = GetSelectedObject();
		if( obj )
		{
			double right = obj->GetRight();
			int count = 0;
			while (obj = GetAt( count++ ))
			{
				if (!obj->IsSelected()) continue;
				double width = obj->GetRight() - obj->GetLeft();
				double left = right - width;
				obj->SetRect( left, obj->GetTop(), right, obj->GetBottom() );
			}

		}
		SetModified( TRUE );
	}
}