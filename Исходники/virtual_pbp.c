int vpbp_dread(SceUID fd, SceIoDirent * dir)
{
    int result, cur_idx, ret;
    struct IoDirentEntry *entry;

    lock();

    entry = dirent_search(fd);

    if(entry == NULL) {
        result = -44;
        goto exit;
    }

    result = sceIoDread(entry->iso_dfd, dir);

    if(sceKernelFindModuleByName("Game_Categories_Light") == NULL) {
        while(result > 0 && !is_iso(dir)) {
            result = sceIoDread(entry->iso_dfd, dir);
        }
    }

    if (result > 0 && is_iso(dir)) {
        VirtualPBP *vpbp;

        vpbp = vpbp_realloc(g_vpbps, g_vpbps_cnt+1);

        if(vpbp == NULL) {
            result = -42;
            goto exit;
        }

        g_vpbps = vpbp;
        g_vpbps_cnt++;
        cur_idx = g_vpbps_cnt-1;
        vpbp = &g_vpbps[cur_idx];
        STRCPY_S(vpbp->name, entry->path);
        vpbp->name[4] = '\0';
        STRCAT_S(vpbp->name, "/ISO");
        STRCAT_S(vpbp->name, entry->path + sizeof("xxx:/PSP/GAME") - 1);
        STRCAT_S(vpbp->name, "/");
        STRCAT_S(vpbp->name, dir->d_name);
        memcpy(&vpbp->ctime, &dir->d_stat.st_ctime, sizeof(vpbp->ctime));
        memcpy(&vpbp->mtime, &dir->d_stat.st_mtime, sizeof(vpbp->mtime));

        ret = get_cache(vpbp->name, &vpbp->mtime, vpbp);

        if (ret < 0) {
            ret = build_vpbp(vpbp);

            if (ret < 0) {
                result = -43;
                goto exit;
            }
        }

        result = add_fake_dirent(dir, cur_idx);
    }

exit:
    unlock();

    return result;
}