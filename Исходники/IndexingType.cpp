void dumpIndexingType(PrintStream& out, IndexingType indexingType)
{
    const char* basicName;
    switch (indexingType & AllArrayTypes) {
    case NonArray:
        basicName = "NonArray";
        break;
    case NonArrayWithInt32:
        basicName = "NonArrayWithInt32";
        break;
    case NonArrayWithDouble:
        basicName = "NonArrayWithDouble";
        break;
    case NonArrayWithContiguous:
        basicName = "NonArrayWithContiguous";
        break;
    case NonArrayWithArrayStorage:
        basicName = "NonArrayWithArrayStorage";
        break;
    case NonArrayWithSlowPutArrayStorage:
        basicName = "NonArrayWithSlowPutArrayStorage";
        break;
    case ArrayClass:
        basicName = "ArrayClass";
        break;
    case ArrayWithUndecided:
        basicName = "ArrayWithUndecided";
        break;
    case ArrayWithInt32:
        basicName = "ArrayWithInt32";
        break;
    case ArrayWithDouble:
        basicName = "ArrayWithDouble";
        break;
    case ArrayWithContiguous:
        basicName = "ArrayWithContiguous";
        break;
    case ArrayWithArrayStorage:
        basicName = "ArrayWithArrayStorage";
        break;
    case ArrayWithSlowPutArrayStorage:
        basicName = "ArrayWithSlowPutArrayStorage";
        break;
    case CopyOnWriteArrayWithInt32:
        basicName = "CopyOnWriteArrayWithInt32";
        break;
    case CopyOnWriteArrayWithDouble:
        basicName = "CopyOnWriteArrayWithDouble";
        break;
    case CopyOnWriteArrayWithContiguous:
        basicName = "CopyOnWriteArrayWithContiguous";
        break;
    default:
        basicName = "Unknown!";
        break;
    }
    
    out.printf("%s%s", basicName, (indexingType & MayHaveIndexedAccessors) ? "|MayHaveIndexedAccessors" : "");
}