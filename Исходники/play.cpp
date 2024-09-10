int main(int argc, const char*argv[])
{
    if (argc < 1) { return -1; }

    unsigned int ports = midi.getPortCount();
    if (ports < 1) { return -1; }
    midi.openPort(0);

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    
    lua_pushcfunction(L, midi_send);
    lua_setglobal(L, "midi_send");
    
    int ret = luaL_dofile(L, argv[1]);
    if(ret != 0){
        printf("Error occurs when calling luaL_dofile() Hint Machine 0x%x\n",ret);
        printf("Error: %s", lua_tostring(L,-1));
    }
    lua_close(L);
    return 0;
}