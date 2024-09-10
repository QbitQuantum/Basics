/**
 * Load debug info, optionally related to a specific module.
 *
 * @returns VBox status.
 * @param   pVM             VM Handle.
 * @param   pszFilename     Path to the file containing the symbol information.
 *                          This can be the executable image, a flat symbol file of some kind or stripped debug info.
 * @param   AddressDelta    The value to add to the loaded symbols.
 * @param   pszName         Short hand name for the module. If not related to a module specify NULL.
 * @param   ModuleAddress   Address which the image is loaded at. This will be used to reference the module other places in the api.
 *                          Ignored when pszName is NULL.
 * @param   cbImage         Size of the image.
 *                          Ignored when pszName is NULL.
 */
VMMR3DECL(int) DBGFR3ModuleLoad(PVM pVM, const char *pszFilename, RTGCUINTPTR AddressDelta, const char *pszName, RTGCUINTPTR ModuleAddress, unsigned cbImage)
{
    /*
     * Lazy init.
     */
    if (!pVM->dbgf.s.fSymInited)
    {
        int rc = dbgfR3SymLazyInit(pVM);
        if (RT_FAILURE(rc))
            return rc;
    }

    /*
     * Open the load file.
     */
    FILE *pFile = NULL;
    char szFoundFile[RTPATH_MAX];
    int rc = dbgfR3ModuleLocateAndOpen(pVM, pszFilename, szFoundFile, sizeof(szFoundFile), &pFile);
    if (pFile)
    {
        /*
         * Probe the file type.
         */
        SYMFILETYPE enmType = dbgfR3ModuleProbe(pFile);
        if (enmType != SYMFILETYPE_UNKNOWN)
        {
            /*
             * Add the module.
             */
            if (pszName)
            {
                #ifdef HAVE_DBGHELP
                /** @todo arg! checkout the inserting of modules and then loading them again.... Or just the module representation.... */
                DWORD64 ImageBase = SymLoadModule64(pVM, NULL, (char *)(void *)szFoundFile, (char *)(void *)pszName, ModuleAddress, cbImage);
                if (!ImageBase)
                    ImageBase = SymLoadModule64(pVM, NULL, (char *)(void *)pszName, (char *)(void *)pszName, ModuleAddress, cbImage);
                if (ImageBase)
                {
                    AssertMsg(ModuleAddress == 0 || ModuleAddress == ImageBase, ("ModuleAddres=%RGv ImageBase=%llx\n", ModuleAddress, ImageBase));
                    ModuleAddress = ImageBase;
                }
                else
                    rc = win32Error(pVM);
                #else
                rc = VERR_NOT_IMPLEMENTED;
                #endif
            }
            if (RT_SUCCESS(rc))
            {
                /*
                 * Seek to the start of the file.
                 */
                rc = fseek(pFile, 0, SEEK_SET);
                Assert(!rc);

                /*
                 * Process the specific.
                 */
                switch (enmType)
                {
                    case SYMFILETYPE_LINUX_SYSTEM_MAP:
                        rc = dbgfR3LoadLinuxSystemMap(pVM, pFile, ModuleAddress, AddressDelta);
                        break;

                    case SYMFILETYPE_PDB:
                    case SYMFILETYPE_DBG:
                    case SYMFILETYPE_MZ:
                #ifdef HAVE_DBGHELP
                        /* done it all above! */
                        break;
                #endif
                    case SYMFILETYPE_LD_MAP:
                    case SYMFILETYPE_MS_MAP:
                    case SYMFILETYPE_OBJDUMP:
                    case SYMFILETYPE_ELF:
                        rc = VERR_NOT_SUPPORTED;
                        break;

                    default:
                        AssertFailed();
                        rc = VERR_INTERNAL_ERROR;
                        break;
                } /* file switch. */
            } /* module added successfully. */
        } /* format identified */
        else
            rc = VERR_NOT_SUPPORTED;
        /** @todo check for read errors */
        fclose(pFile);
    }
    return rc;
}