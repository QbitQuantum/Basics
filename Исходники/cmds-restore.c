static int copy_one_extent(struct btrfs_root *root, int fd,
			   struct extent_buffer *leaf,
			   struct btrfs_file_extent_item *fi, u64 pos)
{
	struct btrfs_multi_bio *multi = NULL;
	struct btrfs_device *device;
	char *inbuf, *outbuf = NULL;
	ssize_t done, total = 0;
	u64 bytenr;
	u64 ram_size;
	u64 disk_size;
	u64 num_bytes;
	u64 length;
	u64 size_left;
	u64 dev_bytenr;
	u64 offset;
	u64 count = 0;
	int compress;
	int ret;
	int dev_fd;
	int mirror_num = 1;
	int num_copies;

	compress = btrfs_file_extent_compression(leaf, fi);
	bytenr = btrfs_file_extent_disk_bytenr(leaf, fi);
	disk_size = btrfs_file_extent_disk_num_bytes(leaf, fi);
	ram_size = btrfs_file_extent_ram_bytes(leaf, fi);
	offset = btrfs_file_extent_offset(leaf, fi);
	num_bytes = btrfs_file_extent_num_bytes(leaf, fi);
	size_left = disk_size;
	if (compress == BTRFS_COMPRESS_NONE)
		bytenr += offset;

	if (verbose && offset)
		printf("offset is %Lu\n", offset);
	/* we found a hole */
	if (disk_size == 0)
		return 0;

	inbuf = malloc(size_left);
	if (!inbuf) {
		error("not enough memory");
		return -ENOMEM;
	}

	if (compress != BTRFS_COMPRESS_NONE) {
		outbuf = calloc(1, ram_size);
		if (!outbuf) {
			error("not enough memory");
			free(inbuf);
			return -ENOMEM;
		}
	}
again:
	length = size_left;
	ret = btrfs_map_block(root->fs_info, READ, bytenr, &length, &multi,
			      mirror_num, NULL);
	if (ret) {
		error("cannot map block logical %llu length %llu: %d",
				(unsigned long long)bytenr,
				(unsigned long long)length, ret);
		goto out;
	}
	device = multi->stripes[0].dev;
	dev_fd = device->fd;
	device->total_ios++;
	dev_bytenr = multi->stripes[0].physical;
	free(multi);

	if (size_left < length)
		length = size_left;

	done = pread(dev_fd, inbuf+count, length, dev_bytenr);
	/* Need both checks, or we miss negative values due to u64 conversion */
	if (done < 0 || done < length) {
		num_copies = btrfs_num_copies(root->fs_info, bytenr, length);
		mirror_num++;
		/* mirror_num is 1-indexed, so num_copies is a valid mirror. */
		if (mirror_num > num_copies) {
			ret = -1;
			error("exhausted mirrors trying to read (%d > %d)",
					mirror_num, num_copies);
			goto out;
		}
		fprintf(stderr, "Trying another mirror\n");
		goto again;
	}

	mirror_num = 1;
	size_left -= length;
	count += length;
	bytenr += length;
	if (size_left)
		goto again;

	if (compress == BTRFS_COMPRESS_NONE) {
		while (total < num_bytes) {
			done = pwrite(fd, inbuf+total, num_bytes-total,
				      pos+total);
			if (done < 0) {
				ret = -1;
				error("cannot write data: %d %m", errno);
				goto out;
			}
			total += done;
		}
		ret = 0;
		goto out;
	}

	ret = decompress(root, inbuf, outbuf, disk_size, &ram_size, compress);
	if (ret) {
		num_copies = btrfs_num_copies(root->fs_info, bytenr, length);
		mirror_num++;
		if (mirror_num >= num_copies) {
			ret = -1;
			goto out;
		}
		fprintf(stderr, "Trying another mirror\n");
		goto again;
	}

	while (total < num_bytes) {
		done = pwrite(fd, outbuf + offset + total,
			      num_bytes - total,
			      pos + total);
		if (done < 0) {
			ret = -1;
			goto out;
		}
		total += done;
	}
out:
	free(inbuf);
	free(outbuf);
	return ret;
}