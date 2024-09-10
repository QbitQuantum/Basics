/**
 * See JNI method __1close.
 * This is an internal wrapper method for handling Leaves.
 */
jint CloseL(JNIEnv *aEnv, jclass aClass, jint aHandle, jobject aOutputFilename)
{
    // Convert handle to pointer.
    CImportFile *file = reinterpret_cast<CImportFile*>(aHandle<<2);

    // Complete writing and get output filename from the agent.
    TInt err = file->WriteDataComplete();
    // Initialize output filename to aOutputFilename parameter.
    if (KErrNone == err)
    {
        // Get class handle to StringBuffer
        aClass = aEnv->GetObjectClass(aOutputFilename);
        // Get method ID to StringBuffer StringBuffer.append(String)
        jmethodID methodID = aEnv->GetMethodID(
                                 aClass, "append", "(Ljava/lang/String;)Ljava/lang/StringBuffer;");
        if (0 == methodID)
        {
            ELOG(EJavaInstaller,
                 "FileWriter__1close: StringBuffer.append not found");
            err = KErrGeneral;
        }
        else
        {
            CSupplierOutputFile &output = file->OutputFileL(0);
            TPtrC outputFilename = output.FileName();
            // Create new Java String.
            jstring jOutputFilename =
                aEnv->NewString(outputFilename.Ptr(), outputFilename.Length());
            aEnv->CallObjectMethod(aOutputFilename, methodID, jOutputFilename);
        }
    }

    // Delete the CImportFile instance which is no longer used.
    delete file;
    return err;
}