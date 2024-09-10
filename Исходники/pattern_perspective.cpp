    virtual void on_draw()
    {
        pixfmt            pixf(rbuf_window());
        pixfmt_pre        pixf_pre(rbuf_window());
        renderer_base     rb(pixf);
        renderer_base_pre rb_pre(pixf_pre);

        if(!m_test_flag)
        {
            rb.clear(agg::rgba(1, 1, 1));
        }

        if(m_trans_type.cur_item() == 0)
        {
            // For the affine parallelogram transformations we
            // calculate the 4-th (implicit) point of the parallelogram
            m_quad.xn(3) = m_quad.xn(0) + (m_quad.xn(2) - m_quad.xn(1));
            m_quad.yn(3) = m_quad.yn(0) + (m_quad.yn(2) - m_quad.yn(1));
        }

        if(!m_test_flag)
        {
            //--------------------------
            // Render the "quad" tool and controls
            g_rasterizer.add_path(m_quad);
            agg::render_scanlines_aa_solid(g_rasterizer, g_scanline, rb, agg::rgba(0, 0.3, 0.5, 0.6));

            //--------------------------
            agg::render_ctrl(g_rasterizer, g_scanline, rb, m_trans_type);
        }

        // Prepare the polygon to rasterize. Here we need to fill
        // the destination (transformed) polygon.
        g_rasterizer.clip_box(0, 0, width(), height());
        g_rasterizer.reset();
        g_rasterizer.move_to_d(m_quad.xn(0), m_quad.yn(0));
        g_rasterizer.line_to_d(m_quad.xn(1), m_quad.yn(1));
        g_rasterizer.line_to_d(m_quad.xn(2), m_quad.yn(2));
        g_rasterizer.line_to_d(m_quad.xn(3), m_quad.yn(3));


        typedef agg::span_allocator<color_type> span_alloc_type;
        span_alloc_type sa;
        agg::image_filter<agg::image_filter_hanning> filter;
    
        typedef agg::wrap_mode_reflect_auto_pow2 remainder_type;
        typedef agg::image_accessor_wrap<pixfmt, 
                                         remainder_type, 
                                         remainder_type> img_source_type;

        pixfmt img_pixf(rbuf_img(0));
        img_source_type img_src(img_pixf);

        enum subdiv_shift_e { subdiv_shift = 2 };
         
        switch(m_trans_type.cur_item())
        {
            case 0:
            {
                // Note that we consruct an affine matrix that transforms
                // a parallelogram to a rectangle, i.e., it's inverted.
                // It's actually the same as:
                // tr(g_x1, g_y1, g_x2, g_y2, m_triangle.polygon());
                // tr.invert();
                agg::trans_affine tr(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);

                // Also note that we can use the linear interpolator instead of 
                // arbitrary span_interpolator_trans. It works much faster, 
                // but the transformations must be linear and parellel.
                typedef agg::span_interpolator_linear<agg::trans_affine> interpolator_type;
                interpolator_type interpolator(tr);

                typedef span_image_filter_2x2<img_source_type,
                                              interpolator_type> span_gen_type;
                span_gen_type sg(img_src, interpolator, filter);
                agg::render_scanlines_aa(g_rasterizer, g_scanline, rb_pre, sa, sg);
                break;
            }

            case 1:
            {
                agg::trans_bilinear tr(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);
                if(tr.is_valid())
                {
                    typedef agg::span_interpolator_linear<agg::trans_bilinear> interpolator_type;
                    interpolator_type interpolator(tr);

                    typedef span_image_filter_2x2<img_source_type,
                                                  interpolator_type> span_gen_type;
                    span_gen_type sg(img_src, interpolator, filter);
                    agg::render_scanlines_aa(g_rasterizer, g_scanline, rb_pre, sa, sg);
                }
                break;
            }

            case 2:
            {
                agg::trans_perspective tr(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);
                if(tr.is_valid())
                {
                    typedef agg::span_interpolator_linear_subdiv<agg::trans_perspective, 8> interpolator_type;
                    interpolator_type interpolator(tr);

                    typedef span_image_filter_2x2<img_source_type,
                                                  interpolator_type> span_gen_type;
                    span_gen_type sg(img_src, interpolator, filter);
                    agg::render_scanlines_aa(g_rasterizer, g_scanline, rb_pre, sa, sg);
                }
                break;
            }
        }
    }