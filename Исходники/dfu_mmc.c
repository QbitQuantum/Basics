static int mmc_block_op(enum dfu_op op, struct dfu_entity *dfu,
			u64 offset, void *buf, long *len)
{
	struct mmc *mmc = find_mmc_device(dfu->dev_num);
	u32 blk_start, blk_count, n = 0;
	int ret, part_num_bkp = 0;

	/*
	 * We must ensure that we work in lba_blk_size chunks, so ALIGN
	 * this value.
	 */
	*len = ALIGN(*len, dfu->data.mmc.lba_blk_size);

	blk_start = dfu->data.mmc.lba_start +
			(u32)lldiv(offset, dfu->data.mmc.lba_blk_size);
	blk_count = *len / dfu->data.mmc.lba_blk_size;
	if (blk_start + blk_count >
			dfu->data.mmc.lba_start + dfu->data.mmc.lba_size) {
		puts("Request would exceed designated area!\n");
		return -EINVAL;
	}

	if (dfu->data.mmc.hw_partition >= 0) {
		part_num_bkp = mmc->part_num;
		ret = mmc_access_part(dfu, mmc, dfu->data.mmc.hw_partition);
		if (ret)
			return ret;
	}

	debug("%s: %s dev: %d start: %d cnt: %d buf: 0x%p\n", __func__,
	      op == DFU_OP_READ ? "MMC READ" : "MMC WRITE", dfu->dev_num,
	      blk_start, blk_count, buf);
	switch (op) {
	case DFU_OP_READ:
		n = mmc->block_dev.block_read(dfu->dev_num, blk_start,
					      blk_count, buf);
		break;
	case DFU_OP_WRITE:
		n = mmc->block_dev.block_write(dfu->dev_num, blk_start,
					       blk_count, buf);
		break;
	default:
		error("Operation not supported\n");
	}

	if (n != blk_count) {
		error("MMC operation failed");
		if (dfu->data.mmc.hw_partition >= 0)
			mmc_access_part(dfu, mmc, part_num_bkp);
		return -EIO;
	}

	if (dfu->data.mmc.hw_partition >= 0) {
		ret = mmc_access_part(dfu, mmc, part_num_bkp);
		if (ret)
			return ret;
	}

	return 0;
}