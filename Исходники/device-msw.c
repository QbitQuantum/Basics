static void
msprinter_delete_device_internal (struct device *d)
{
  if (DEVICE_MSPRINTER_HPRINTER (d))
    ClosePrinter (DEVICE_MSPRINTER_HPRINTER (d));
  if (DEVICE_MSPRINTER_HDC (d))
    DeleteDC (DEVICE_MSPRINTER_HDC (d));
  if (DEVICE_MSPRINTER_HCDC (d))
    DeleteDC (DEVICE_MSPRINTER_HCDC (d));

  DEVICE_MSPRINTER_FONTLIST (d) = Qnil;
}