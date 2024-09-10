 errno_t
 __cdecl
 My_sopen_s(
     _Out_ int * _FileHandle,
     _In_z_ const char * _Filename,
     _In_ int _OpenFlag,
     _In_ int _ShareFlag,
     _In_ int _PermissionMode
 )
 {
     return _wsopen_s( _FileHandle, FromUTF8( _Filename ), _OpenFlag, _ShareFlag, _PermissionMode );
 }