 void WidgetTableWidget::UpdateTableImpl()
 {
     SettlerMap::Iterator iter = _settlers.Begin();
     for (; !!iter; ++iter)
     {
         Rect clientrect = ClientRect( iter.Key().x, iter.Key().y );
         Rect boundrect  = iter.Value()._settler->GetBoundingRect();
         Rect area = boundrect.Align( clientrect, iter.Value()._alignment ) ;
         Widget *p_child = iter.Value()._settler;
         DirtyLock guard_dirty(p_child);
         p_child->SetPosition( Pos( area.GetX(), area.GetY() ) );
     }
     SetDimensions( GetWidth(), GetHeight() );
 }