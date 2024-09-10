bool EffectShaderAnnotationDX9Imp::acquireResource()
{
    assert( effect_ );
    if( NULL == effect_ ) return false;

    switch( searchBy_ )
    {
    case ESEARCH_BY_INDEX:
        handle_ = effect_->GetAnnotation( getParentHandle(), index_ );
        break;
    case ESEARCH_BY_NAME:
        handle_ = effect_->GetParameterByName( getParentHandle(), convertString( name_ ).c_str() );
        break;
    }

    if( NULL == handle_ ) {
        wchar_t tmp[256];
        _snwprintf_s( tmp, 256, L"EffectShaderAnnotationDX9Imp::acquireResource\n" );
        OutputDebugStr( tmp );
        return false;
    }

    assert( effect_ );
    effect_->GetParameterDesc( getHandleDX9(), & desc_ );

    return true;
}