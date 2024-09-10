/*
 * This example shows how to retrieve the PMU register mapping information.
 * It does not use the libpfm library. 
 * The mapping gives the translation between the logical register names,
 * as exposed by the perfmon interface, and the actual hardware registers.
 * Depending on the PMU and perfmon implementation, not all registers are
 * necessarily PMU registers, some may correspond to software resources.
 */
int
main(int argc, char **argv)
{
	unsigned long long dfl, rsvd;
	unsigned long hw_addr;
	pfarg_ctx_t ctx;
	char pname[64];
	char name[64], buffer[32];
	unsigned int i, num_pmcs = 0, num_pmds = 0;
	int c, ret, ret2 = 0;
	int use_html = 0;

	while((c=getopt(argc, argv, "hH")) != -1) {
		switch(c) {
			case 'h':
				printf("usage: showreginfo [-h] [-H]\n");
				return 0;
			case 'H':
				use_html = 1;
				break;
			default:
				return -1;

		}
	}

try_again:
	ret = get_value("/sys/kernel/perfmon/pmu_desc/model", buffer, sizeof(buffer));
	if (ret == -1) {
		/*
		 * try to trigger automatic PMU description loading
		 */
		if (ret2 == 0) {
			memset(&ctx, 0, sizeof(ctx));
			ret2 = pfm_create(0, NULL);
			if (ret2 > -1) {
				close(ret2);
				goto try_again;
			}
			fatal_error("invalid or missing perfmon support for your CPU (need at least v3.0)\n");
		}
	}
	if (use_html) {
		puts("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
		puts("<html>");
		puts("<head>");
		puts("<body>");
		puts("<table border=\"5\" frame=\"border\" rules=\"groups\" width=\"60%\" cellpadding=\"2\" cellspacing=\"0\">");
		printf("<caption>%s</caption>\n", buffer);
		puts("<thead><tr align=\"left\">");
		puts("<th>Name</th><th>HW ADDR</th><th>Description</th>");
		puts("<tbody>");
	} else {
		printf("model  : %s\n", buffer);
		puts(  "----------------------------------------------------------------------------\n"
				"name   |   default  value   |   reserved  mask   | hw address | description\n"
				"-------+--------------------+--------------------+------------+-------------");
	}

	for(i=0; i < PFM_MAX_PMCS; i++) {

		sprintf(pname, "/sys/kernel/perfmon/pmu_desc/pmc%d/name", i);
		ret = get_value(pname, name, sizeof(name));
		if (ret)
			continue;

		num_pmcs++;

		sprintf(pname, "/sys/kernel/perfmon/pmu_desc/pmc%d/dfl_val", i);
		get_value(pname, buffer, sizeof(buffer));
		dfl = strtoull(buffer, NULL, 16);

		sprintf(pname, "/sys/kernel/perfmon/pmu_desc/pmc%d/rsvd_msk", i);
		get_value(pname, buffer, sizeof(buffer));
		rsvd = strtoull(buffer, NULL, 16);

		sprintf(pname, "/sys/kernel/perfmon/pmu_desc/pmc%d/addr", i);
		get_value(pname, buffer, sizeof(buffer));
		hw_addr = strtoul(buffer, NULL, 0);

		if (use_html) {
			printf("<tr> <td>PMC%d</td><td>0x%lx</td><td>%s</td>\n",
					i,
					hw_addr,
					name);
		} else {
			printf("pmc%-3d | 0x%016llx | 0x%016llx | 0x%-8lx | %s\n",
					i,
					dfl,
					rsvd,
					hw_addr,
					name);
		}

	}
	if (use_html)
		puts("<tbody>");
	else
		puts("-------+--------------------+--------------------+------------+-------------");

	for(i=0; i < PFM_MAX_PMDS; i++) {

		sprintf(pname, "/sys/kernel/perfmon/pmu_desc/pmd%d/name", i);
		ret = get_value(pname, name, sizeof(name));
		if (ret)
			continue;

		num_pmds++;
		sprintf(pname, "/sys/kernel/perfmon/pmu_desc/pmd%d/dfl_val", i);
		get_value(pname, buffer, sizeof(buffer));
		dfl = strtoull(buffer, NULL, 16);

		sprintf(pname, "/sys/kernel/perfmon/pmu_desc/pmd%d/rsvd_msk", i);
		get_value(pname, buffer, sizeof(buffer));
		rsvd = strtoull(buffer, NULL, 16);

		sprintf(pname, "/sys/kernel/perfmon/pmu_desc/pmd%d/addr", i);
		get_value(pname, buffer, sizeof(buffer));
		hw_addr = strtoul(buffer, NULL, 0);
		if (use_html) {
			printf("<tr> <td>PMC%d</td><td>0x%lx</td><td>%s</td>\n",
					i,
					hw_addr,
					name);
		} else {	
			printf("pmd%-3d | 0x%016llx | 0x%016llx | 0x%-8lx | %s\n",
					i,
					dfl,
					rsvd,
					hw_addr,
					name);
		}
	}
	if (use_html) {
		puts("</table>");
		puts("</body>");
		puts("</html>");
	} else  {
		puts("----------------------------------------------------------------------------");
		printf("%u PMC registers, %u PMD registers\n", num_pmcs, num_pmds);
	}
	return 0;
}