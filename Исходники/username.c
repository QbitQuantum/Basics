/****************************************************************************
a wrapper for getpwnam() that tries with all lower and all upper case 
if the initial name fails. Also tried with first letter capitalised
****************************************************************************/
struct passwd *
Get_Pwnam (const char *a_user)
{
    fstring user;
    int last_char;
    int usernamelevel = lp_usernamelevel ();

    struct passwd *ret;

    if (!a_user || !(*a_user))
        return (NULL);

    StrnCpy (user, a_user, sizeof (user) - 1);

    ret = _Get_Pwnam (user);
    if (ret)
        return (ret);

    strlower (user);
    ret = _Get_Pwnam (user);
    if (ret)
        return (ret);

    strupper (user);
    ret = _Get_Pwnam (user);
    if (ret)
        return (ret);

    /* try with first letter capitalised */
    if (strlen (user) > 1)
        strlower (user + 1);
    ret = _Get_Pwnam (user);
    if (ret)
        return (ret);

    /* try with last letter capitalised */
    strlower (user);
    last_char = strlen (user) - 1;
    user[last_char] = toupper (user[last_char]);
    ret = _Get_Pwnam (user);
    if (ret)
        return (ret);

    /* try all combinations up to usernamelevel */
    strlower (user);
    ret = uname_string_combinations (user, _Get_Pwnam, usernamelevel);
    if (ret)
        return (ret);

    return (NULL);
}