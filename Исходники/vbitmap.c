/* Methods */
int
VbitmapResize(Vbitmap *vbitmap, int width, int height)
{
  if (vbitmap == NULL) {
    return YMAGINE_ERROR;
  }

  if (width <= 0 || height <= 0) {
    return YMAGINE_ERROR;
  }

  if (width == vbitmap->width && height == vbitmap->height) {
    /* Size not changed, ignore */
    return YMAGINE_OK;
  }

  if (vbitmap->bitmaptype == VBITMAP_NONE) {
    vbitmap->width = width;
    vbitmap->height = height;

    return YMAGINE_OK;
  }

  if (vbitmap->bitmaptype == VBITMAP_ANDROID) {
    AndroidBitmapInfo bitmapinfo;
    jobject jbitmap;
    jobject jbitmapref;
    int ret;

    JNIEnv *jenv = getEnv(vbitmap);
    if (jenv == NULL) {
      return YMAGINE_ERROR;
    }

    jbitmap = createAndroidBitmap(jenv, width, height);
    if (jbitmap == NULL) {
      return YMAGINE_ERROR;
    }

    ret = AndroidBitmap_getInfo(jenv, jbitmap, &bitmapinfo);
    if (ret < 0 ||
        bitmapinfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888 ||
        bitmapinfo.width != width || bitmapinfo.height != height) {
      return YMAGINE_ERROR;
    }

    jbitmapref = (*jenv)->NewGlobalRef(jenv, jbitmap);
    if (jbitmapref == NULL) {
      return YMAGINE_ERROR;
    }

    /* Replace Bitmap */
    if (vbitmap->jbitmap != NULL) {
      if (vbitmap->jkeepref) {
        (*jenv)->DeleteGlobalRef(jenv, vbitmap->jbitmap);
        vbitmap->jkeepref = 0;
      }
      vbitmap->jbitmap = NULL;
    }

#if VBITMAP_ENABLE_GLOBAL_REF
      vbitmap->jbitmap = jbitmapref;
      vbitmap->jkeepref = 1;
#else
      vbitmap->jbitmap = jbitmap;
      vbitmap->jkeepref = 0;
      (*jenv)->DeleteGlobalRef(jenv, jbitmapref);
#endif

    vbitmap->width = bitmapinfo.width;
    vbitmap->height = bitmapinfo.height;
    vbitmap->pitch = bitmapinfo.stride;

    return YMAGINE_OK;
  }

  if (vbitmap->bitmaptype == VBITMAP_MEMORY) {
    int bpp = colorBpp(VbitmapColormode(vbitmap));
    int pitch = width * bpp;
    unsigned char *pixels = NULL;

    if (pitch > 0) {
      pixels = Ymem_malloc(pitch * height);
    }
    if (pixels == NULL) {
      return YMAGINE_ERROR;
    }

    if (vbitmap->pixels != NULL) {
      Ymem_free(vbitmap->pixels);
    }

    vbitmap->pixels = pixels;
    vbitmap->width = width;
    vbitmap->height = height;
    vbitmap->pitch = pitch;

    return YMAGINE_OK;
  }

  if (vbitmap->bitmaptype == VBITMAP_STATIC) {
    /* Can't resize a static bitmap */
    return YMAGINE_ERROR;
  }

  return YMAGINE_ERROR;
}