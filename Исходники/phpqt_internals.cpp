// time critical
bool PHPQt::methodExists(const zend_class_entry* ce_ptr, const char* methodname)
{
    if(ce_ptr == NULL)
        pError() << "no class entry, could not check for message " << methodname;

    char* lcname = zend_str_tolower_dup(methodname, strlen(methodname));

    if(zend_hash_exists(const_cast<HashTable*>(&ce_ptr->function_table), lcname, strlen(methodname)+1)){
        return true;
    }

    efree(lcname);
    return false;
}