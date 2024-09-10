//---------------------------------------------------------
bool CSG_PointCloud::_Get_Field_Value(char *pPoint, int iField, CSG_String &Value)	const
{
    if( pPoint && iField >= 0 && iField < m_nFields )
    {
        switch( m_Field_Type[iField] )
        {
        default:
            Value.Printf("%f", _Get_Field_Value(pPoint, iField));
            break;

        case SG_DATATYPE_Date:
        case SG_DATATYPE_String:
        {
            char	s[PC_STR_NBYTES + 1];

            memcpy(s, pPoint + m_Field_Offset[iField], PC_STR_NBYTES);

            s[PC_STR_NBYTES]	= '\0';

            Value	= s;
        }
        break;
        }

        return( true );
    }

    return( false );
}