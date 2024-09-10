bool CTimeBarListModel::SetValueByRow( const wxVariant &variant, unsigned int row, unsigned int col )
{
    if (row < m_textColValues.GetCount())
    {
        switch ( col )
        {
        case Col_EditableText:
            m_textColValues[row] = variant.GetString();
            break;

        case Col_Visible:
            m_view[row] = variant.GetChar();
            break;

        case Col_Lock:
            m_lock[row] = variant.GetChar();
            break;

        case Col_Max:
        default:
            wxFAIL_MSG( _T("invalid column") );
            break;
        }
    }
    return false;
}