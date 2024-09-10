void pci_init_board(void)
{
	int mem_target, mem_attr, i;
	int bus = 0;
	u32 reg;
	u32 soc_ctrl = readl(MVEBU_SYSTEM_REG_BASE + 0x4);

	/* Check SoC Control Power State */
	debug("%s: SoC Control %08x, 0en %01lx, 1en %01lx, 2en %01lx\n",
	      __func__, soc_ctrl, SELECT(soc_ctrl, 0), SELECT(soc_ctrl, 1),
	      SELECT(soc_ctrl, 2));

	for (i = 0; i < MAX_PEX; i++) {
		struct mvebu_pcie *pcie = &pcie_bus[i];
		struct pci_controller *hose = &pcie->hose;

		/* Get port number, lane number and memory target / attr */
		mvebu_get_port_lane(pcie, i, &mem_target, &mem_attr);

		/* Don't read at all from pci registers if port power is down */
		if (pcie->lane == 0 && SELECT(soc_ctrl, pcie->port) == 0) {
			i += 3;
			debug("%s: skipping port %d\n", __func__, pcie->port);
			continue;
		}

		pcie->base = (void __iomem *)PCIE_BASE(i);

		/* Check link and skip ports that have no link */
		if (!mvebu_pcie_link_up(pcie)) {
			debug("%s: PCIe %d.%d - down\n", __func__,
			      pcie->port, pcie->lane);
			continue;
		}
		debug("%s: PCIe %d.%d - up, base %08x\n", __func__,
		      pcie->port, pcie->lane, (u32)pcie->base);

		/* Read Id info and local bus/dev */
		debug("direct conf read %08x, local bus %d, local dev %d\n",
		      readl(pcie->base), mvebu_pcie_get_local_bus_nr(pcie),
		      mvebu_pcie_get_local_dev_nr(pcie));

		mvebu_pcie_set_local_bus_nr(pcie, bus);
		mvebu_pcie_set_local_dev_nr(pcie, 0);
		pcie->dev = PCI_BDF(bus, 0, 0);

		pcie->mem.start = (u32)mvebu_pcie_membase;
		pcie->mem.end = pcie->mem.start + PCIE_MEM_SIZE - 1;
		mvebu_pcie_membase += PCIE_MEM_SIZE;

		if (mvebu_mbus_add_window_by_id(mem_target, mem_attr,
						(phys_addr_t)pcie->mem.start,
						PCIE_MEM_SIZE)) {
			printf("PCIe unable to add mbus window for mem at %08x+%08x\n",
			       (u32)pcie->mem.start, PCIE_MEM_SIZE);
		}

		/* Setup windows and configure host bridge */
		mvebu_pcie_setup_wins(pcie);

		/* Master + slave enable. */
		reg = readl(pcie->base + PCIE_CMD_OFF);
		reg |= PCI_COMMAND_MEMORY;
		reg |= PCI_COMMAND_MASTER;
		reg |= BIT(10);		/* disable interrupts */
		writel(reg, pcie->base + PCIE_CMD_OFF);

		/* Setup U-Boot PCI Controller */
		hose->first_busno = 0;
		hose->current_busno = bus;

		/* PCI memory space */
		pci_set_region(hose->regions + 0, pcie->mem.start,
			       pcie->mem.start, PCIE_MEM_SIZE, PCI_REGION_MEM);
		pci_set_region(hose->regions + 1,
			       0, 0,
			       gd->ram_size,
			       PCI_REGION_MEM | PCI_REGION_SYS_MEMORY);
		hose->region_count = 2;

		pci_set_ops(hose,
			    pci_hose_read_config_byte_via_dword,
			    pci_hose_read_config_word_via_dword,
			    mvebu_pcie_read_config_dword,
			    pci_hose_write_config_byte_via_dword,
			    pci_hose_write_config_word_via_dword,
			    mvebu_pcie_write_config_dword);
		pci_register_hose(hose);

		hose->last_busno = pci_hose_scan(hose);

		/* Set BAR0 to internal registers */
		writel(SOC_REGS_PHY_BASE, pcie->base + PCIE_BAR_LO_OFF(0));
		writel(0, pcie->base + PCIE_BAR_HI_OFF(0));

		bus = hose->last_busno + 1;
	}
}