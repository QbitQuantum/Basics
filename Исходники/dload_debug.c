/*lint -e528*/
static int dload_printf_to_file(const char *path, int tv_sec, int tv_usec, const char *buf)
{
    FILE    *pFile = NULL;
    int     file_length = 0;
    char    filea_name[DLOAD_LOGREC_PATH_LENGTH] = {0};
    char    fileb_name[DLOAD_LOGREC_PATH_LENGTH] = {0};
    int     ret = 0;
    int     status = 0;

    ret = access(path, F_OK);
    if(ret)
    {
        /* 目录不存在，则创建目录 */
        status = mkdir(path, S_IRWXU);
        if(-1 == status)
        {
            printf("[DLOAD LOGREC] mkdir %s error.\n", path, strerror(errno));
            return DLOAD_ERR;
        }
    }

    /*获取file A长度*/
    /*lint -e119*/
    snprintf(filea_name, DLOAD_LOGREC_PATH_LENGTH, "%s%s", path, DLOAD_LOGREC_FILENAME_A);
    /*lint +e119*/
    pFile = fopen(filea_name, "a+");
    if (NULL == pFile)
    {
        printf("[DLOAD LOGREC] fopen %s, %s\n", filea_name, strerror(errno));
        return DLOAD_ERR;
    }

    ret = fseek(pFile, 0, SEEK_END);
    if(0 != ret)
    {
        fclose(pFile);

        printf("[DLOAD LOGREC] fseek %s, %s\n", filea_name, strerror(errno));
        return DLOAD_ERR;       
    }
    
    file_length = ftell(pFile);
    if(0 > file_length)
    {
        fclose(pFile);

        printf("[DLOAD LOGREC] Get length %s, %s\n", filea_name, strerror(errno));
        return DLOAD_ERR;
    }

    /*如果超长: A->B, new A*/
    if (DLOAD_LOGREC_MAX_FILESIZE <= file_length)
    {
        fclose(pFile);
        /*lint -e119*/
        snprintf(fileb_name, DLOAD_LOGREC_PATH_LENGTH, "%s%s", path, DLOAD_LOGREC_FILENAME_B);
        /*lint +e119*/
        ret = rename(filea_name, fileb_name);
        if (0 != ret)
        {
            printf("[DLOAD LOGREC] Rename %s to %s, %s\n", filea_name, fileb_name, strerror(errno));
            return DLOAD_ERR;
        }

        pFile = NULL;
        pFile = fopen(filea_name, "a+");
        if (NULL == pFile)
        {
            printf("[DLOAD LOGREC] Open %s, %s\n", filea_name, strerror(errno));
            return DLOAD_ERR;
        }
    }

    ret = fprintf(pFile, "[%d.%d]", tv_sec, tv_usec);
    if (0 > ret)
    {
        fclose(pFile);
        printf("[DLOAD LOGREC] fprintf %s, %s\n", filea_name, strerror(errno));
        return DLOAD_ERR;
    }

    ret = fprintf(pFile, "%s", buf);
    if (0 > ret)
    {
        fclose(pFile);

        printf("[DLOAD LOGREC] fvprintf %s, %s\n", filea_name, strerror(errno));
        return DLOAD_ERR;
    }

    fclose(pFile);
    return DLOAD_OK;
}