static STATUS _backup_dir_show(char *path)
{
    DIR* d;
    struct dirent* de;
    d = opendir(path);
    return_val_if_fail(d != NULL, RET_FAIL);

    int d_size = 0;
    int d_alloc = 10;
    return_val_if_fail(backup_menu != NULL, RET_FAIL);
    char** dirs = malloc(d_alloc * sizeof(char*));
    char** dirs_desc = malloc(d_alloc * sizeof(char*));
    return_val_if_fail(dirs != NULL, RET_FAIL);
    return_val_if_fail(dirs_desc != NULL, RET_FAIL);
    int z_size = 1;
    int z_alloc = 10;
    char** zips = malloc(z_alloc * sizeof(char*));
    char** zips_desc=malloc(z_alloc * sizeof(char*));
    return_val_if_fail(zips != NULL, RET_FAIL);
    return_val_if_fail(zips_desc != NULL, RET_FAIL);
    zips[0] = strdup("../");
    zips_desc[0]=strdup("../");

    while ((de = readdir(d)) != NULL) {
        int name_len = strlen(de->d_name);
        char de_path[PATH_MAX];
        snprintf(de_path, PATH_MAX, "%s/%s", path, de->d_name);
        struct stat st ;
        assert_if_fail(stat(de_path, &st) == 0);
        if (de->d_type == DT_DIR) {
            //skip "." and ".." entries
            if (name_len == 1 && de->d_name[0] == '.') continue;
            if (name_len == 2 && de->d_name[0] == '.' && 
                    de->d_name[1] == '.') continue;
            if (d_size >= d_alloc) {
                d_alloc *= 2;
                dirs = realloc(dirs, d_alloc * sizeof(char*));
                dirs_desc = realloc(dirs_desc, d_alloc * sizeof(char*));
            }
            dirs[d_size] = malloc(name_len + 2);
            dirs_desc[d_size] = malloc(64);
            strcpy(dirs[d_size], de->d_name);
            dirs[d_size][name_len ] = '\0';
            snprintf(dirs_desc[d_size], 64, "%s" ,ctime(&st.st_mtime));
            ++d_size;
        } else if (de->d_type == DT_REG && name_len >= 4 &&
                  strncasecmp(de->d_name + (name_len - 4), ".zip", 4) == 0) {
            if (z_size >= z_alloc) {
                z_alloc *= 2;
                zips = realloc(zips, z_alloc * sizeof(char*));
                zips_desc = realloc(zips_desc, z_alloc * sizeof(char*));
            }
            zips[z_size] = strdup(de->d_name);
            zips_desc[z_size] = malloc(64);
            snprintf(zips_desc[z_size], 64, "%s   %lldbytes" ,ctime(&st.st_mtime), st.st_size);
            z_size++;
        }
    }
    closedir(d);


    // append dirs to the zips list
    if (d_size + z_size + 1 > z_alloc) {
        z_alloc = d_size + z_size + 1;
        zips = realloc(zips, z_alloc * sizeof(char*));
        zips_desc = realloc(zips_desc, z_alloc * sizeof(char*));
    }
    memcpy(zips + z_size, dirs, d_size * sizeof(char *));
    memcpy(zips_desc + z_size, dirs_desc, d_size * sizeof(char*));
    free(dirs);
    z_size += d_size;
    zips[z_size] = NULL;
    zips_desc[z_size] = NULL;

   int result;
   int chosen_item = 0;
   do {
       chosen_item = miui_sdmenu(backup_menu->name, zips, zips_desc, z_size);
       return_val_if_fail(chosen_item >= 0, RET_FAIL);
       char * item = zips[chosen_item];
       int item_len = strlen(item);
       if ( chosen_item == 0) {
           //go up but continue browsing
           result = -1;
           break;
       } else {
           // select a zipfile
           // the status to the caller
           char new_path[PATH_MAX];
           strlcpy(new_path, path, PATH_MAX);
           strlcat(new_path, "/", PATH_MAX);
           strlcat(new_path, item, PATH_MAX);
           /*
            *nandroid_restore(backup_path, restore_boot, system, data, chache , sdext, wimax)
            */
           if (p_current != NULL && RET_YES == miui_confirm(3, p_current->name, p_current->desc, p_current->icon)) {
               backup_restore(new_path);
           }
           break;
       }
   } while(1);

   int i;
   for (i = 0; i < z_size; ++i) 
   {
       free(zips[i]);
       free(zips_desc[i]);
   }
   free(zips);
   return result;
}