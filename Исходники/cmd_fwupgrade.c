static int do_fwupgrade(struct cmd_ctx *cmdctx, int argc, char * const argv[])
{
    struct mtd_info *mtd = NULL;
    const char *filename = NULL;
    int ret;
    int oob = 0;
    switch(argc) {
    case 4:
        oob = (argv[3][0] == 'y');;
        if (oob) printf("FWU: Will write oob data!\n");
    /* pass through */
    case 3:
        filename = argv[2];
    /* pass through */
    case 2:
        mtd = mtd_by_name(argv[1]);
        break;
    default:
        return cmd_usage(cmdctx->cmdtp);
    }

    if(mtd == NULL) {
        printf("FWU mtd device is not available (bad part name?)\n");
        return -1;
    }

    if(mtd->erasesize > CONFIG_CMD_FWUPGRADE_BUFFER_SIZE) {
        printf("FWU internal buffer is smaller than size of eraseblock\n");
        return -ENOMEM;
    };
    u8 *block = (u8*)CONFIG_CMD_FWUPGRADE_BUFFER_ADDR;
    if(block == NULL) {
        printf("FWU unable to allocate memory\n");
        return -ENOMEM;
    }

    struct fwu_tftp_ctx ctx;
    memset(&ctx, 0, sizeof(struct fwu_tftp_ctx));
    ctx.mtd = mtd;
    ctx.block = block;
    ctx.flash_offset = 0;
    ctx.flash_end = mtd->size;
    ctx.oob = oob;

    struct NetTask task;
    net_init_task_def(&task, TFTP);
    task.u.tftp.data_cb = fwu_tftp_cb;
    task.u.tftp.data_ctx = &ctx;

    char dir[MAXPATH];
    extract_dirname(dir, task.bootfile);
    if(filename) {
        if(filename[0] == '/') {
            strncpy_s(task.bootfile, filename, MAXPATH);
        }
        else {
            sprintf(task.bootfile, "%s%s", dir, filename);
        }
    } else {
        if(0 == strcmp(mtd->name, "boot")) {
            sprintf(task.bootfile, "%smboot.img", dir);
        } else if(0 == strcmp(mtd->name, "kernel")) {
            sprintf(task.bootfile, "%suImage", dir);
        } else {
            sprintf(task.bootfile, "%smboot-%s.bin", dir, mtd->name);
        }
    }

    ret = erase_part(mtd, 0, 1);
    if (ret)
    {
        printf("FW: Partition erase failed, aborting...");
        goto out;
    }

    ret = NetLoop(&task);
    if (ret < 0) {
        printf("FWU net trasfer failed: ret %d\n", ret);
        goto out;
    }

    printf("FWU complete: tftp_bytes %lu hex 0x%08lX flash_area 0x%012llX flash_bb %d\n",
           task.out_filesize, task.out_filesize, ctx.flash_offset, ctx.bb);

out:
    return 0;
}