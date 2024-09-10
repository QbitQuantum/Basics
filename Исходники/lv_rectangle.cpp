  Rect Rect::clip (Rect const& bounds, Rect const& r)
  {
      // Return an empty rectangle
      if (!bounds.intersects (r)) {
          return Rect ();
      }

      Rect result (r);

      // Left, Upper boundries
      if (r.x < bounds.x) {
          result.width = r.width - (bounds.x - r.x);
          result.x = bounds.x;
      }

      if (r.y < bounds.y) {
          result.height = r.height - (bounds.y - r.y);
          result.y = bounds.y;
      }

      // Right, Lower boundries
      if (result.x + result.width > bounds.width)
          result.width = bounds.width - result.x;

      if (result.y + result.height > bounds.height)
          result.height = bounds.height - result.y;

      return result;
  }