static int do_iommu_domain_map(struct hisi_iommu_domain *hisi_domain,struct scatterlist *sgl,
		struct iommu_map_format *format, struct map_result *result)
{
	int ret;
	unsigned long phys_len, iova_size;
	unsigned long iova_start;

	struct gen_pool *pool;
	struct iommu_domain *domain;
	struct scatterlist *sg;
	struct tile_format fmt;
	/* calculate whole phys mem length */
	for (phys_len = 0, sg = sgl; sg; sg = sg_next(sg)) {
		phys_len += (unsigned long)ALIGN(sg->length, PAGE_SIZE);
	}

	/* get io virtual address size */
	if (format->is_tile) {
		unsigned long lines;
		unsigned long body_size;
		body_size = phys_len - format->header_size;
		lines = body_size / (format->phys_page_line * PAGE_SIZE);

		/*header need more lines virtual space*/
		if ( format->header_size ){
			unsigned long header_size;
			header_size = ALIGN(format->header_size ,format->virt_page_line * PAGE_SIZE);
			lines +=  header_size / (format->virt_page_line * PAGE_SIZE);
		}

		iova_size = lines * format->virt_page_line * PAGE_SIZE ;
	} else {
		iova_size = phys_len;
	}

	/* alloc iova */
	pool = hisi_domain->iova_pool;
	domain = hisi_domain->domain;
	iova_start = hisi_alloc_iova(pool,iova_size,hisi_domain->range.align);
	if (!iova_start) {
		printk("[%s]hisi_alloc_iova alloc 0x%lx failed!\n", __func__, iova_size);
		printk("[%s]dump iova pool begain--------------------------\n", __func__);
		printk("iova available: 0x%x\n",(unsigned int)hisi_iommu_iova_available());
		printk("alloc count: %d, free count: %d\n",
				dbg_inf.alloc_iova_count, dbg_inf.free_iova_count);
		printk("[%s]dump iova pool end   --------------------------\n", __func__);
		return -EINVAL;
	}

	if (0x100000000 < (iova_start + iova_size)) {
		pr_err("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! "
				"hisi iommu can not deal with iova 0x%lx size 0x%lx\n",
				iova_start, iova_size);
	}

	/* do map */
	if (format->is_tile) {
		fmt.is_tile = format->is_tile;
		fmt.phys_page_line = format->phys_page_line;
		fmt.virt_page_line = format->virt_page_line;
		fmt.header_size = format->header_size ;
		ret = iommu_map_tile(domain, iova_start, sgl, iova_size, 0,&fmt);
	} else {
		ret = iommu_map_range(domain, iova_start,sgl,(size_t)iova_size,format->prot);
	}

	if (ret) {
		printk(KERN_ERR "[%s]map failed!\n", __func__);
		hisi_free_iova(pool, iova_start, iova_size);
		return ret;
	}else {
		/* out put result */
		result->iova_start = iova_start;
		result->iova_size = iova_size;
	}
	return 0;
}