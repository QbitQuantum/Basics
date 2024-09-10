PHP_COM_DOTNET_API void php_com_wrap_variant(zval *z, VARIANT *v,
        int codepage)
{
    php_com_dotnet_object *obj;

    obj = emalloc(sizeof(*obj));
    memset(obj, 0, sizeof(*obj));
    obj->code_page = codepage;
    obj->ce = php_com_variant_class_entry;
    obj->zo.ce = php_com_variant_class_entry;

    VariantInit(&obj->v);
    VariantCopyInd(&obj->v, v);
    obj->modified = 0;

    if ((V_VT(&obj->v) == VT_DISPATCH) && (V_DISPATCH(&obj->v) != NULL)) {
        IDispatch_GetTypeInfo(V_DISPATCH(&obj->v), 0, LANG_NEUTRAL, &obj->typeinfo);
    }

    zend_object_std_init(&obj->zo, php_com_variant_class_entry);
    obj->zo.handlers = &php_com_object_handlers;
    ZVAL_OBJ(z, &obj->zo);
}