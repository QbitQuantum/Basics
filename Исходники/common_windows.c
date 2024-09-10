// this is a helper function that takes the logic of determining window classes and puts it all in one place
// there are a number of places where we need to know what window class an arbitrary handle has
// theoretically we could use the class atom to avoid a _wcsicmp()
// however, raymond chen advises against this - http://blogs.msdn.com/b/oldnewthing/archive/2004/10/11/240744.aspx (and we're not in control of the Tab class, before you say anything)
// usage: windowClassOf(hwnd, L"class 1", L"class 2", ..., NULL)
int windowClassOf(HWND hwnd, ...)
{
// MSDN says 256 is the maximum length of a class name; add a few characters just to be safe (because it doesn't say whether this includes the terminating null character)
#define maxClassName 260
    WCHAR classname[maxClassName + 1];
    va_list ap;
    WCHAR *curname;
    int i;

    if (GetClassNameW(hwnd, classname, maxClassName) == 0)
        xpanic("error getting name of window class in windowClassOf()", GetLastError());
    va_start(ap, hwnd);
    i = 0;
    for (;;) {
        curname = va_arg(ap, WCHAR *);
        if (curname == NULL)
            break;
        if (_wcsicmp(classname, curname) == 0) {
            va_end(ap);
            return i;
        }
        i++;
    }
    // no match
    va_end(ap);
    return -1;
}