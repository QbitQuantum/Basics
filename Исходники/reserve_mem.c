void __init s5p_cma_region_reserve(struct cma_region *regions_normal,
				      struct cma_region *regions_secure,
				      size_t align_secure, const char *map)
{
	struct cma_region *reg;
	phys_addr_t paddr_last = 0xFFFFFFFF;

	for (reg = regions_normal; reg->size != 0; reg++) {
		phys_addr_t paddr;

		if (!IS_ALIGNED(reg->size, PAGE_SIZE)) {
			pr_debug("S5P/CMA: size of '%s' is NOT page-aligned\n",
								reg->name);
			reg->size = PAGE_ALIGN(reg->size);
		}


		if (reg->reserved) {
			pr_err("S5P/CMA: '%s' already reserved\n", reg->name);
			continue;
		}

		if (reg->alignment) {
			if ((reg->alignment & ~PAGE_MASK) ||
				(reg->alignment & ~reg->alignment)) {
				pr_err("S5P/CMA: Failed to reserve '%s': "
						"incorrect alignment 0x%08x.\n",
						reg->name, reg->alignment);
				continue;
			}
		} else {
			reg->alignment = PAGE_SIZE;
		}

		if (reg->start) {
			if (!memblock_is_region_reserved(reg->start, reg->size)
			    && (memblock_reserve(reg->start, reg->size) == 0))
				reg->reserved = 1;
			else {
				pr_err("S5P/CMA: Failed to reserve '%s'\n",
				       reg->name);
				continue;
			}

			pr_debug("S5P/CMA: "
				 "Reserved 0x%08x/0x%08x for '%s'\n",
				 reg->start, reg->size, reg->name);
			paddr = reg->start;
		} else {
			paddr = memblock_find_in_range(0,
					MEMBLOCK_ALLOC_ACCESSIBLE,
					reg->size, reg->alignment);
		}

		if (paddr) {
			if (memblock_reserve(paddr, reg->size)) {
				pr_err("S5P/CMA: Failed to reserve '%s'\n",
								reg->name);
				continue;
			}

			reg->start = paddr;
			reg->reserved = 1;

			pr_info("S5P/CMA: Reserved 0x%08x/0x%08x for '%s'\n",
						reg->start, reg->size, reg->name);
		} else {
			pr_err("S5P/CMA: No free space in memory for '%s'\n",
								reg->name);
		}

		if (cma_early_region_register(reg)) {
			pr_err("S5P/CMA: Failed to register '%s'\n",
								reg->name);
			memblock_free(reg->start, reg->size);
		} else {
			paddr_last = min(paddr, paddr_last);
		}
	}

	if (align_secure & ~align_secure) {
		pr_err("S5P/CMA: "
			"Wrong alignment requirement for secure region.\n");
	} else if (regions_secure && regions_secure->size) {
		size_t size_secure = 0;

		for (reg = regions_secure; reg->size != 0; reg++)
			size_secure += reg->size;

		reg--;

		/* Entire secure regions will be merged into 2
		 * consecutive regions. */
		if (align_secure == 0) {
			size_t size_region2;
			size_t order_region2;
			size_t aug_size;

			align_secure = 1 <<
				(get_order((size_secure + 1) / 2) + PAGE_SHIFT);
			/* Calculation of a subregion size */
			size_region2 = size_secure - align_secure;
			order_region2 = get_order(size_region2) + PAGE_SHIFT;
			if (order_region2 < 20)
				order_region2 = 20; /* 1MB */
			order_region2 -= 3; /* divide by 8 */
			size_region2 = ALIGN(size_region2, 1 << order_region2);

			aug_size = align_secure + size_region2 - size_secure;
			if (aug_size > 0) {
				reg->size += aug_size;
				size_secure += aug_size;
				pr_debug("S5P/CMA: "
					"Augmented size of '%s' by %#x B.\n",
					reg->name, aug_size);
			}
		} else
			size_secure = ALIGN(size_secure, align_secure);

		pr_info("S5P/CMA: "
			"Reserving %#x for secure region aligned by %#x.\n",
						size_secure, align_secure);

		if (paddr_last >= memblock.current_limit) {
			paddr_last = memblock_find_in_range(0,
					MEMBLOCK_ALLOC_ACCESSIBLE,
					size_secure, reg->alignment);
		} else {
			paddr_last -= size_secure;
			paddr_last = round_down(paddr_last, align_secure);
		}

		if (paddr_last) {
#ifndef CONFIG_DMA_CMA
			while (memblock_reserve(paddr_last, size_secure))
				paddr_last -= align_secure;
#else
			if (!reg->start) {
				while (memblock_reserve(paddr_last,
							size_secure))
					paddr_last -= align_secure;
			}
#endif

			do {
#ifndef CONFIG_DMA_CMA
				reg->start = paddr_last;
				reg->reserved = 1;
				paddr_last += reg->size;
#else
				if (reg->start) {
					reg->reserved = 1;
#ifdef CONFIG_USE_MFC_CMA
#if defined(CONFIG_MACH_M0)
					if (reg->start == 0x5C100000) {
						if (memblock_reserve(0x5C100000,
								0x700000))
							panic("memblock\n");
						if (memblock_reserve(0x5F000000,
								0x200000))
							panic("memblock\n");
					} else
#elif defined(CONFIG_MACH_GC1)
					if (reg->start == 0x50400000) {
						if (memblock_reserve(0x50400000,
								0x400000))
							panic("memblock\n");
						if (memblock_reserve(0x53000000,
								0x500000))
							panic("memblock\n");
					} else
#endif
					{
						if (memblock_reserve(reg->start,
								reg->size))
							panic("memblock\n");
					}
#else
					if (memblock_reserve(reg->start,
								reg->size))
						panic("memblock\n");
#endif
				} else {
					reg->start = paddr_last;
					reg->reserved = 1;
					paddr_last += reg->size;
				}
#endif
				pr_info("S5P/CMA: "
					"Reserved 0x%08x/0x%08x for '%s'\n",
					reg->start, reg->size, reg->name);
				if (cma_early_region_register(reg)) {
					memblock_free(reg->start, reg->size);
					pr_err("S5P/CMA: "
					"Failed to register secure region "
					"'%s'\n", reg->name);
				} else {
					size_secure -= reg->size;
				}
			} while (reg-- != regions_secure);

			if (size_secure > 0)
				memblock_free(paddr_last, size_secure);
		} else {
			pr_err("S5P/CMA: Failed to reserve secure regions\n");
		}
	}

	if (map)
		cma_set_defaults(NULL, map);
}