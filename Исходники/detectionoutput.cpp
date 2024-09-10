int DetectionOutput::forward(const std::vector<Mat>& bottom_blobs, std::vector<Mat>& top_blobs) const
{
    const Mat& location = bottom_blobs[0];
    const Mat& confidence = bottom_blobs[1];
    const Mat& priorbox = bottom_blobs[2];

    const int num_prior = priorbox.w / 4;

    // apply location with priorbox
    Mat bboxes;
    bboxes.create(4, num_prior);
    if (bboxes.empty())
        return -100;

    const float* location_ptr = location;
    const float* priorbox_ptr = priorbox.row(0);
    const float* variance_ptr = priorbox.row(1);

    #pragma omp parallel for
    for (int i = 0; i < num_prior; i++)
    {
        const float* loc = location_ptr + i * 4;
        const float* pb = priorbox_ptr + i * 4;
        const float* var = variance_ptr + i * 4;

        float* bbox = bboxes.row(i);

        // CENTER_SIZE
        float pb_w = pb[2] - pb[0];
        float pb_h = pb[3] - pb[1];
        float pb_cx = (pb[0] + pb[2]) * 0.5f;
        float pb_cy = (pb[1] + pb[3]) * 0.5f;

        float bbox_cx = var[0] * loc[0] * pb_w + pb_cx;
        float bbox_cy = var[1] * loc[1] * pb_h + pb_cy;
        float bbox_w = exp(var[2] * loc[2]) * pb_w;
        float bbox_h = exp(var[3] * loc[3]) * pb_h;

        bbox[0] = bbox_cx - bbox_w * 0.5f;
        bbox[1] = bbox_cy - bbox_h * 0.5f;
        bbox[2] = bbox_cx + bbox_w * 0.5f;
        bbox[3] = bbox_cy + bbox_h * 0.5f;
    }

    // sort and nms for each class
    std::vector< std::vector<BBoxRect> > all_class_bbox_rects;
    std::vector< std::vector<float> > all_class_bbox_scores;
    all_class_bbox_rects.resize(num_class);
    all_class_bbox_scores.resize(num_class);

    // start from 1 to ignore background class
    #pragma omp parallel for
    for (int i = 1; i < num_class; i++)
    {
        // filter by confidence_threshold
        std::vector<BBoxRect> class_bbox_rects;
        std::vector<float> class_bbox_scores;

        for (int j = 0; j < num_prior; j++)
        {
            float score = confidence[j * num_class + i];

            if (score > confidence_threshold)
            {
                const float* bbox = bboxes.row(j);
                BBoxRect c = { bbox[0], bbox[1], bbox[2], bbox[3], i };
                class_bbox_rects.push_back(c);
                class_bbox_scores.push_back(score);
            }
        }

        // sort inplace
        qsort_descent_inplace(class_bbox_rects, class_bbox_scores);

        // keep nms_top_k
        if (nms_top_k < (int)class_bbox_rects.size())
        {
            class_bbox_rects.resize(nms_top_k);
            class_bbox_scores.resize(nms_top_k);
        }

        // apply nms
        std::vector<int> picked;
        nms_sorted_bboxes(class_bbox_rects, picked, nms_threshold);

        // select
        for (int j = 0; j < (int)picked.size(); j++)
        {
            int z = picked[j];
            all_class_bbox_rects[i].push_back(class_bbox_rects[z]);
            all_class_bbox_scores[i].push_back(class_bbox_scores[z]);
        }
    }

    // gather all class
    std::vector<BBoxRect> bbox_rects;
    std::vector<float> bbox_scores;

    for (int i = 1; i < num_class; i++)
    {
        const std::vector<BBoxRect>& class_bbox_rects = all_class_bbox_rects[i];
        const std::vector<float>& class_bbox_scores = all_class_bbox_scores[i];

        bbox_rects.insert(bbox_rects.end(), class_bbox_rects.begin(), class_bbox_rects.end());
        bbox_scores.insert(bbox_scores.end(), class_bbox_scores.begin(), class_bbox_scores.end());
    }

    // global sort inplace
    qsort_descent_inplace(bbox_rects, bbox_scores);

    // keep_top_k
    if (keep_top_k < (int)bbox_rects.size())
    {
        bbox_rects.resize(keep_top_k);
        bbox_scores.resize(keep_top_k);
    }

    // fill result
    int num_detected = bbox_rects.size();

    Mat& top_blob = top_blobs[0];
    top_blob.create(6, num_detected);
    if (top_blob.empty())
        return -100;

    for (int i = 0; i < num_detected; i++)
    {
        const BBoxRect& r = bbox_rects[i];
        float score = bbox_scores[i];
        float* outptr = top_blob.row(i);

        outptr[0] = r.label;
        outptr[1] = score;
        outptr[2] = r.xmin;
        outptr[3] = r.ymin;
        outptr[4] = r.xmax;
        outptr[5] = r.ymax;
    }

    return 0;
}