void setRtlFormat(IPropertyTree & properties, IOutputMetaData * meta)
{
    if (meta && meta->queryTypeInfo())
    {
        MemoryBuffer out;
        if (dumpTypeInfo(out, meta->querySerializedDiskMeta()->queryTypeInfo()))
            properties.setPropBin("_rtlType", out.length(), out.toByteArray());
    }
}