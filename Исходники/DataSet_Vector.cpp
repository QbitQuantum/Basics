// DataSet_Vector::WriteBuffer()
void DataSet_Vector::WriteBuffer(CpptrajFile &cbuffer, SizeArray const& pIn) const {
  if (pIn[0] >= vectors_.size()) {
    cbuffer.Printf(format_.fmt(), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); // VXYZ OXYZ
  } else {
    Vec3 const& Vxyz = vectors_[pIn[0]];
    Vec3 const& Oxyz = OXYZ(pIn[0]);
    cbuffer.Printf(format_.fmt(), Vxyz[0], Vxyz[1], Vxyz[2],
                                  Oxyz[0], Oxyz[1], Oxyz[2]);
  }
}