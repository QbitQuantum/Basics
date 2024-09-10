static int imx_bbu_nand_update(struct bbu_handler *handler, struct bbu_data *data)
{
	struct imx_nand_fcb_bbu_handler *imx_handler =
		container_of(handler, struct imx_nand_fcb_bbu_handler, handler);
	struct cdev *bcb_cdev;
	struct mtd_info *mtd;
	int ret, i;
	struct fcb_block *fcb = NULL;
	void *fw = NULL, *fw_orig = NULL;
	unsigned fw_size, partition_size;
	enum filetype filetype;
	unsigned num_blocks_fw;
	int pages_per_block;
	int used = 0;
	int fw_orig_len;
	int used_refresh = 0, unused_refresh = 0;

	if (data->image) {
		filetype = file_detect_type(data->image, data->len);

		if (filetype != imx_handler->filetype &&
			!bbu_force(data, "Image is not of type %s but of type %s",
				file_type_to_string(imx_handler->filetype),
				file_type_to_string(filetype)))
			return -EINVAL;
	}

	bcb_cdev = cdev_by_name(handler->devicefile);
	if (!bcb_cdev) {
		pr_err("%s: No FCB device!\n", __func__);
		return -ENODEV;
	}

	mtd = bcb_cdev->mtd;
	partition_size = mtd->size;
	pages_per_block = mtd->erasesize / mtd->writesize;

	for (i = 0; i < 4; i++) {
		read_fcb(mtd, i, &fcb);
		if (fcb)
			break;
	}

	/*
	 * This code uses the following layout in the Nand flash:
	 *
	 * fwmaxsize = (n_blocks - 4) / 2
	 *
	 * block
	 *
	 * 0              ----------------------
	 *                | FCB/DBBT 0         |
	 * 1              ----------------------
	 *                | FCB/DBBT 1         |
	 * 2              ----------------------
	 *                | FCB/DBBT 2         |
	 * 3              ----------------------
	 *                | FCB/DBBT 3         |
	 * 4              ----------------------
	 *                | Firmware slot 0    |
	 * 4 + fwmaxsize  ----------------------
	 *                | Firmware slot 1    |
	 *                ----------------------
	 *
	 * We want a robust update in which a power failure may occur
	 * everytime without bricking the board, so here's the strategy:
	 *
	 * The FCBs contain pointers to the firmware slots in the
	 * Firmware1_startingPage and Firmware2_startingPage fields. Note that
	 * Firmware1_startingPage doesn't necessarily point to slot 0. We
	 * exchange the pointers during update to atomically switch between the
	 * old and the new firmware.
	 *
	 * - We read the first valid FCB and the firmware slots.
	 * - We check which firmware slot is currently used by the ROM:
	 *    - if no FCB is found or its layout differs from the above layout,
	 *      continue without robust update
	 *   - if only one firmware slot is readable, the ROM uses it
	 *   - if both slots are readable, the ROM will use slot 0
	 * - Step 1: erase/update the slot currently unused by the ROM
	 * - Step 2: Update FCBs/DBBTs, thereby letting Firmware1_startingPage
	 *           point to the slot we just updated. From this moment
	 *           on the new firmware will be used and running a
	 *           refresh/repair after a power failure after this
	 *           step will complete the update.
	 * - Step 3: erase/update the other firmwre slot
	 * - Step 4: Eventually write FCBs/DBBTs again. This may become
	 *           necessary when step 3 revealed new bad blocks.
	 *
	 * This robust update only works when the original FCBs on the device
	 * uses the same layout as this code does. In other cases update will
	 * also work, but it won't be robust against power failures.
	 *
	 * Refreshing the firmware which is needed when blocks become unreadable
	 * due to read disturbance works the same way, only that the new firmware
	 * is the same as the old firmware and that it will only be written when
	 * reading from the device returns -EUCLEAN indicating that a block needs
	 * to be rewritten.
	 */
	if (fcb)
		read_firmware_all(mtd, fcb, &fw_orig, &fw_orig_len,
				  &used_refresh, &unused_refresh, &used);

	if (data->image) {
		/*
		 * We have to write one additional page to make the ROM happy.
		 * Maybe the PagesInFirmwarex fields are really the number of pages - 1.
		 * kobs-ng has the same.
		 */
		fw_size = ALIGN(data->len + mtd->writesize, mtd->writesize);
		fw = xzalloc(fw_size);
		memcpy(fw, data->image, data->len);
		free(fw_orig);
		used_refresh = 1;
		unused_refresh = 1;

		free(fcb);
		fcb = xzalloc(sizeof(*fcb));
		fcb->Firmware1_startingPage = imx_bbu_firmware_start_block(mtd, !used) * pages_per_block;
		fcb->Firmware2_startingPage = imx_bbu_firmware_start_block(mtd, used) * pages_per_block;
		fcb->PagesInFirmware1 = fw_size / mtd->writesize;
		fcb->PagesInFirmware2 = fcb->PagesInFirmware1;

		fcb_create(imx_handler, fcb, mtd);
	} else {
		if (!fcb) {
			pr_err("No FCB found on device, cannot refresh\n");
			ret = -EINVAL;
			goto out;
		}

		if (!fw_orig) {
			pr_err("No firmware found on device, cannot refresh\n");
			ret = -EINVAL;
			goto out;
		}

		fw = fw_orig;
		fw_size = fw_orig_len;
		pr_info("Refreshing existing firmware\n");
	}

	num_blocks_fw = imx_bbu_firmware_max_blocks(mtd);

	if (num_blocks_fw * mtd->erasesize < fw_size) {
		pr_err("Not enough space for update\n");
		return -ENOSPC;
	}

	ret = bbu_confirm(data);
	if (ret)
		goto out;

	/* Step 1: write firmware which is currently unused by the ROM */
	if (unused_refresh) {
		pr_info("%sing slot %d\n", data->image ? "updat" : "refresh", !used);
		ret = imx_bbu_write_firmware(mtd, !used, fw, fw_size);
		if (ret < 0)
			goto out;
	} else {
		pr_info("firmware slot %d still ok, nothing to do\n", !used);
	}

	/*
	 * Step 2: Write FCBs/DBBTs. This will use the firmware we have
	 * just written as primary firmware. From now on the new
	 * firmware will be booted.
	 */
	ret = imx_bbu_write_fcbs_dbbts(mtd, fcb);
	if (ret < 0)
		goto out;

	/* Step 3: Write the secondary firmware */
	if (used_refresh) {
		pr_info("%sing slot %d\n", data->image ? "updat" : "refresh", used);
		ret = imx_bbu_write_firmware(mtd, used, fw, fw_size);
		if (ret < 0)
			goto out;
	} else {
		pr_info("firmware slot %d still ok, nothing to do\n", used);
	}

	/*
	 * Step 4: If writing the secondary firmware discovered new bad
	 * blocks, write the FCBs/DBBTs again with updated bad block
	 * information.
	 */
	if (ret > 0) {
		pr_info("New bad blocks detected, writing FCBs/DBBTs again\n");
		ret = imx_bbu_write_fcbs_dbbts(mtd, fcb);
		if (ret < 0)
			goto out;
	}

out:
	free(fw);
	free(fcb);

	return ret;
}