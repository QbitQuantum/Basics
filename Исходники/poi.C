Array2D<float> evaluateImage(const Image &src, const std::vector<float> &scales, int steps)
{
    int border = 2.5f * (*std::max_element(scales.begin(), scales.end()));
    int w = src.getWidth(), h = src.getHeight();

    progress(0);

    Array2D<float> globalProfile[steps];
    for(int i=0; i<steps; i++) {
        globalProfile[i] = Array2D<float>(w,h);
        globalProfile[i].fill(1.f);
    }

    {
        Array2D<float> currentProfile[steps];
        for(int i=0; i<steps; i++)
            currentProfile[i] = Array2D<float>(w,h);
        
        PrefixSums ps(src);

        DifferenceJob jobs[steps];
        Completion c;

        float progress_step = 1.f/(steps * scales.size());
        float progress_done = 0.f;

        for(int i=0; i<steps; i++) {
            jobs[i].src = &ps;
            jobs[i].dst = &currentProfile[i];
            jobs[i].x1 = border;
            jobs[i].y1 = border;
            jobs[i].x2 = w-border;
            jobs[i].y2 = h-border;
            jobs[i].progress_step = progress_step;
            jobs[i].progress_done = &progress_done;
            jobs[i].completion = &c;
        }
        
        for(int s=0; s<(int)scales.size(); s++)
        {
            for(int i=0; i<steps; i++)
            {
                float angle = 2.0f*M_PI/steps*i;
                jobs[i].scale = scales[s];
                jobs[i].dx = jobs[i].scale * cosf(angle);
                jobs[i].dy = jobs[i].scale * sinf(angle);
                aq->queue(&jobs[i]);
            }
            
            c.wait();
            
            for(int i=0; i<steps; i++)
                for(int y=0; y<h; y++)
                    for(int x=0; x<w; x++)
                        globalProfile[i][y][x] *= currentProfile[i][y][x];
        }
    }

    Array2D<float> maxs(globalProfile[0]), mins(globalProfile[0]);
    
    for(int i=1; i<steps; i++)
        for(int y=border; y<h-border; y++)
            for(int x=border; x<w-border; x++) {
                maxs[y][x] = std::max(maxs[y][x], globalProfile[i][y][x]);
                mins[y][x] = std::min(mins[y][x], globalProfile[i][y][x]);
            }

    Array2D<float> eval(w,h);
    eval.fill(0.f);
    for(int y=border; y<h-border; y++)
        for(int x=border; x<w-border; x++)
            eval[y][x] = powf(maxs[y][x] - mins[y][x], 1.0f/scales.size());
    return eval;
}