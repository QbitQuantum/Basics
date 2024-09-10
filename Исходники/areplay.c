void areplay_init(void)
{
  int size;
  FILE *f;
  
  memset(&action_replay,0,sizeof(action_replay));

  /* store Action replay ROM (max. 128k) & RAM (64k) above cartridge ROM + SRAM area */
  if (cart.romsize > 0x810000) return;
  action_replay.rom = cart.rom + 0x810000;
  action_replay.ram = cart.rom + 0x830000;

  /* Open Action Replay ROM */
  f = fopen(AR_ROM,"rb");
  if (f == NULL) return;

  /* ROM size */
  fseek(f, 0, SEEK_END);
  size = ftell(f);
  fseek(f, 0, SEEK_SET);

  /* detect Action Replay board type */
  switch (size)
  {
    case 0x8000:  
    {
      /* normal Action Replay (32K) */
      action_replay.enabled = TYPE_AR;
  
      /* internal registers mapped at $010000-$01ffff */
      m68k.memory_map[0x01].write16 = ar_write_regs;
      break;
    }

    case 0x10000:
    case 0x20000:
    {
      /* read Stack Pointer */
      uint8 sp[4];
      fread(&sp, 4, 1, f);
      fseek(f, 0, SEEK_SET);

      /* Detect board version */
      if (sp[1] == 0x42)
      {
        /* PRO Action Replay 1 (64/128K) */
        action_replay.enabled = TYPE_PRO1;

        /* internal registers mapped at $010000-$01ffff */
        m68k.memory_map[0x01].write16 = ar_write_regs;
      }
      else if (sp[1] == 0x60)
      {
        /* PRO Action Replay 2 (64K) */
        action_replay.enabled = TYPE_PRO2;

        /* internal registers mapped at $100000-$10ffff */
        m68k.memory_map[0x10].write16 = ar_write_regs_2;
      }

      /* internal RAM (64k), mapped at $420000-$42ffff or $600000-$60ffff */
      if (action_replay.enabled)
      {
        m68k.memory_map[sp[1]].base      = action_replay.ram;
        m68k.memory_map[sp[1]].read8     = NULL;
        m68k.memory_map[sp[1]].read16    = NULL;
        m68k.memory_map[sp[1]].write8    = ar_write_ram_8;
        m68k.memory_map[sp[1]].write16   = NULL;
      }
      break;
    }

    default:
    {
      break;
    }
  }

  if (action_replay.enabled)
  {
    /* Load ROM */
    int i = 0;
    for (i=0; i<size; i+=0x1000)
    {
      fread(action_replay.rom + i, 0x1000, 1, f);
    }

#ifdef LSB_FIRST
    for (i= 0; i<size; i+=2)
    {
      /* Byteswap ROM */
      uint8 temp = action_replay.rom[i];
      action_replay.rom[i] = action_replay.rom[i+1];
      action_replay.rom[i+1] = temp;
    }
#endif
  }

  /* Close ROM file */
  fclose(f);
}