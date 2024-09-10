int ILGenImplementsAllInterfaces(ILGenInfo *info, ILNode *node,
                                 ILClass *classInfo,
                                 ILGenInterfaceErrorFunc error,
                                 ILGenInterfaceProxyFunc proxy)
{
    ILClass **visited;
    int visitedSize;
    int sawErrors;

    /* Allocate a temporary array to keep track of which interfaces
       we have already visited, in case the same interface is present
       along multiple inheritance paths */
    visited = (ILClass **)ILMalloc(sizeof(ILClass *) *
                                   GetSpanningSize(classInfo));
    if(!visited)
    {
        ILGenOutOfMemory(info);
    }
    visitedSize = 0;

    /* Recursively visit all interfaces */
    sawErrors = ImplementsAllInterfaces(node, classInfo, classInfo, error,
                                        proxy, visited, &visitedSize);

    /* Clean up and exit */
    ILFree(visited);
    return !sawErrors;
}