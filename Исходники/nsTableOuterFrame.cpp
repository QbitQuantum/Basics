// caption frame
nsTableCaptionFrame::nsTableCaptionFrame(nsStyleContext* aContext):
  nsBlockFrame(aContext)
{
  // shrink wrap 
  SetFlags(NS_BLOCK_FLOAT_MGR);
}