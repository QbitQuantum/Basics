static void parse_extended_opts(struct ext2_super_block *param, 
				const char *opts)
{
	char	*buf, *token, *next, *p, *arg, *badopt = "";
	int	len;
	int	r_usage = 0;

	len = strlen(opts);
	buf = malloc(len+1);
	if (!buf) {
		fprintf(stderr,
			_("Couldn't allocate memory to parse options!\n"));
		exit(1);
	}
	strcpy(buf, opts);
	for (token = buf; token && *token; token = next) {
		p = strchr(token, ',');
		next = 0;
		if (p) {
			*p = 0;
			next = p+1;
		}
		arg = strchr(token, '=');
		if (arg) {
			*arg = 0;
			arg++;
		}
		if (strcmp(token, "stride") == 0) {
			if (!arg) {
				r_usage++;
				badopt = token;
				continue;
			}
			param->s_raid_stride = strtoul(arg, &p, 0);
			if (*p || (param->s_raid_stride == 0)) {
				fprintf(stderr,
					_("Invalid stride parameter: %s\n"),
					arg);
				r_usage++;
				continue;
			}
		} else if (strcmp(token, "stripe-width") == 0 ||
			   strcmp(token, "stripe_width") == 0) {
			if (!arg) {
				r_usage++;
				badopt = token;
				continue;
			}
			param->s_raid_stripe_width = strtoul(arg, &p, 0);
			if (*p || (param->s_raid_stripe_width == 0)) {
				fprintf(stderr,
					_("Invalid stripe-width parameter: %s\n"),
					arg);
				r_usage++;
				continue;
			}
		} else if (!strcmp(token, "resize")) {
			unsigned long resize, bpg, rsv_groups;
			unsigned long group_desc_count, desc_blocks;
			unsigned int gdpb, blocksize;
			int rsv_gdb;

			if (!arg) {
				r_usage++;
				badopt = token;
				continue;
			}

			resize = parse_num_blocks(arg, 
						  param->s_log_block_size);

			if (resize == 0) {
				fprintf(stderr, 
					_("Invalid resize parameter: %s\n"),
					arg);
				r_usage++;
				continue;
			}
			if (resize <= param->s_blocks_count) {
				fprintf(stderr, 
					_("The resize maximum must be greater "
					  "than the filesystem size.\n"));
				r_usage++;
				continue;
			}

			blocksize = EXT2_BLOCK_SIZE(param);
			bpg = param->s_blocks_per_group;
			if (!bpg)
				bpg = blocksize * 8;
			gdpb = blocksize / sizeof(struct ext2_group_desc);
			group_desc_count = 
				ext2fs_div_ceil(param->s_blocks_count, bpg);
			desc_blocks = (group_desc_count +
				       gdpb - 1) / gdpb;
			rsv_groups = ext2fs_div_ceil(resize, bpg);
			rsv_gdb = ext2fs_div_ceil(rsv_groups, gdpb) - 
				desc_blocks;
			if (rsv_gdb > (int) EXT2_ADDR_PER_BLOCK(param))
				rsv_gdb = EXT2_ADDR_PER_BLOCK(param);

			if (rsv_gdb > 0) {
				if (param->s_rev_level == EXT2_GOOD_OLD_REV) {
					fprintf(stderr, 
	_("On-line resizing not supported with revision 0 filesystems\n"));
					free(buf);
					exit(1);
				}
				param->s_feature_compat |=
					EXT2_FEATURE_COMPAT_RESIZE_INODE;

				param->s_reserved_gdt_blocks = rsv_gdb;
			}
		} else if (!strcmp(token, "test_fs")) {
			param->s_flags |= EXT2_FLAGS_TEST_FILESYS;
		} else {
			r_usage++;
			badopt = token;
		}
	}
	if (r_usage) {
		fprintf(stderr, _("\nBad option(s) specified: %s\n\n"
			"Extended options are separated by commas, "
			"and may take an argument which\n"
			"\tis set off by an equals ('=') sign.\n\n"
			"Valid extended options are:\n"
			"\tstride=<RAID per-disk data chunk in blocks>\n"
			"\tstripe-width=<RAID stride * data disks in blocks>\n"
			"\tresize=<resize maximum size in blocks>\n\n"
			"\ttest_fs\n"),
			badopt);
		free(buf);
		exit(1);
	}
	if (param->s_raid_stride &&
	    (param->s_raid_stripe_width % param->s_raid_stride) != 0)
		fprintf(stderr, _("\nWarning: RAID stripe-width %u not an even "
				  "multiple of stride %u.\n\n"),
			param->s_raid_stripe_width, param->s_raid_stride);

	free(buf);
}	