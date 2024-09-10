int DDLT::Select::l__gc( lua_State* L )
{
  Select* self = Check( L, 1 );

  self->Destroy();
  return 0;
}