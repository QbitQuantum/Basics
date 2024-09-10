static int quat_exp(lua_State* L)
{
    Quatf* x = check_quat(L, 1);
    new_quat(L, result);
    *result = Exp(*x);
    return 1;
}