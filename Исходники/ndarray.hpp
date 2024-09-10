inline NDArray::NDArray(const std::vector<mx_float> &data, const Shape &shape,
                        const Context &context) {
  NDArrayHandle handle;
  CHECK_EQ(MXNDArrayCreate(shape.data(), shape.ndim(), context.GetDeviceType(),
                           context.GetDeviceId(), false, &handle),
           0);
  MXNDArraySyncCopyFromCPU(handle, data.data(), shape.Size());
  blob_ptr_ = std::make_shared<NDBlob>(handle);
}