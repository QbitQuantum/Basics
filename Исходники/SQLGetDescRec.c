SQLRETURN SQLGetDescRecA( SQLHDESC descriptor_handle,
           SQLSMALLINT rec_number, 
           SQLCHAR *name,
           SQLSMALLINT buffer_length, 
           SQLSMALLINT *string_length,
           SQLSMALLINT *type, 
           SQLSMALLINT *sub_type, 
           SQLLEN *length, 
           SQLSMALLINT *precision, 
           SQLSMALLINT *scale, 
           SQLSMALLINT *nullable )
{
    return SQLGetDescRec( descriptor_handle,
                        rec_number, 
                        name,
                        buffer_length, 
                        string_length,
                        type, 
                        sub_type, 
                        length, 
                        precision, 
                        scale, 
                        nullable );
}