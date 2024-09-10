/* Initialize ProvReg strucutre from given directory */
_Use_decl_annotations_
MI_Result ProvReg_Init(ProvReg* self, const char* directory)
{
    RegFile* reg = NULL;
    Dir* dir = NULL;
    Dir* dir2 = NULL;
    MI_Result r = MI_RESULT_FAILED;
    
    /* Zero-fill self */
    memset(self, 0, sizeof(*self));

    dir = Dir_Open(directory);
    if (!dir)
    {
        return r;
    }

    /* Initialize batch allocator */
    Batch_Init(&self->batch, BATCH_MAX_PAGES);

    /* For each namespace directory in 'omirgister' */
    for (;;)
    {
        DirEnt* ent = Dir_Read(dir);

        if (!ent)
        {
            break;
        }

        /* Ignore system directories */
        if (strcmp(ent->name, ".") == 0 || strcmp(ent->name, "..") == 0)
            continue;

        /* Skip 'CVS' directories */
        if (strcmp(ent->name, "CVS") == 0)
            continue;

        /* Scan .reg files in the current namespace directory */
        {
            char path[PAL_MAX_PATH_SIZE];

            Strlcpy(path, directory, sizeof(path));
            Strlcat(path, "/", sizeof(path));
            Strlcat(path, ent->name, sizeof(path));

            /* Skip if not a dir */
            if(!Isdir(path))
                continue;

            dir2 = Dir_Open(path);
            if (!dir2)
            {
                goto failed;
            }

            for (;;)
            {
                DirEnt* ent2 = Dir_Read(dir2);
                if (!ent2)
                {
                    break;
                }

                /* Ignore system directories */
                if (strcmp(ent2->name,".") == 0 || strcmp(ent2->name,"..") == 0)
                {
                    continue;
                }

                /* Skip non-reg file */
                {
                    char* affix = Strrchr(ent2->name, '.');
                    if (!affix || (Strcasecmp(&affix[1], "reg") != 0))
                        continue;
                }

                /* Load the reg file */
                {
                    char regPath[PAL_MAX_PATH_SIZE];

                    /* Form path to .reg file */
                    Strlcpy(regPath, path, sizeof(regPath));
                    Strlcat(regPath, "/", sizeof(regPath));
                    Strlcat(regPath, ent2->name, sizeof(regPath));

                    /* Create new reg file object */
                    reg = RegFile_New(regPath);
                    if (!reg)
                    {
                        trace_ProvReg_SkipRegFile(scs(regPath));
                        continue;
                    }

                    /* For each class in the reg file */
                    {
                        RegClass* rc;
                        char* p = ent->name;
                        
                        /* Transpose NAMESPACE_SEPARATOR characters to '/' 
                         * characters 
                         */
                        while (*p)
                        {
                            if (*p == NAMESPACE_SEPARATOR)
                                *p = '/';
                            p++;
                        }

                        for (rc = reg->classesHead; rc; rc = rc->next)
                        {
                            if (_AddEntry(self, ent->name, reg, rc) != 0)
                            {
                                goto failed;
                            }
                        }
                    }

                    /* For each extraClass in the reg file */
                    {
                        RegClass* rc;
                        char* p = ent->name;
                        
                        /* Transpose NAMESPACE_SEPARATOR characters to '/' 
                         * characters 
                         */
                        while (*p)
                        {
                            if (*p == NAMESPACE_SEPARATOR)
                                *p = '/';
                            p++;
                        }

                        for (rc = reg->extraClassesHead; rc; rc = rc->next)
                        {
                            if (_AddEntryForExtraClass(self, ent->name, reg, rc) != 0)
                            {
                                goto failed;
                            }
                        }
                    }

                    /* Delete the current entry */
                    RegFile_Delete(reg);
                    reg = NULL;
                }
            }

            /* Close the directory */
            Dir_Close(dir2);
            dir2 = NULL;
        }
    }
    r = MI_RESULT_OK;

failed:
    if (dir2)
    {
        Dir_Close(dir2);
    }
    if (dir)
    {
        Dir_Close(dir);
    }
    if (r != MI_RESULT_OK)
    {
        ProvReg_Destroy(self);
        memset(self, 0, sizeof(*self));
    }
    if(reg)
    {
        RegFile_Delete(reg);
        reg = NULL;
    }
    return r;
}