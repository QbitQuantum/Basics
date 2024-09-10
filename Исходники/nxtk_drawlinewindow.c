int nxtk_drawlinewindow(NXTKWINDOW hfwnd, FAR struct nxgl_vector_s *vector,
                        nxgl_coord_t width, nxgl_mxpixel_t color[CONFIG_NX_NPLANES],
                        uint8_t caps)
{
  struct nxgl_trapezoid_s trap[3];
  struct nxgl_rect_s rect;
  int ret;

#ifdef CONFIG_DEBUG
  if (!hfwnd || !vector || width < 1 || !color)
    {
      set_errno(EINVAL);
      return ERROR;
    }
#endif

  /* Split the line into trapezoids */

  ret = nxgl_splitline(vector, trap, &rect, width);
  switch (ret)
    {
      /* 0: Line successfully broken up into three trapezoids.  Values in
       *    traps[0], traps[1], and traps[2] are valid.
       */

      case 0:
        ret = nxtk_filltrapwindow(hfwnd, &trap[0], color);
        if (ret == OK)
          {
            ret = nxtk_filltrapwindow(hfwnd, &trap[1], color);
            if (ret == OK)
              {
                ret = nxtk_filltrapwindow(hfwnd, &trap[2], color);
              }
          }
        break;

      /* 1: Line successfully represented by one trapezoid. Value in traps[1]
       *    is valid.
       */

      case 1:
        ret = nxtk_filltrapwindow(hfwnd, &trap[1], color);
         break;

      /* 2: Line successfully represented by one rectangle. Value in rect is
       *    valid
       */

       case 2:
         ret = nxtk_fillwindow(hfwnd, &rect, color);
         break;

      /* <0: On errors, a negated errno value is returned. */

      default:
         set_errno(EINVAL);
         return ERROR;
    }

  /* Draw circular caps at each end of the line to support better line joins */

  if (caps != NX_LINECAP_NONE && width >= 3)
    {
      nxgl_coord_t radius = width >> 1;

      /* Draw a circle at pt1 */

      ret = OK;
      if ((caps & NX_LINECAP_PT1) != 0)
        {
          ret = nxtk_fillcirclewindow(hfwnd, &vector->pt1, radius, color);
        }

      /* Draw a circle at pt2 */

      if (ret == OK && (caps & NX_LINECAP_PT2) != 0)
        {
          ret = nxtk_fillcirclewindow(hfwnd, &vector->pt2, radius, color);
        }
    }