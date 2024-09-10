/*****************************************************************************
*Name         :
*Description  :receive testcase num from echo command
*Parameter    :
*Return       :
*Note         :
*****************************************************************************/
static ssize_t nand_test_store(struct kobject *kobject,struct attribute *attr, const char *buf, size_t count)
{
    int             ret;
    int             argnum = 0;
    char            cmd[32] = {0};
    unsigned int    param0 = 0;
    unsigned int    param1 = 0;
    unsigned int    param2 = 0;

    struct nand_kobject* nand_kobj;
    nand_kobj = (struct nand_kobject*)kobject;

    argnum = sscanf(buf, "%s %u %u %u ", cmd, &param0, &param1, &param2);
    printk("argnum=%i, cmd=%s, param0=%u, param1=%u, param2=%u\n", argnum, cmd, param0, param1, param2);

    if (-1 == argnum)
    {
        printk("cmd format err!");
        goto NAND_TEST_STORE_EXIT;
    }

    if(strcmp(cmd,"help") == 0)
    {
        printk("nand debug cmd:\n");
        printk("  help \n");
    }
    else if(strcmp(cmd,"flush") == 0)
    {
        printk("nand debug cmd:\n");
        printk("  flush \n");
        mutex_lock(nand_kobj->nftl_blk->blk_lock);
        ret = nand_kobj->nftl_blk->flush_write_cache(nand_kobj->nftl_blk,param0);
        mutex_unlock(nand_kobj->nftl_blk->blk_lock);
        goto NAND_TEST_STORE_EXIT;
    }
    else if(strcmp(cmd,"gcall") == 0)
    {
        printk("nand debug cmd:\n");
        printk("  gcall \n");
        mutex_lock(nand_kobj->nftl_blk->blk_lock);
        ret = gc_all(nand_kobj->nftl_blk->nftl_zone);
        mutex_unlock(nand_kobj->nftl_blk->blk_lock);
        goto NAND_TEST_STORE_EXIT;
    }
    else if(strcmp(cmd,"gcone") == 0)
    {
        printk("nand debug cmd:\n");
        printk("  gcone \n");
        mutex_lock(nand_kobj->nftl_blk->blk_lock);
        ret = gc_one(nand_kobj->nftl_blk->nftl_zone);
        mutex_unlock(nand_kobj->nftl_blk->blk_lock);
        goto NAND_TEST_STORE_EXIT;
    }
    else if(strcmp(cmd,"test") == 0)
    {
        printk("nand debug cmd:\n");
        printk("  test \n");
        mutex_lock(nand_kobj->nftl_blk->blk_lock);
        ret = nftl_set_zone_test((void*)nand_kobj->nftl_blk->nftl_zone,param0);
        mutex_unlock(nand_kobj->nftl_blk->blk_lock);
        goto NAND_TEST_STORE_EXIT;
    }
    else if(strcmp(cmd,"showall") == 0)
    {
        printk("nand debug cmd:\n");
        printk("  show all \n");
        print_free_list(nand_kobj->nftl_blk->nftl_zone);
        print_block_invalid_list(nand_kobj->nftl_blk->nftl_zone);
        print_nftl_zone(nand_kobj->nftl_blk->nftl_zone);
        goto NAND_TEST_STORE_EXIT;
    }
    else
    {
        printk("err, nand debug undefined cmd: %s\n", cmd);
    }

NAND_TEST_STORE_EXIT:
    return count;
}