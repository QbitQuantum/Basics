void jgfs_reduce(struct jgfs_dir_ent *dir_ent, uint32_t new_size) {
	if (new_size >= dir_ent->size) {
		errx(1, "jgfs_reduce: new_size is not smaller");
	}
	
	uint16_t clust_before = CEIL(dir_ent->size, jgfs_clust_size()),
		clust_after = CEIL(new_size, jgfs_clust_size());
	
	if (clust_before != clust_after) {
		fat_ent_t this = dir_ent->begin, next;
		
		for (uint16_t i = 1; i <= clust_before; ++i) {
			next = jgfs_fat_read(this);
			
			/* this means the filesystem is inconsistent */
			if (this == FAT_EOF && i < clust_before) {
				warnx("jgfs_reduce: found premature FAT_EOF in clust chain");
				break;
			}
			
			if (i == clust_after) {
				jgfs_fat_write(this, FAT_EOF);
			} else if (i > clust_after) {
				jgfs_fat_write(this, FAT_FREE);
			}
			
			this = next;
		}
		
		/* special case for zero-size files */
		if (clust_after == 0) {
			jgfs_fat_write(dir_ent->begin, FAT_FREE);
			dir_ent->begin = FAT_NALLOC;
		}
	}
	
	dir_ent->size = new_size;
}