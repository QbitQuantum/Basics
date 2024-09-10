/* Note that this also does the right thing for colored tiles. */
static int
win_ddb_tile_rectangle(gx_device * dev, const gx_tile_bitmap * tile,
      int x, int y, int w, int h, gx_color_index czero, gx_color_index cone,
		       int px, int py)
{
    fit_fill(dev, x, y, w, h);
    if (czero != gx_no_color_index && cone != gx_no_color_index) {
	fill_rect(x, y, w, h, czero);
	czero = gx_no_color_index;
    }
    if (tile->raster == bmWidthBytes && tile->size.y <= bmHeight &&
	(px | py) == 0 && cone != gx_no_color_index
	) {			/* We can do this much more efficiently */
	/* by using the internal algorithms of copy_mono */
	/* and gx_default_tile_rectangle. */
	int width = tile->size.x;
	int height = tile->size.y;
	int rwidth = tile->rep_width;
	int irx = ((rwidth & (rwidth - 1)) == 0 ?	/* power of 2 */
		   x & (rwidth - 1) :
		   x % rwidth);
	int ry = y % tile->rep_height;
	int icw = width - irx;
	int ch = height - ry;
	int ex = x + w, ey = y + h;
	int fex = ex - width, fey = ey - height;
	int cx, cy;

	select_brush((int)cone);

	if (tile->id != wdev->bm_id || tile->id == gx_no_bitmap_id) {
	    wdev->bm_id = tile->id;
	    SetBitmapBits(wdev->hbmmono,
			  (DWORD) (bmWidthBytes * tile->size.y),
			  (BYTE *) tile->data);
	}
#define copy_tile(srcx, srcy, tx, ty, tw, th)\
  BitBlt(wdev->hdcbit, tx, ty, tw, th, wdev->hdcmono, srcx, srcy, rop_write_at_1s)

	if (ch > h)
	    ch = h;
	for (cy = y;;) {
	    if (w <= icw)
		copy_tile(irx, ry, x, cy, w, ch);
	    else {
		copy_tile(irx, ry, x, cy, icw, ch);
		cx = x + icw;
		while (cx <= fex) {
		    copy_tile(0, ry, cx, cy, width, ch);
		    cx += width;
		}
		if (cx < ex) {
		    copy_tile(0, ry, cx, cy, ex - cx, ch);
		}
	    }
	    if ((cy += ch) >= ey)
		break;
	    ch = (cy > fey ? ey - cy : height);
	    ry = 0;
	}

	win_update((gx_device_win *) dev);
	return 0;
    }
    return gx_default_tile_rectangle(dev, tile, x, y, w, h, czero, cone, px, py);
}