void Xim2col<T>::DoIm2col(const size_t channels, const size_t height, const size_t width,
                          const size_t kernel_h, const size_t kernel_w, const size_t pad_h,
                          const size_t pad_w, const size_t stride_h, const size_t stride_w,
                          const size_t dilation_h, const size_t dilation_w,
                          const Buffer<T> &im_buffer, const size_t im_offset,
                          const Buffer<T> &col_buffer, const size_t col_offset) {

  // Makes sure all dimensions are larger than zero
  if ((channels == 0) || (height == 0) || (width == 0)) { throw BLASError(StatusCode::kInvalidDimension); }

  // Sets the output height and width
  const auto size_h = height + 2 * pad_h;
  const auto padding_h = dilation_h * (kernel_h - 1) + 1;
  const auto output_h = (size_h >= padding_h) ? (size_h - padding_h) / stride_h + 1 : 1;
  const auto size_w = width + 2 * pad_w;
  const auto padding_w = dilation_w * (kernel_w - 1) + 1;
  const auto output_w = (size_w >= padding_w) ? (size_w - padding_w) / stride_w + 1 : 1;

  // Retrieves the Xcopy kernel from the compiled binary
  auto kernel = Kernel(program_, "im2col");

  // Sets the kernel arguments
  kernel.SetArgument(0, static_cast<int>(height));
  kernel.SetArgument(1, static_cast<int>(width));
  kernel.SetArgument(2, static_cast<int>(channels));
  kernel.SetArgument(3, static_cast<int>(output_h));
  kernel.SetArgument(4, static_cast<int>(output_w));
  kernel.SetArgument(5, static_cast<int>(kernel_h));
  kernel.SetArgument(6, static_cast<int>(kernel_w));
  kernel.SetArgument(7, static_cast<int>(pad_h));
  kernel.SetArgument(8, static_cast<int>(pad_w));
  kernel.SetArgument(9, static_cast<int>(stride_h));
  kernel.SetArgument(10, static_cast<int>(stride_w));
  kernel.SetArgument(11, static_cast<int>(dilation_h));
  kernel.SetArgument(12, static_cast<int>(dilation_w));
  kernel.SetArgument(13, im_buffer());
  kernel.SetArgument(14, static_cast<int>(im_offset));
  kernel.SetArgument(15, col_buffer());
  kernel.SetArgument(16, static_cast<int>(col_offset));

  // Launches the kernel
  const auto w_ceiled = Ceil(output_w, db_["COPY_DIMX"]);
  const auto h_ceiled = Ceil(output_h, db_["COPY_DIMY"]);
  const auto global = std::vector<size_t>{w_ceiled, h_ceiled * channels};
  const auto local = std::vector<size_t>{db_["COPY_DIMX"], db_["COPY_DIMY"]};
  RunKernel(kernel, queue_, device_, global, local, event_);
}