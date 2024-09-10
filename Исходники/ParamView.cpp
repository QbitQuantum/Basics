    void ParamView::handleSliderChange( float v )
    {
        // update the parameter and the label
        const ParamInfo* _pinfo = _pset.paramInfo( _paramIdx );

        String label;
        switch( _pinfo->type ){
            case PTYPE_UINT8:
                _pset.setArg( _paramHandle, ( uint8_t )v );
                label.sprintf( "%u", ( uint8_t )v );
                break;
            case PTYPE_UINT16:
                _pset.setArg( _paramHandle, ( uint16_t )v );
                label.sprintf( "%u", ( uint16_t )v );
                break;
            case PTYPE_UINT32:
                _pset.setArg( _paramHandle, ( uint32_t )v );
                label.sprintf( "%u", ( uint32_t )v );
                break;
            case PTYPE_UINT64:
                _pset.setArg( _paramHandle, ( uint64_t )v );
                label.sprintf( "%u", ( uint64_t )v );
                break;
            case PTYPE_INT8:
                _pset.setArg( _paramHandle, ( int8_t )v );
                label.sprintf( "%d", ( int8_t )v );
                break;
            case PTYPE_INT16:
                _pset.setArg( _paramHandle, ( int16_t )v );
                label.sprintf( "%d", ( int16_t )v );
                break;
            case PTYPE_INT32:
                _pset.setArg( _paramHandle, ( int32_t )v );
                label.sprintf( "%d", ( int32_t )v );
                break;
            case PTYPE_INT64:
                _pset.setArg( _paramHandle, ( int64_t )v );
                label.sprintf( "%d", ( int64_t )v );
                break;
            case PTYPE_FLOAT:
                _pset.setArg( _paramHandle, v );
                label.sprintf( "%0.1g", v );
                break;
            case PTYPE_DOUBLE:
                _pset.setArg( _paramHandle, ( double )v );
                label.sprintf( "%0.1g", v );
                break;
            default:
                break;
        }
        _valueLabel.setLabel( label );
    }