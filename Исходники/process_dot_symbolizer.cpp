 void operator() (Adapter const& va)
 {
     double x,y,z = 0;
     unsigned cmd = SEG_END;
     va.rewind(0);
     while ((cmd = va.vertex(&x, &y)) != mapnik::SEG_END)
     {
         if (cmd == SEG_CLOSE) continue;
         prj_trans_.backward(x, y, z);
         common_.t_.forward(&x, &y);
         el_.init(x, y, rx_, ry_, el_.num_steps());
         ras_.add_path(el_);
         agg::render_scanlines(ras_, sl_, ren_);
     }
 }