static void
float_reply (rr_dev dev, char **i, rr_reply type)
{
  if (dev->reply_cb)
    dev->reply_cb (dev, type, strtof (*i + 2, i), NULL, dev->reply_cl);
}