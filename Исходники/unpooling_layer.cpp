void UnpoolingLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
  if (!propagate_down[0]) {
    return;
  }
  const Dtype* top_diff = top[0]->cpu_diff();
  Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();
  // Different unpooling methods. We explicitly do the switch outside the for
  // loop to save time, although this results in more codes.
  caffe_set(bottom[0]->count(), Dtype(0), bottom_diff);
  // We'll output the mask to top[1] if it's of size >1.
  const bool use_bottom_mask = bottom.size() > 1;
  const Dtype* bottom_mask = NULL;
  switch (this->layer_param_.unpooling_param().unpool()) {
  case UnpoolingParameter_UnpoolMethod_MAX:
    if (use_bottom_mask) {
      bottom_mask = bottom[1]->cpu_data();
    } 
    // The main loop
    for (int n = 0; n < top[0]->num(); ++n) {
      for (int c = 0; c < channels_; ++c) {
        for (int ph = 0; ph < height_; ++ph) {
          for (int pw = 0; pw < width_; ++pw) {
            int uph = max(0,min(ph * stride_h_ - pad_h_, unpooled_height_-1));
            int upw = max(0,min(pw * stride_w_ - pad_w_, unpooled_width_-1)); 
            const int index = ph * width_ + pw;
            const int unpooled_index = uph * unpooled_width_ + upw; 
            if (use_bottom_mask) {
              const int mask_index = bottom_mask[index];
              bottom_diff[index] = top_diff[mask_index]; 
            } else {
              bottom_diff[index] = top_diff[unpooled_index];
            }
          }
        }
        // compute offset
        bottom_diff += bottom[0]->offset(0, 1);
        top_diff += top[0]->offset(0, 1);
        if (use_bottom_mask) {
          bottom_mask += bottom[1]->offset(0, 1);
        } 
      }
    }
    break;
  case UnpoolingParameter_UnpoolMethod_AVE:
    for (int i = 0; i < bottom[0]->count(); ++i) {
      bottom_diff[i] = 0;
    }
    // The main loop
    for (int n = 0; n < bottom[0]->num(); ++n) {
      for (int c = 0; c < channels_; ++c) {
        for (int ph = 0; ph < height_; ++ph) {
          for (int pw = 0; pw < width_; ++pw) {
            int hstart = ph * stride_h_ - pad_h_;
            int wstart = pw * stride_w_ - pad_w_;
            int hend = min(hstart + kernel_h_, unpooled_height_ + pad_h_);
            int wend = min(wstart + kernel_w_, unpooled_width_ + pad_w_);
            int pool_size = (hend - hstart) * (wend - wstart);
            hstart = max(hstart, 0);
            wstart = max(wstart, 0);
            hend = min(hend, unpooled_height_);
            wend = min(wend, unpooled_width_);
            for (int h = hstart; h < hend; ++h) {
              for (int w = wstart; w < wend; ++w) {
                bottom_diff[ph * width_ + pw] +=
                    top_diff[h * unpooled_width_ + w];
              }
            }
            bottom_diff[ph * width_ + pw] /= pool_size;
          }
        }
        // compute offset
        bottom_diff += bottom[0]->offset(0, 1);
        top_diff += top[0]->offset(0, 1);
      }
    }
    break;
  case UnpoolingParameter_UnpoolMethod_TILE:
    for (int i = 0; i < bottom[0]->count(); ++i) {
      bottom_diff[i] = 0;
    }
    // The main loop
    for (int n = 0; n < bottom[0]->num(); ++n) {
      for (int c = 0; c < channels_; ++c) {
        for (int ph = 0; ph < height_; ++ph) {
          for (int pw = 0; pw < width_; ++pw) {
            int hstart = ph * stride_h_ - pad_h_;
            int wstart = pw * stride_w_ - pad_w_;
            int hend = min(hstart + kernel_h_, unpooled_height_ + pad_h_);
            int wend = min(wstart + kernel_w_, unpooled_width_ + pad_w_);
            int pool_size = (hend - hstart) * (wend - wstart);
            hstart = max(hstart, 0);
            wstart = max(wstart, 0);
            hend = min(hend, unpooled_height_);
            wend = min(wend, unpooled_width_);
            for (int h = hstart; h < hend; ++h) {
              for (int w = wstart; w < wend; ++w) {
                bottom_diff[ph * width_ + pw] +=
                    top_diff[h * unpooled_width_ + w];
              }
            }
            bottom_diff[ph * width_ + pw] /= pool_size;
          }
        }
        // compute offset
        bottom_diff += bottom[0]->offset(0, 1);
        top_diff += top[0]->offset(0, 1);
      }
    }
    break;
  default:
    LOG(FATAL) << "Unknown unpooling method.";
  }
}