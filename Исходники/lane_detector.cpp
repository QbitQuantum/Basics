//void processLanes(CvSeq *lines, IplImage* edges, IplImage *temp_frame)
static void processLanes(CvSeq *lines, IplImage* edges, IplImage *temp_frame, IplImage *org_frame)
{
  /* classify lines to left/right side */
  std::vector<Lane> left, right;

  for (int i=0; i<lines->total; i++)
    {
      CvPoint *line = (CvPoint *)cvGetSeqElem(lines, i);
      int dx = line[1].x - line[0].x;
      int dy = line[1].y - line[0].y;
      float angle = atan2f(dy, dx) * 180/CV_PI;

      if (fabs(angle) <= LINE_REJECT_DEGREES) // reject near horizontal lines
        {
          continue;
        }

      /* assume that vanishing point is close to the image horizontal center
         calculate line parameters: y = kx + b; */
      dx = (dx == 0) ? 1 : dx;  // prevent DIV/0!
      float k = dy/(float)dx;
      float b = line[0].y - k*line[0].x;

      /* assign lane's side based by its midpoint position */
      int midx = (line[0].x + line[1].x) / 2;
      if (midx < temp_frame->width/2)
        {
          left.push_back(Lane(line[0], line[1], angle, k, b));
        }
      else if (midx > temp_frame->width/2)
        {
          right.push_back(Lane(line[0], line[1], angle, k, b));
        }
    }

  /* show Hough lines */
  int org_offset = temp_frame->height;
  for (std::size_t i = 0; i < right.size(); ++i)
    {
      CvPoint org_p0 = right[i].p0;
      org_p0.y += org_offset;
      CvPoint org_p1 = right[i].p1;
      org_p1.y += org_offset;
#ifdef USE_POSIX_SHARED_MEMORY
#ifdef SHOW_DETAIL
      cvLine(temp_frame, right[i].p0, right[i].p1, BLUE, 2);
#endif
      cvLine(org_frame, org_p0, org_p1, BLUE, 2);
#endif
    }
  for (std::size_t i = 0; i < left.size(); ++i)
    {
      CvPoint org_p0 = left[i].p0;
      org_p0.y += org_offset;
      CvPoint org_p1 = left[i].p1;
      org_p1.y += org_offset;
#ifdef USE_POSIX_SHARED_MEMORY
#ifdef SHOW_DETAIL
      cvLine(temp_frame, left[i].p0, left[i].p1, RED, 2);
#endif
      cvLine(org_frame, org_p0, org_p1, RED, 2);
#endif
    }

  processSide(left, edges, false);
  processSide(right, edges, true);

  /* show computed lanes */
  int x = temp_frame->width * 0.55f;
  int x2 = temp_frame->width;
#if defined(USE_POSIX_SHARED_MEMORY)
#ifdef SHOW_DETAIL
  cvLine(temp_frame, cvPoint(x, laneR.k.get()*x + laneR.b.get()),
         cvPoint(x2, laneR.k.get()*x2 + laneR.b.get()), PURPLE, 2);
#endif

  cvLine(org_frame, cvPoint(x, laneR.k.get()*x + laneR.b.get() + org_offset),
         cvPoint(x2, laneR.k.get()*x2 + laneR.b.get() + org_offset), PURPLE, 2);
#else
  lane_detector::ImageLaneObjects lane_msg;
  lane_msg.lane_r_x1 = x;
  lane_msg.lane_r_y1 = laneR.k.get()*x + laneR.b.get() + org_offset;
  lane_msg.lane_r_x2 = x2;
  lane_msg.lane_r_y2 = laneR.k.get()*x2 + laneR.b.get() + org_offset;
#endif

  x = temp_frame->width * 0;
  x2 = temp_frame->width * 0.45f;
#if defined(USE_POSIX_SHARED_MEMORY)
#ifdef SHOW_DETAIL
  cvLine(temp_frame, cvPoint(x, laneL.k.get()*x + laneL.b.get()),
         cvPoint(x2, laneL.k.get()*x2 + laneL.b.get()), PURPLE, 2);
#endif

  cvLine(org_frame, cvPoint(x, laneL.k.get()*x + laneL.b.get() + org_offset),
         cvPoint(x2, laneL.k.get()*x2 + laneL.b.get() + org_offset), PURPLE, 2);
#else
  lane_msg.lane_l_x1 = x;
  lane_msg.lane_l_y1 = laneL.k.get()*x + laneL.b.get() + org_offset;
  lane_msg.lane_l_x2 = x2;
  lane_msg.lane_l_y2 = laneL.k.get()*x2 + laneL.b.get() + org_offset;

  image_lane_objects.publish(lane_msg);
#endif
  // cvLine(org_frame, cvPoint(lane_msg.lane_l_x1, lane_msg.lane_l_y1), cvPoint(lane_msg.lane_l_x2, lane_msg.lane_l_y2), RED, 5);
  // cvLine(org_frame, cvPoint(lane_msg.lane_r_x1, lane_msg.lane_r_y1), cvPoint(lane_msg.lane_r_x2, lane_msg.lane_r_y2), RED, 5);
}