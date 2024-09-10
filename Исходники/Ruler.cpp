int Ruler::pos2pix(const Pos& p) const
      {
      return lrint((p.time(_timeType)+480) * _xmag) + MAP_OFFSET - _xpos;
      }