_CRTIMP type_info::~type_info()
{
        

        _mlock(_TYPEINFO_LOCK);
        if (_m_data != NULL) {
#ifdef _DEBUG /* CRT debug lib build */
            _free_base (_m_data);
#else
            free (_m_data);
#endif
        }
        _munlock(_TYPEINFO_LOCK);

}