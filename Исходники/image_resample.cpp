    virtual void on_draw()
    {
        if(m_gamma.value() != m_old_gamma)
        {
            m_gamma_lut.gamma(m_gamma.value());
            load_img(0, "spheres");
            pixfmt pixf(rbuf_img(0));
            pixf.apply_gamma_dir(m_gamma_lut);
            m_old_gamma = m_gamma.value();
        }

        pixfmt            pixf(rbuf_window());
        pixfmt_pre        pixf_pre(rbuf_window());
        renderer_base     rb(pixf);
        renderer_base_pre rb_pre(pixf_pre);

        renderer_solid r(rb);

        rb.clear(agg::rgba(1, 1, 1));

        if(m_trans_type.cur_item() < 2)
        {
            // For the affine parallelogram transformations we
            // calculate the 4-th (implicit) point of the parallelogram
            m_quad.xn(3) = m_quad.xn(0) + (m_quad.xn(2) - m_quad.xn(1));
            m_quad.yn(3) = m_quad.yn(0) + (m_quad.yn(2) - m_quad.yn(1));
        }

        //--------------------------
        // Render the "quad" tool and controls
        g_rasterizer.add_path(m_quad);
        r.color(agg::rgba(0, 0.3, 0.5, 0.1));
        agg::render_scanlines(g_rasterizer, g_scanline, r);

        // Prepare the polygon to rasterize. Here we need to fill
        // the destination (transformed) polygon.
        g_rasterizer.clip_box(0, 0, width(), height());
        g_rasterizer.reset();
        int b = 0;
        g_rasterizer.move_to_d(m_quad.xn(0)-b, m_quad.yn(0)-b);
        g_rasterizer.line_to_d(m_quad.xn(1)+b, m_quad.yn(1)-b);
        g_rasterizer.line_to_d(m_quad.xn(2)+b, m_quad.yn(2)+b);
        g_rasterizer.line_to_d(m_quad.xn(3)-b, m_quad.yn(3)+b);

        typedef agg::span_allocator<color_type> span_alloc_type;
        span_alloc_type sa;
        agg::image_filter_bilinear filter_kernel;
        agg::image_filter_lut filter(filter_kernel, true);

        pixfmt pixf_img(rbuf_img(0));
        typedef agg::image_accessor_clone<pixfmt> source_type;
        source_type source(pixf_img);

        start_timer();
        switch(m_trans_type.cur_item())
        {
            case 0:
            {
                agg::trans_affine tr(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);

                typedef agg::span_interpolator_linear<agg::trans_affine> interpolator_type;
                interpolator_type interpolator(tr);

                typedef image_filter_2x2_type<source_type, 
                                              interpolator_type> span_gen_type;
                span_gen_type sg(source, interpolator, filter);
                agg::render_scanlines_aa(g_rasterizer, g_scanline, rb_pre, sa, sg);
                break;
            }

            case 1:
            {
                agg::trans_affine tr(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);

                typedef agg::span_interpolator_linear<agg::trans_affine> interpolator_type;
                typedef image_resample_affine_type<source_type> span_gen_type;

                interpolator_type interpolator(tr);
                span_gen_type sg(source, interpolator, filter);
                sg.blur(m_blur.value());
                agg::render_scanlines_aa(g_rasterizer, g_scanline, rb_pre, sa, sg);
                break;
            }

            case 2:
            {
                agg::trans_perspective tr(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);
                if(tr.is_valid())
                {
                    typedef agg::span_interpolator_linear_subdiv<agg::trans_perspective> interpolator_type;
                    interpolator_type interpolator(tr);

                    typedef image_filter_2x2_type<source_type,
                                                  interpolator_type> span_gen_type;
                    span_gen_type sg(source, interpolator, filter);
                    agg::render_scanlines_aa(g_rasterizer, g_scanline, rb_pre, sa, sg);
                }
                break;
            }

            case 3:
            {
                agg::trans_perspective tr(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);
                if(tr.is_valid())
                {
                    typedef agg::span_interpolator_trans<agg::trans_perspective> interpolator_type;
                    interpolator_type interpolator(tr);

                    typedef image_filter_2x2_type<source_type, 
                                                  interpolator_type> span_gen_type;
                    span_gen_type sg(source, interpolator, filter);
                    agg::render_scanlines_aa(g_rasterizer, g_scanline, rb_pre, sa, sg);
                }
                break;
            }

            case 4:
            {
                typedef agg::span_interpolator_persp_lerp<> interpolator_type;
                typedef agg::span_subdiv_adaptor<interpolator_type> subdiv_adaptor_type;

                interpolator_type interpolator(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);
                subdiv_adaptor_type subdiv_adaptor(interpolator);

                if(interpolator.is_valid())
                {
                    typedef image_resample_type<source_type, 
                                                subdiv_adaptor_type> span_gen_type;
                    span_gen_type sg(source, subdiv_adaptor, filter);
                    sg.blur(m_blur.value());
                    agg::render_scanlines_aa(g_rasterizer, g_scanline, rb_pre, sa, sg);
                }
                break;
            }

            case 5:
            {
                typedef agg::span_interpolator_persp_exact<> interpolator_type;
                typedef agg::span_subdiv_adaptor<interpolator_type> subdiv_adaptor_type;

                interpolator_type interpolator(m_quad.polygon(), g_x1, g_y1, g_x2, g_y2);
                subdiv_adaptor_type subdiv_adaptor(interpolator);

                if(interpolator.is_valid())
                {
                    typedef image_resample_type<source_type, 
                                                subdiv_adaptor_type> span_gen_type;
                    span_gen_type sg(source, subdiv_adaptor, filter);
                    sg.blur(m_blur.value());
                    agg::render_scanlines_aa(g_rasterizer, g_scanline, rb_pre, sa, sg);
                }
                break;
            }
        }
        double tm = elapsed_time();
        pixf.apply_gamma_inv(m_gamma_lut);

        char buf[64]; 
        agg::gsv_text t;
        t.size(10.0);

        agg::conv_stroke<agg::gsv_text> pt(t);
        pt.width(1.5);

        sprintf(buf, "%3.2f ms", tm);
        t.start_point(10.0, 70.0);
        t.text(buf);

        g_rasterizer.add_path(pt);
        r.color(agg::rgba(0,0,0));
        agg::render_scanlines(g_rasterizer, g_scanline, r);

        //--------------------------
        agg::render_ctrl(g_rasterizer, g_scanline, rb, m_trans_type);
        agg::render_ctrl(g_rasterizer, g_scanline, rb, m_gamma);
        agg::render_ctrl(g_rasterizer, g_scanline, rb, m_blur);
    }