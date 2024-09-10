static void
pci_vtcon_control_tx(struct pci_vtcon_port *port, void *arg, struct iovec *iov,
    int niov)
{
	struct pci_vtcon_softc *sc;
	struct pci_vtcon_port *tmp;
	struct pci_vtcon_control resp, *ctrl;
	int i;

	assert(niov == 1);

	sc = port->vsp_sc;
	ctrl = (struct pci_vtcon_control *)iov->iov_base;

	switch (ctrl->event) {
	case VTCON_DEVICE_READY:
		/* set port ready events for registered ports */
		for (i = 0; i < VTCON_MAXPORTS; i++) {
			tmp = &sc->vsc_ports[i];
			if (tmp->vsp_enabled)
				pci_vtcon_announce_port(tmp);
		}
		break;

	case VTCON_PORT_READY:
		if (ctrl->id >= sc->vsc_nports) {
			WPRINTF(("VTCON_PORT_READY event for unknown port %d\n",
			    ctrl->id));
			return;
		}

		tmp = &sc->vsc_ports[ctrl->id];
		if (tmp->vsp_console) {
			resp.event = VTCON_CONSOLE_PORT;
			resp.id = ctrl->id;
			resp.value = 1;
			pci_vtcon_control_send(sc, &resp, NULL, 0);
		}
		break;
	}
}