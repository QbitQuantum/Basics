/**
 * Return the next command line option. This has a number of special cases
 * which closely, but not exactly, follow the POSIX command line options
 * patterns:
 *
 * <pre>
 * -- means to stop processing additional options
 * -z means option z
 * -z ARGS means option z with (non-optional) arguments ARGS
 * -zARGS means option z with (optional) arguments ARGS
 * --zz means option zz
 * --zz ARGS means option zz with (non-optional) arguments ARGS
 * </pre>
 *
 * Note that you cannot combine single letter options; -abc != -a -b -c
 *
 * @return Returns the option string, or null if there are no more options.
 */
String Monkey::NextOption()
{
    if (mNextArg >= mArgs->GetLength()) {
        return String();
    }
    String arg = (*mArgs)[mNextArg];
    if (!arg.StartWith("-")) {
        return String();
    }
    mNextArg++;
    if (arg.Equals("--")) {
        return String();
    }
    if (arg.GetLength() > 1 && arg.GetChar(1) != '-') {
        if (arg.GetLength() > 2) {
            mCurArgData = arg.Substring(2);
            return arg.Substring(0, 2);
        }
        else {
            mCurArgData = String();
            return arg;
        }
    }
    mCurArgData = String();
    return arg;
}