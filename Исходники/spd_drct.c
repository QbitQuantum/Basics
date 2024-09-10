static int drct_make_rmw_sg(spd_dev_t *dev)
{
  spd_scatterlist_t *sg = dev->sg;
  struct bio *bio = dev->bdev->rmw_bio;
  int n,i;
  int len1, len2, len3;
  u8  *virt_addr;
  u32 b_size, size, offset, b_offset;
  u32 c_size;
  PTRACE();

  PINFO("<spd%c>cache_sector=%08x, rmw_sector=%08x, rmw_count=%04x",
        dev->id+'a',
	dev->cache->sector, 
        dev->bdev->rmw_sector,
        dev->bdev->rmw_count);

  PCOMMAND("<spd%c>USE_CACHE id=%02d, cache_sector=%08x, rmw_sector=%08x, rmw_count=%04x",
           dev->id+'a',
           dev->cache->id,
           dev->cache->sector,
           dev->bdev->rmw_sector,
           dev->bdev->rmw_count);

  n = 0;
  len1 = (dev->bdev->rmw_sector - dev->cache->sector);
  if(len1 + dev->bdev->rmw_count > dev->cache->n_sector){
    len2 = dev->cache->n_sector - len1;
    len3 = 0;

    dev->bdev->rmw_count -= len2;
    dev->bdev->rmw_sector = dev->cache->sector+dev->cache->n_sector;
  } else {
    len2 = dev->bdev->rmw_count;
    len3 = dev->cache->n_sector -len2 - len1;

    dev->bdev->rmw_count  = 0;
    dev->bdev->rmw_sector = (u32)-1;
  };

  PINFO("<spd%c>len1=%d, len2=%d, len3=%d", dev->id+'a', len1, len2, len3);

  c_size = dev->cache->n_sector*SPD_HARDSECT_SIZE;
  if(c_size > SPD_CACHE_BUFFER_SIZE){
    c_size = SPD_CACHE_BUFFER_SIZE;
  }

  if (len1 > 0){
    i = 0;
    size = len1*SPD_HARDSECT_SIZE;
    while(size > 0){
      virt_addr = dev->cache->buffer[i++];
      b_size    = (size<c_size?size:c_size);
      n = set_sg_entry(sg, n, virt_to_bus(virt_addr), b_size);
      if(unlikely(n < 0)){
        PERROR("<spd%c>set_sg_entry() failed(%d)", dev->id+'a', n);
        return n;
      }
      size -= b_size;
    }
  }

  if(len2 > 0){
    size = len2*SPD_HARDSECT_SIZE;
    bio  = dev->bdev->rmw_bio;

    while(size > 0){
      b_size = bio->bi_size - dev->bdev->rmw_bio_offset;

      PINFO("b_size=%lx size=%lx maxvec=%d",
	    (unsigned long)b_size, (unsigned long)size, bio->bi_max_vecs);

      if(b_size > size){
	PINFO("==");
	n = drct_set_sg_entry(dev, n, bio, size);
	dev->bdev->rmw_bio_offset += size;
        break;
      }
      n = drct_set_sg_entry(dev, n, bio, b_size);
      if(unlikely(n < 0)){
        PERROR("<spd%c>drct_set_sg_entry() failed(%d)",dev->id+'a', n);
        return n;
      }
      size -= b_size;
      bio   = bio->bi_next;
      dev->bdev->rmw_bio         = bio;
      dev->bdev->rmw_bio_offset  = 0;
      dev->bdev->rmw_bvec_offset = 0;
      dev->bdev->rmw_bio_idx     = bio ? bio->bi_idx : 0;
    }
  }

  if (len3 > 0){
    size   = len3*SPD_HARDSECT_SIZE;
    offset = (len1+len2)*SPD_HARDSECT_SIZE;

    b_offset = offset%c_size;
    b_size   = c_size - b_offset;
    i        = offset/c_size;

    virt_addr = dev->cache->buffer[i++] + b_offset;
    n = set_sg_entry(sg, n, virt_to_bus(virt_addr), b_size);
    if(unlikely(n < 0)){
      PERROR("<spd%c>set_sg_entry() failed(%d)",dev->id+'a', n);
      return n;
    }
    size -= b_size;

    while(size > 0){
      virt_addr = dev->cache->buffer[i++];
      n = set_sg_entry(sg, n, virt_to_bus(virt_addr), c_size);
      if(unlikely(n < 0)){
        PERROR("<spd%c>set_sg_entry() failed(%d)",dev->id+'a', n);
        return n;
      }
      size -= c_size;
    }
  }

  sg[n-1].count |= cpu_to_le32(SPD_SG_ENDMARK);
  dev->sg_n_entry = n;
  spd_dma_cache_wback(dev->dev, sg, sizeof(spd_scatterlist_t)*n);

  PRINT_SG(sg, n, dev->id);

  return 0;
}