void dumpNodeFlags(PrintStream& actualOut, NodeFlags flags)
{
    StringPrintStream out;
    CommaPrinter comma("|");
    
    if (flags & NodeResultMask) {
        switch (flags & NodeResultMask) {
        case NodeResultJS:
            out.print(comma, "JS");
            break;
        case NodeResultNumber:
            out.print(comma, "Number");
            break;
        case NodeResultDouble:
            out.print(comma, "Double");
            break;
        case NodeResultInt32:
            out.print(comma, "Int32");
            break;
        case NodeResultInt52:
            out.print(comma, "Int52");
            break;
        case NodeResultBoolean:
            out.print(comma, "Boolean");
            break;
        case NodeResultStorage:
            out.print(comma, "Storage");
            break;
        default:
            RELEASE_ASSERT_NOT_REACHED();
            break;
        }
    }
    
    if (flags & NodeMustGenerate)
        out.print(comma, "MustGen");
    
    if (flags & NodeHasVarArgs)
        out.print(comma, "VarArgs");
    
    if (flags & NodeClobbersWorld)
        out.print(comma, "Clobbers");
    
    if (flags & NodeMightClobber)
        out.print(comma, "MightClobber");
    
    if (flags & NodeResultMask) {
        if (!(flags & NodeBytecodeUsesAsNumber) && !(flags & NodeBytecodeNeedsNegZero))
            out.print(comma, "PureInt");
        else if (!(flags & NodeBytecodeUsesAsNumber))
            out.print(comma, "PureInt(w/ neg zero)");
        else if (!(flags & NodeBytecodeNeedsNegZero))
            out.print(comma, "PureNum");
        if (flags & NodeBytecodeUsesAsOther)
            out.print(comma, "UseAsOther");
    }
    
    if (flags & NodeMayOverflow)
        out.print(comma, "MayOverflow");
    
    if (flags & NodeMayNegZero)
        out.print(comma, "MayNegZero");
    
    if (flags & NodeBytecodeUsesAsInt)
        out.print(comma, "UseAsInt");
    
    if (!(flags & NodeDoesNotExit))
        out.print(comma, "CanExit");
    
    if (flags & NodeIsFlushed)
        out.print(comma, "IsFlushed");
    
    CString string = out.toCString();
    if (!string.length())
        actualOut.print("<empty>");
    else
        actualOut.print(string);
}