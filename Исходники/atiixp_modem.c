static int snd_atiixp_pcm_open(struct snd_pcm_substream *substream,
			       struct atiixp_dma *dma, int pcm_type)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;
	static unsigned int rates[] = { 8000,  9600, 12000, 16000 };
	static struct snd_pcm_hw_constraint_list hw_constraints_rates = {
		.count = ARRAY_SIZE(rates),
		.list = rates,
		.mask = 0,
	};

	if (snd_BUG_ON(!dma->ops || !dma->ops->enable_dma))
		return -EINVAL;

	if (dma->opened)
		return -EBUSY;
	dma->substream = substream;
	runtime->hw = snd_atiixp_pcm_hw;
	dma->ac97_pcm_type = pcm_type;
	if ((err = snd_pcm_hw_constraint_list(runtime, 0,
					      SNDRV_PCM_HW_PARAM_RATE,
					      &hw_constraints_rates)) < 0)
		return err;
	if ((err = snd_pcm_hw_constraint_integer(runtime,
						 SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		return err;
	runtime->private_data = dma;

	/* enable DMA bits */
	spin_lock_irq(&chip->reg_lock);
	dma->ops->enable_dma(chip, 1);
	spin_unlock_irq(&chip->reg_lock);
	dma->opened = 1;

	return 0;
}

static int snd_atiixp_pcm_close(struct snd_pcm_substream *substream,
				struct atiixp_dma *dma)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	/* disable DMA bits */
	if (snd_BUG_ON(!dma->ops || !dma->ops->enable_dma))
		return -EINVAL;
	spin_lock_irq(&chip->reg_lock);
	dma->ops->enable_dma(chip, 0);
	spin_unlock_irq(&chip->reg_lock);
	dma->substream = NULL;
	dma->opened = 0;
	return 0;
}

/*
 */
static int snd_atiixp_playback_open(struct snd_pcm_substream *substream)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	int err;

	mutex_lock(&chip->open_mutex);
	err = snd_atiixp_pcm_open(substream, &chip->dmas[ATI_DMA_PLAYBACK], 0);
	mutex_unlock(&chip->open_mutex);
	if (err < 0)
		return err;
	return 0;
}

static int snd_atiixp_playback_close(struct snd_pcm_substream *substream)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	int err;
	mutex_lock(&chip->open_mutex);
	err = snd_atiixp_pcm_close(substream, &chip->dmas[ATI_DMA_PLAYBACK]);
	mutex_unlock(&chip->open_mutex);
	return err;
}

static int snd_atiixp_capture_open(struct snd_pcm_substream *substream)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	return snd_atiixp_pcm_open(substream, &chip->dmas[ATI_DMA_CAPTURE], 1);
}

static int snd_atiixp_capture_close(struct snd_pcm_substream *substream)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	return snd_atiixp_pcm_close(substream, &chip->dmas[ATI_DMA_CAPTURE]);
}


/* AC97 playback */
static struct snd_pcm_ops snd_atiixp_playback_ops = {
	.open =		snd_atiixp_playback_open,
	.close =	snd_atiixp_playback_close,
	.ioctl =	snd_pcm_lib_ioctl,
	.hw_params =	snd_atiixp_pcm_hw_params,
	.hw_free =	snd_atiixp_pcm_hw_free,
	.prepare =	snd_atiixp_playback_prepare,
	.trigger =	snd_atiixp_pcm_trigger,
	.pointer =	snd_atiixp_pcm_pointer,
};

/* AC97 capture */
static struct snd_pcm_ops snd_atiixp_capture_ops = {
	.open =		snd_atiixp_capture_open,
	.close =	snd_atiixp_capture_close,
	.ioctl =	snd_pcm_lib_ioctl,
	.hw_params =	snd_atiixp_pcm_hw_params,
	.hw_free =	snd_atiixp_pcm_hw_free,
	.prepare =	snd_atiixp_capture_prepare,
	.trigger =	snd_atiixp_pcm_trigger,
	.pointer =	snd_atiixp_pcm_pointer,
};

static struct atiixp_dma_ops snd_atiixp_playback_dma_ops = {
	.type = ATI_DMA_PLAYBACK,
	.llp_offset = ATI_REG_MODEM_OUT_DMA1_LINKPTR,
	.dt_cur = ATI_REG_MODEM_OUT_DMA1_DT_CUR,
	.enable_dma = atiixp_out_enable_dma,
	.enable_transfer = atiixp_out_enable_transfer,
	.flush_dma = atiixp_out_flush_dma,
};
	
static struct atiixp_dma_ops snd_atiixp_capture_dma_ops = {
	.type = ATI_DMA_CAPTURE,
	.llp_offset = ATI_REG_MODEM_IN_DMA_LINKPTR,
	.dt_cur = ATI_REG_MODEM_IN_DMA_DT_CUR,
	.enable_dma = atiixp_in_enable_dma,
	.enable_transfer = atiixp_in_enable_transfer,
	.flush_dma = atiixp_in_flush_dma,
};

static int __devinit snd_atiixp_pcm_new(struct atiixp_modem *chip)
{
	struct snd_pcm *pcm;
	int err;

	/* initialize constants */
	chip->dmas[ATI_DMA_PLAYBACK].ops = &snd_atiixp_playback_dma_ops;
	chip->dmas[ATI_DMA_CAPTURE].ops = &snd_atiixp_capture_dma_ops;

	/* PCM #0: analog I/O */
	err = snd_pcm_new(chip->card, "ATI IXP MC97", ATI_PCMDEV_ANALOG, 1, 1, &pcm);
	if (err < 0)
		return err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_atiixp_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_atiixp_capture_ops);
	pcm->dev_class = SNDRV_PCM_CLASS_MODEM;
	pcm->private_data = chip;
	strcpy(pcm->name, "ATI IXP MC97");
	chip->pcmdevs[ATI_PCMDEV_ANALOG] = pcm;

	snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
					      snd_dma_pci_data(chip->pci),
					      64*1024, 128*1024);

	return 0;
}



/*
 * interrupt handler
 */
static irqreturn_t snd_atiixp_interrupt(int irq, void *dev_id)
{
	struct atiixp_modem *chip = dev_id;
	unsigned int status;

	status = atiixp_read(chip, ISR);

	if (! status)
		return IRQ_NONE;

	/* process audio DMA */
	if (status & ATI_REG_ISR_MODEM_OUT1_XRUN)
		snd_atiixp_xrun_dma(chip,  &chip->dmas[ATI_DMA_PLAYBACK]);
	else if (status & ATI_REG_ISR_MODEM_OUT1_STATUS)
		snd_atiixp_update_dma(chip, &chip->dmas[ATI_DMA_PLAYBACK]);
	if (status & ATI_REG_ISR_MODEM_IN_XRUN)
		snd_atiixp_xrun_dma(chip,  &chip->dmas[ATI_DMA_CAPTURE]);
	else if (status & ATI_REG_ISR_MODEM_IN_STATUS)
		snd_atiixp_update_dma(chip, &chip->dmas[ATI_DMA_CAPTURE]);

	/* for codec detection */
	if (status & CODEC_CHECK_BITS) {
		unsigned int detected;
		detected = status & CODEC_CHECK_BITS;
		spin_lock(&chip->reg_lock);
		chip->codec_not_ready_bits |= detected;
		atiixp_update(chip, IER, detected, 0); /* disable the detected irqs */
		spin_unlock(&chip->reg_lock);
	}

	/* ack */
	atiixp_write(chip, ISR, status);

	return IRQ_HANDLED;
}


/*
 * ac97 mixer section
 */

static int __devinit snd_atiixp_mixer_new(struct atiixp_modem *chip, int clock)
{
	struct snd_ac97_bus *pbus;
	struct snd_ac97_template ac97;
	int i, err;
	int codec_count;
	static struct snd_ac97_bus_ops ops = {
		.write = snd_atiixp_ac97_write,
		.read = snd_atiixp_ac97_read,
	};
	static unsigned int codec_skip[NUM_ATI_CODECS] = {
		ATI_REG_ISR_CODEC0_NOT_READY,
		ATI_REG_ISR_CODEC1_NOT_READY,
		ATI_REG_ISR_CODEC2_NOT_READY,
	};

	if (snd_atiixp_codec_detect(chip) < 0)
		return -ENXIO;

	if ((err = snd_ac97_bus(chip->card, 0, &ops, chip, &pbus)) < 0)
		return err;
	pbus->clock = clock;
	chip->ac97_bus = pbus;

	codec_count = 0;
	for (i = 0; i < NUM_ATI_CODECS; i++) {
		if (chip->codec_not_ready_bits & codec_skip[i])
			continue;
		memset(&ac97, 0, sizeof(ac97));
		ac97.private_data = chip;
		ac97.pci = chip->pci;
		ac97.num = i;
		ac97.scaps = AC97_SCAP_SKIP_AUDIO | AC97_SCAP_POWER_SAVE;
		if ((err = snd_ac97_mixer(pbus, &ac97, &chip->ac97[i])) < 0) {
			chip->ac97[i] = NULL; /* to be sure */
			snd_printdd("atiixp-modem: codec %d not available for modem\n", i);
			continue;
		}
		codec_count++;
	}

	if (! codec_count) {
		snd_printk(KERN_ERR "atiixp-modem: no codec available\n");
		return -ENODEV;
	}

	/* snd_ac97_tune_hardware(chip->ac97, ac97_quirks); */

	return 0;
}


#ifdef CONFIG_PM
/*
 * power management
 */
static int snd_atiixp_suspend(struct pci_dev *pci, pm_message_t state)
{
	struct snd_card *card = pci_get_drvdata(pci);
	struct atiixp_modem *chip = card->private_data;
	int i;

	snd_power_change_state(card, SNDRV_CTL_POWER_D3hot);
	for (i = 0; i < NUM_ATI_PCMDEVS; i++)
		snd_pcm_suspend_all(chip->pcmdevs[i]);
	for (i = 0; i < NUM_ATI_CODECS; i++)
		snd_ac97_suspend(chip->ac97[i]);
	snd_atiixp_aclink_down(chip);
	snd_atiixp_chip_stop(chip);

	pci_disable_device(pci);
	pci_save_state(pci);
	pci_set_power_state(pci, pci_choose_state(pci, state));
	return 0;
}

static int snd_atiixp_resume(struct pci_dev *pci)
{
	struct snd_card *card = pci_get_drvdata(pci);
	struct atiixp_modem *chip = card->private_data;
	int i;

	pci_set_power_state(pci, PCI_D0);
	pci_restore_state(pci);
	if (pci_enable_device(pci) < 0) {
		printk(KERN_ERR "atiixp-modem: pci_enable_device failed, "
		       "disabling device\n");
		snd_card_disconnect(card);
		return -EIO;
	}
	pci_set_master(pci);

	snd_atiixp_aclink_reset(chip);
	snd_atiixp_chip_start(chip);

	for (i = 0; i < NUM_ATI_CODECS; i++)
		snd_ac97_resume(chip->ac97[i]);

	snd_power_change_state(card, SNDRV_CTL_POWER_D0);
	return 0;
}
#endif /* CONFIG_PM */


#ifdef CONFIG_PROC_FS
/*
 * proc interface for register dump
 */

static void snd_atiixp_proc_read(struct snd_info_entry *entry,
				 struct snd_info_buffer *buffer)
{
	struct atiixp_modem *chip = entry->private_data;
	int i;

	for (i = 0; i < 256; i += 4)
		snd_iprintf(buffer, "%02x: %08x\n", i, readl(chip->remap_addr + i));
}

static void __devinit snd_atiixp_proc_init(struct atiixp_modem *chip)
{
	struct snd_info_entry *entry;

	if (! snd_card_proc_new(chip->card, "atiixp-modem", &entry))
		snd_info_set_text_ops(entry, chip, snd_atiixp_proc_read);
}
#else
#define snd_atiixp_proc_init(chip)
#endif


/*
 * destructor
 */

static int snd_atiixp_free(struct atiixp_modem *chip)
{
	if (chip->irq < 0)
		goto __hw_end;
	snd_atiixp_chip_stop(chip);

      __hw_end:
	if (chip->irq >= 0)
		free_irq(chip->irq, chip);
	if (chip->remap_addr)
		iounmap(chip->remap_addr);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);
	kfree(chip);
	return 0;
}

static int snd_atiixp_dev_free(struct snd_device *device)
{
	struct atiixp_modem *chip = device->device_data;
	return snd_atiixp_free(chip);
}

/*
 * constructor for chip instance
 */
static int __devinit snd_atiixp_create(struct snd_card *card,
				       struct pci_dev *pci,
				       struct atiixp_modem **r_chip)
{
	static struct snd_device_ops ops = {
		.dev_free =	snd_atiixp_dev_free,
	};
	struct atiixp_modem *chip;
	int err;

	if ((err = pci_enable_device(pci)) < 0)
		return err;

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (chip == NULL) {
		pci_disable_device(pci);
		return -ENOMEM;
	}

	spin_lock_init(&chip->reg_lock);
	mutex_init(&chip->open_mutex);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	if ((err = pci_request_regions(pci, "ATI IXP MC97")) < 0) {
		kfree(chip);
		pci_disable_device(pci);
		return err;
	}
	chip->addr = pci_resource_start(pci, 0);
	chip->remap_addr = pci_ioremap_bar(pci, 0);
	if (chip->remap_addr == NULL) {
		snd_printk(KERN_ERR "AC'97 space ioremap problem\n");
		snd_atiixp_free(chip);
		return -EIO;
	}

	if (request_irq(pci->irq, snd_atiixp_interrupt, IRQF_SHARED,
			card->shortname, chip)) {
		snd_printk(KERN_ERR "unable to grab IRQ %d\n", pci->irq);
		snd_atiixp_free(chip);
		return -EBUSY;
	}
	chip->irq = pci->irq;
	pci_set_master(pci);
	synchronize_irq(chip->irq);

	if ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) {
		snd_atiixp_free(chip);
		return err;
	}

	snd_card_set_dev(card, &pci->dev);

	*r_chip = chip;
	return 0;
}


static int __devinit snd_atiixp_probe(struct pci_dev *pci,
				      const struct pci_device_id *pci_id)
{
	struct snd_card *card;
	struct atiixp_modem *chip;
	int err;

	err = snd_card_create(index, id, THIS_MODULE, 0, &card);
	if (err < 0)
		return err;

	strcpy(card->driver, "ATIIXP-MODEM");
	strcpy(card->shortname, "ATI IXP Modem");
	if ((err = snd_atiixp_create(card, pci, &chip)) < 0)
		goto __error;
	card->private_data = chip;

	if ((err = snd_atiixp_aclink_reset(chip)) < 0)
		goto __error;

	if ((err = snd_atiixp_mixer_new(chip, ac97_clock)) < 0)
		goto __error;

	if ((err = snd_atiixp_pcm_new(chip)) < 0)
		goto __error;
	
	snd_atiixp_proc_init(chip);

	snd_atiixp_chip_start(chip);

	sprintf(card->longname, "%s rev %x at 0x%lx, irq %i",
		card->shortname, pci->revision, chip->addr, chip->irq);

	if ((err = snd_card_register(card)) < 0)
		goto __error;

	pci_set_drvdata(pci, card);
	return 0;

 __error:
	snd_card_free(card);
	return err;
}

static void __devexit snd_atiixp_remove(struct pci_dev *pci)
{
	snd_card_free(pci_get_drvdata(pci));
	pci_set_drvdata(pci, NULL);
}