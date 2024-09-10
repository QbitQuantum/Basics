const EDA_RECT SCH_FIELD::GetBoundingBox() const
{
    SCH_COMPONENT* parentComponent = (SCH_COMPONENT*) m_Parent;
    int linewidth = ( m_Thickness == 0 ) ? GetDefaultLineThickness() : m_Thickness;

    // We must pass the effective text thickness to GetTextBox
    // when calculating the bounding box
    linewidth = Clamp_Text_PenSize( linewidth, m_Size, m_Bold );

    // Calculate the text bounding box:
    EDA_RECT rect;

    if( m_id == REFERENCE )     // multi units have one letter or more added to reference
    {
        SCH_FIELD text( *this );    // Make a local copy to change text
                                    // because GetBoundingBox() is const
        text.SetText( GetFullyQualifiedText() );
        rect = text.GetTextBox( -1, linewidth );
    }
    else
        rect = GetTextBox( -1, linewidth );

    // Calculate the bounding box position relative to the component:
    wxPoint origin = parentComponent->GetPosition();
    wxPoint pos = m_Pos - origin;
    wxPoint begin = rect.GetOrigin() - origin;
    wxPoint end = rect.GetEnd() - origin;
    RotatePoint( &begin, pos, m_Orient );
    RotatePoint( &end, pos, m_Orient );

    // Due to the Y axis direction, we must mirror the bounding box,
    // relative to the text position:
    begin.y -= pos.y;
    end.y -= pos.y;
    NEGATE( begin.y );
    NEGATE( end.y );
    begin.y += pos.y;
    end.y += pos.y;

    // Now, apply the component transform (mirror/rot)
    begin = parentComponent->GetTransform().TransformCoordinate( begin );
    end = parentComponent->GetTransform().TransformCoordinate( end );
    rect.SetOrigin( begin);
    rect.SetEnd( end);
    rect.Move( origin );
    rect.Normalize();
    return rect;
}