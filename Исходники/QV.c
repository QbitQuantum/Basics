static HScheme *Huffman(uint64 *hist, HScheme *inscheme)
{ HScheme *scheme;
  HTree   *heap[257];
  HTree    node[512];
  int      hsize;
  HTree   *lft, *rgt;
  int      value, range;
  int     i;

  scheme = (HScheme *) Malloc(sizeof(HScheme),"Allocating Huffman scheme record");
  if (scheme == NULL)
    exit (1);

  hsize = 0;                        //  Load heap
  value = 0;
  if (inscheme != NULL)
    { node[0].count = 0;
      node[0].lft   = (HTree *) (uint64) 255;
      node[0].rgt   = NULL;
      heap[++hsize] = node+(value++);
    }
  for (i = 0; i < 256; i++)
    if (hist[i] > 0)
      { if (inscheme != NULL && (inscheme->codelens[i] > HUFF_CUTOFF || i == 255))
          node[0].count += hist[i];
        else
          { node[value].count = hist[i];
            node[value].lft   = (HTree *) (uint64) i;
            node[value].rgt   = NULL;
            heap[++hsize] = node+(value++);
          }
      }

  for (i = hsize/2; i >= 1; i--)    //  Establish heap property
    Reheap(i,heap,hsize);

  range = value;                    //   Merge pairs with smallest count until have a tree
  for (i = 1; i < value; i++)
    { lft = heap[1];
      heap[1] = heap[hsize--];
      Reheap(1,heap,hsize);
      rgt = heap[1];
      node[range].lft = lft;
      node[range].rgt = rgt;
      node[range].count = lft->count + rgt->count;
      heap[1] = node+(range++);
      Reheap(1,heap,hsize);
    }

  for (i = 0; i < 256; i++)        //  Build the code table
    { scheme->codebits[i] = 0;
      scheme->codelens[i] = 0;
    }

  Build_Table(node+(range-1),0,0,scheme->codebits,scheme->codelens);

  if (inscheme != NULL)            //  Set scheme type and if truncated (2), map truncated codes
    { scheme->type = 2;            //    to code and length for 255
      for (i = 0; i < 255; i++)
        if (inscheme->codelens[i] > HUFF_CUTOFF || scheme->codelens[i] > HUFF_CUTOFF)
          { scheme->codelens[i] = scheme->codelens[255];
            scheme->codebits[i] = scheme->codebits[255];
          }
    }
  else
    { scheme->type = 0;
      for (i = 0; i < 256; i++)
        { if (scheme->codelens[i] > HUFF_CUTOFF)
            scheme->type = 1;
        }
    }

  return (scheme);
}