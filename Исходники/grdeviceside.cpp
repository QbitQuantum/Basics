 void ide_device::polyline(int n, double *x, double *y, const pGEcontext gc) {
     auto dev = get_or_create_file_device();
     if (dev->polyline != nullptr) {
         dev->polyline(n, x, y, gc, dev);
     }
 }