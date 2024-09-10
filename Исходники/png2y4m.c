int alphasort(const void *_a, const void *_b){
  return strcoll((*(const struct dirent **)_a)->d_name,
   (*(const struct dirent **)_b)->d_name);
}