/* Initialize a block */
static void init_block(block_t *p_block, uint8_t type)
{
  p_block->type = type;

  /* Set the number of hits for the block (ignore the special-flag) */
  switch(p_block->type & (0xff ^ TYPE_SPECIAL))
    {
    case TYPE_SIMPLE:
      p_block->hits = 1;
      break;
    case TYPE_HARD:
      p_block->hits = 2;
      break;
    case TYPE_IMPOSSIBLE:
      p_block->hits = 255;
      break;
    }

  if (p_block->type & TYPE_SPECIAL)
    {
      /* This block has a random special, 1/4 can be bad specials, 5/6 are only good.
       * 1/6 of the "only goods" can be very good (extra life, "destroyer" balls etc)
       */
      if (rand_nr & 1)
	p_block->special = 1<<(SRAND()%(SPECIAL_MAX-4)); /* Good specials */
      else
	p_block->special = 1<<(SRAND()%SPECIAL_MAX); /* Can be very good and bad specials */
      DEBUG(printf("Init special %d\n", p_block->special));
    }
}