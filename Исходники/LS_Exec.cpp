DWORD __cdecl LandScape::exec( LS_OPCODE _opcode, ... )
{
   DWORD result;

   va_list  va;
   va_start( va, _opcode );

   result = execV( _opcode, va );

   va_end( va );

   return result;
};