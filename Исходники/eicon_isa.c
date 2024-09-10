int
eicon_isa_load(eicon_isa_card *card, eicon_isa_codebuf *cb) {
	eicon_isa_boot    *boot;
	int               tmp;
	int               timeout;
	int 		  j;
	eicon_isa_codebuf cbuf;
	unsigned char     *code;
	unsigned char     *p;

	if (copy_from_user(&cbuf, cb, sizeof(eicon_isa_codebuf)))
		return -EFAULT;

	if (!(code = kmalloc(cbuf.firmware_len, GFP_KERNEL))) {
		printk(KERN_WARNING "eicon_isa_load: Couldn't allocate code buffer\n");
		return -ENOMEM;
	}

	if (copy_from_user(code, &cb->code, cbuf.firmware_len)) {
		kfree(code);
		return -EFAULT;
	}

	boot = &card->shmem->boot;

	if ((!card->ivalid) && card->master) {
		card->irqprobe = 1;
		/* Check for valid IRQ */
		if ((card->irq < 0) || (card->irq > 15) || 
		    (!((1 << card->irq) & eicon_isa_valid_irq[card->type & 0x0f]))) {
			printk(KERN_WARNING "eicon_isa_load: illegal irq: %d\n", card->irq);
			eicon_isa_release_shmem(card);
			kfree(code);
			return -EINVAL;
		}
		/* Register irq */
		if (!request_irq(card->irq, &eicon_irq, 0, "Eicon ISA ISDN", card))
			card->ivalid = 1;
		else {
			printk(KERN_WARNING "eicon_isa_load: irq %d already in use.\n",
			       card->irq);
			eicon_isa_release_shmem(card);
			kfree(code);
			return -EBUSY;
		}
	}

        tmp = readb(&boot->msize);
        if (tmp != 8 && tmp != 16 && tmp != 24 &&
            tmp != 32 && tmp != 48 && tmp != 60) {
                printk(KERN_WARNING "eicon_isa_load: invalid memsize\n");
		eicon_isa_release_shmem(card);
                return -EIO;
        }

	eicon_isa_printpar(card);

	/* Download firmware */
	printk(KERN_INFO "%s %dkB, loading firmware ...\n", 
	       eicon_ctype_name[card->type],
	       tmp * 16);
	tmp = cbuf.firmware_len >> 8;
	p = code;
	while (tmp--) {
		memcpy_toio(&boot->b, p, 256);
		writeb(1, &boot->ctrl);
		timeout = jiffies + HZ / 10;
		while (time_before(jiffies, timeout)) {
			if (readb(&boot->ctrl) == 0)
				break;
			SLEEP(2);
		}
		if (readb(&boot->ctrl)) {
			printk(KERN_WARNING "eicon_isa_load: download timeout at 0x%x\n", p-code);
			eicon_isa_release(card);
			kfree(code);
			return -EIO;
		}
		p += 256;
	}
	kfree(code);

	/* Initialize firmware parameters */
	memcpy_toio(&card->shmem->c[8], &cbuf.tei, 14);
	memcpy_toio(&card->shmem->c[32], &cbuf.oad, 96);
	memcpy_toio(&card->shmem->c[128], &cbuf.oad, 96);
	
	/* Start firmware, wait for signature */
	writeb(2, &boot->ctrl);
	timeout = jiffies + (5*HZ);
	while (time_before(jiffies, timeout)) {
		if (readw(&boot->signature) == 0x4447)
			break;
		SLEEP(2);
	}
	if (readw(&boot->signature) != 0x4447) {
		printk(KERN_WARNING "eicon_isa_load: firmware selftest failed %04x\n",
		       readw(&boot->signature));
		eicon_isa_release(card);
		return -EIO;
	}

	card->channels = readb(&card->shmem->c[0x3f6]);

	/* clear irq-requests, reset irq-count */
	readb(card->intack);
	writeb(0, card->intack);

	if (card->master) {
		card->irqprobe = 1;
		/* Trigger an interrupt and check if it is delivered */
		tmp = readb(&card->shmem->com.ReadyInt);
		tmp ++;
		writeb(tmp, &card->shmem->com.ReadyInt);
		timeout = jiffies + HZ / 5;
		while (time_before(jiffies, timeout)) {
			if (card->irqprobe > 1)
				break;
			SLEEP(2);
		}
		if (card->irqprobe == 1) {
			printk(KERN_WARNING "eicon_isa_load: IRQ # %d test failed\n", card->irq);
			eicon_isa_release(card);
			return -EIO;
		}
	}
#ifdef EICON_MCA_DEBUG
	printk(KERN_INFO "eicon_isa_load: IRQ # %d test succeeded.\n", card->irq);
#endif

	writeb(card->irq, &card->shmem->com.Int);

	/* initializing some variables */
	((eicon_card *)card->card)->ReadyInt = 0;
	((eicon_card *)card->card)->ref_in  = 1;
	((eicon_card *)card->card)->ref_out = 1;
	for(j=0; j<256; j++) ((eicon_card *)card->card)->IdTable[j] = NULL;
	for(j=0; j< (card->channels + 1); j++) {
		((eicon_card *)card->card)->bch[j].e.busy = 0;
		((eicon_card *)card->card)->bch[j].e.D3Id = 0;
		((eicon_card *)card->card)->bch[j].e.B2Id = 0;
		((eicon_card *)card->card)->bch[j].e.ref = 0;
		((eicon_card *)card->card)->bch[j].e.Req = 0;
		((eicon_card *)card->card)->bch[j].e.complete = 1;
		((eicon_card *)card->card)->bch[j].fsm_state = EICON_STATE_NULL;
	}

	printk(KERN_INFO "Eicon: Supported channels: %d\n", card->channels); 
	printk(KERN_INFO "%s successfully started\n", eicon_ctype_name[card->type]);

	/* Enable normal IRQ processing */
	card->irqprobe = 0;
	return 0;
}