 void operator() (Adapter const& va) const
 {
     double label_x, label_y, z = 0;
     va.rewind(0);
     for (unsigned cmd; (cmd = va.vertex(&label_x, &label_y)) != SEG_END; )
     {
         if (cmd != SEG_CLOSE)
         {
             prj_trans_.backward(label_x, label_y, z);
             tr_.forward(&label_x, &label_y);
             points_.emplace_back(label_x, label_y);
         }
     }
 }