/**
 * Creates JVM context given the JRE home dir. We assume that the parameter
 * points to existing directory. Note that in this case we don't know the
 * version of JRE. We could figure it out by reading the manifest from rt.jar
 * but that might take considerable amount of time. A typical size of rt.jar
 * is over 25MB. Instead, we assume that if the caller has given us a path
 * to its own JRE installation, then this is the preferred version of JRE.
 */
STATIC JVM * JVM_CreateDirContext(Str home)
{
    JVM * jvm = MEM_New(JVM);
    if (jvm) {
        memset(jvm, 0, sizeof(*jvm));
        jvm->versionString = STRING_Dup("UNKNOWN");
        jvm->javaHome = STRING_Dup(home);
        if (jvm->versionString && jvm->javaHome) {
            char s[MAX_PATH];

            /* Normalize the Java home path */
            Char* p;
            int len = StrLen(jvm->javaHome);
            for (p=StrChr(jvm->javaHome,'/'); p; p=strchr(p,'/')) *p = '\\';
            while (len > 0 && jvm->javaHome[len-1] == '\\') {
                jvm->javaHome[--len] = 0;
            }
            
            /* find jvm.dll */
            snprintf(s,COUNT(s),"%s\\%s",jvm->javaHome,JVM_DLL_1);
            s[COUNT(s)-1] = 0;

            if (FILE_IsFile(s)) {
                jvm->javaLib = STRING_Dup(s);
                if (jvm->javaLib) {
                    TRACE1("JNILIB: Java runtime lib: %s\n",s);
                    return jvm;
                }
            } else {
                TRACE1("JNILIB: no such file: %s\n",s);
                snprintf(s,COUNT(s),"%s\\%s",jvm->javaHome,JVM_DLL_2);
                s[COUNT(s)-1] = 0;
                if (FILE_IsFile(s)) {
                    jvm->javaLib = STRING_Dup(s);
                    if (jvm->javaLib) {
                        TRACE1("JNILIB: Java runtime lib: %s\n",s);
                        return jvm;
                    }
                } else {
                    TRACE1("JNILIB: no such file: %s\n",s);
                }
            }
        }
        JVM_Free(jvm);
    }
    return NULL;
}