/** Write data at frame to CharBuffer. If no data for frame write 0.0.
  */
void DataSet_double::WriteBuffer(CpptrajFile &cbuffer, SizeArray const& frame) const {
  if (frame[0] >= Data_.size())
    cbuffer.Printf(format_.fmt(), 0.0);
  else
    cbuffer.Printf(format_.fmt(), Data_[frame[0]]);
}