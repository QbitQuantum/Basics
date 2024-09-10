void SE_Value::setRight(const SE_Value& right)
{
    type = right.type;
	mHasSetValue = right.mHasSetValue;
    switch(type)
    {
    case CHAR_T:
        data.c = right.data.c;
        break;
    case UCHAR_T:
        data.uc = right.data.uc;
        break;
    case SHORT_T:
        data.s = right.data.s;
        break;
    case USHORT_T:
        data.us = right.data.us;
        break;
    case INT_T:
        data.i = right.data.i;
        break;
    case UINT_T:
        data.ui = right.data.ui;
        break;
    case FLOAT_T:
        data.f = right.data.f;
        break;
    case ASCII_T:
        if(right.data.ascii)
        {
            size_t len = strlen(right.data.ascii);
            data.ascii = new char[len + 1];
            memset(data.ascii, 0, len + 1);
            strncpy(data.ascii, right.data.ascii, len);
        }
        break;
    case UTF8_T:
        if(right.data.utf8)
        {
            size_t len = strlen(right.data.utf8);
            data.utf8 = new char[len + 1];
            memset(data.utf8, 0, len + 1);
            strncpy(data.utf8, right.data.utf8, len);
        }
        break;
    case UNICODE_T:
        if(right.data.unicode)
        {
            size_t len = wcslen(right.data.unicode);
            data.unicode = new wchar_t[len + 1];
            memset(data.unicode, 0, sizeof(wchar_t) * (len + 1));
            wcscpy(data.unicode, right.data.unicode);
        }
        break;
    case VECTOR3F_T:
        data.vec3f = new SE_Vector3f;
        *data.vec3f = *right.data.vec3f;
        break;
    case VECTOR4F_T:
        data.vec4f = new SE_Vector4f;
        *data.vec4f = *right.data.vec4f;
        break;
    case VECTOR2F_T:
        data.vec2f = new SE_Vector2f;
        *data.vec2f = *right.data.vec2f;
        break;
    case VECTOR3I_T:
        data.vec3i = new SE_Vector3i;
        *data.vec3i = *right.data.vec3i;
        break;
    case QUAT_T:
        data.quat = new SE_Quat;
        *data.quat = *right.data.quat;
        break;
    case MATRIX3F_T:
        data.mat3f = new SE_Matrix3f;
        *data.mat3f = *right.data.mat3f;
        break;
    case MATRIX2F_T:
        data.mat2f = new SE_Matrix2f;
        *data.mat2f = *right.data.mat2f;
        break;
    case MATRIX4F_T:
        data.mat4f = new SE_Matrix4f;
        *data.mat4f = *right.data.mat4f;
        break;
    case USERDATA_T:
        if(right.data.virtualData->isAutoDeleted())
            data.virtualData = right.data.virtualData->clone();
        else
            data.virtualData = right.data.virtualData;
        break;
    }	
}