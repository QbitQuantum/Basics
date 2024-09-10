static int mh_deleteitem (lua_State* l) {
menu* m = lua_touserdata(l,1);
if (lua_isnoneornil(l,2)) {
const char* menuName = GetMenuName(m->parent, m->position);
if (menuName) free(menuName);
DeleteMenu(m->parent, m->command, MF_BYCOMMAND);
if (!m->sub) {
removeCustomCommand(m->command);
removeAccelerator(m->command);
} 
DrawMenuBar(win);
return 0;
}
else {
if (!m->sub) return 0;
menu* x = lua_touserdata(l,2);
const char* menuName = GetMenuName(m->menu, x->position);
if (menuName) free(menuName);
DeleteMenu(m->menu, x->command, MF_BYCOMMAND);
DrawMenuBar(win);
if (!x->sub) {
removeCustomCommand(x->command);
removeAccelerator(x->command);
}
lua_settop(l,1);
return 1;
}}