/*--------------------------------------------------------------------------*/ 
SCICOS_BLOCKS_IMPEXP void asinh_blk(scicos_block *block,int flag)
{
  int j = 0;
  if(flag==1){
    for (j=0;j<block->insz[0];j++) {
      block->outptr[0][j]=asinh(block->inptr[0][j]);
    }
  }
}