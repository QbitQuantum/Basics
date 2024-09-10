/*
 * See <Documentation/x86/x86_64/boot-options.txt> for the iommu kernel
 * parameter documentation.
 */
static __init int iommu_setup(char *p)
{
	iommu_merge = 1;

	if (!p)
		return -EINVAL;

	while (*p) {
		if (!strncmp(p, "off", 3))
			no_iommu = 1;
		/* gart_parse_options has more force support */
		if (!strncmp(p, "force", 5))
			force_iommu = 1;
		if (!strncmp(p, "noforce", 7)) {
			iommu_merge = 0;
			force_iommu = 0;
		}

		if (!strncmp(p, "biomerge", 8)) {
			iommu_merge = 1;
			force_iommu = 1;
		}
		if (!strncmp(p, "panic", 5))
			panic_on_overflow = 1;
		if (!strncmp(p, "nopanic", 7))
			panic_on_overflow = 0;
		if (!strncmp(p, "merge", 5)) {
			iommu_merge = 1;
			force_iommu = 1;
		}
		if (!strncmp(p, "nomerge", 7))
			iommu_merge = 0;
		if (!strncmp(p, "forcesac", 8))
			iommu_sac_force = 1;
		if (!strncmp(p, "allowdac", 8))
			forbid_dac = 0;
		if (!strncmp(p, "nodac", 5))
			forbid_dac = 1;
		if (!strncmp(p, "usedac", 6)) {
			forbid_dac = -1;
			return 1;
		}
#ifdef CONFIG_SWIOTLB
		if (!strncmp(p, "soft", 4))
			swiotlb = 1;
#endif
		if (!strncmp(p, "pt", 2))
			iommu_pass_through = 1;
		if (!strncmp(p, "group_mf", 8))
			iommu_group_mf = 1;

		gart_parse_options(p);

#ifdef CONFIG_CALGARY_IOMMU
		if (!strncmp(p, "calgary", 7))
			use_calgary = 1;
#endif /* CONFIG_CALGARY_IOMMU */

		p += strcspn(p, ",");
		if (*p == ',')
			++p;
	}
	return 0;
}