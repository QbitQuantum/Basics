void roadmap_canvas_native_draw_multiple_lines (int count, int *lines,
				RoadMapGuiPoint *points, int r, int g, int b, int thickness)
{
	int i;
	int count_of_points;

	POINT winpoints[1024];

   static int init;

   select_native_color (RGB(r, g, b), thickness);

	for (i = 0; i < count; ++i) {

      RoadMapGuiPoint end_points[2];
      int first = 1;
		
		count_of_points = *lines;
		
      if (count_of_points < 2) continue;

		while (count_of_points > 1024) {

         if (first) {
            first = 0;
            end_points[0] = *points;
         }
			roadmap_canvas_convert_points (winpoints, points, 1024);
			Polyline(RoadMapDrawingBuffer, winpoints, 1024);
			/* We shift by 1023 only, because we must link the lines. */
			points += 1023;
			count_of_points -= 1023;
		}

      if (first) {
         first = 0;
         end_points[0] = *points;
      }

      end_points[1] = points[count_of_points - 1];
		roadmap_canvas_convert_points (winpoints, points, count_of_points);
		Polyline(RoadMapDrawingBuffer, winpoints, count_of_points);

#if 0
      if (CurrentPen->thinkness > 5) {

         HPEN oldPen = SelectObject(RoadMapDrawingBuffer,
            GetStockObject(NULL_PEN));

         int radius = CurrentPen->thinkness / 2;

         Ellipse(RoadMapDrawingBuffer,
			   end_points[0].x - radius, end_points[0].y - radius,
			   radius + end_points[0].x + 1,
			   radius + end_points[0].y + 1);

         Ellipse(RoadMapDrawingBuffer,
			   end_points[1].x - radius, end_points[1].y - radius,
			   radius + end_points[1].x + 1,
			   radius + end_points[1].y + 1);

         SelectObject(RoadMapDrawingBuffer, oldPen);
	   }
#endif

		points += count_of_points;
		lines += 1;
	}

//   DeleteObject(SelectObject(RoadMapDrawingBuffer, oldPen));
//   DeleteObject(SelectObject(RoadMapDrawingBuffer, oldBrush));
}