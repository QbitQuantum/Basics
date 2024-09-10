public U8 *DBlk(I64 blk,Bool write=FALSE)
{//Dump Disk Blk.
//If you set write to TRUE, it will be written when you press <ESC>.
//See $LK-A,"::/TempleOS/Demo/Dsk/Raw.CPP"$.
  U8 *buf=MAlloc(BLK_SIZE);

  RBlks(Fs->cur_prt,buf,blk,1);
  DocD(buf,BLK_SIZE);
  if (write) {
    "Edit and press <ESC> to write or <SHIFT-ESC>\n";
    if (View) {
      "Write\n";
      WBlks(Fs->cur_prt,buf,blk,1);
    }
  }
  return buf;
}