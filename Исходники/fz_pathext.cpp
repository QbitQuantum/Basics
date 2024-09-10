extern "C" void pathext_stroke_path(fz_device *dev, fz_path *path,
                                    fz_stroke_state *, const fz_matrix *ctm,
                                    fz_colorspace *, float *, float)
{
  PathExt *ext = static_cast<PathExt*>(dev->user);
  if( ext == 0 ) {
    return;
  }

  QPainterPath qPath;
  float *c = path->coords;
  for(int i = 0; i < path->cmd_len; i++) {
    if(        path->cmds[i] == FZ_MOVETO ) {
      qPath.moveTo(c[0], c[1]);
      c += 2;
    } else if( path->cmds[i] == FZ_LINETO ) {
      qPath.lineTo(c[0], c[1]);
      c += 2;
    } else if( path->cmds[i] == FZ_CURVETO ) {
      qPath.cubicTo(c[0], c[1], c[2], c[3], c[4], c[5]);
      c += 6;
    } else if( path->cmds[i] == FZ_CLOSE_PATH ) {
      if( !ext->closed ) {
        return;
      }
      qPath.closeSubpath();
    } else {
      return;
    }
  }

  const QTransform qCtm = toTransform(ctm);
  qPath = qCtm.map(qPath);

  ext->paths.push_back(qPath);
}