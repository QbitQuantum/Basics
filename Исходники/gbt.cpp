void CvGBTrees::find_gradient(const int k)
{
    int* sample_data = sample_idx->data.i;
    int* subsample_data = subsample_train->data.i;
    float* grad_data = data->responses->data.fl;
    float* resp_data = orig_response->data.fl;
    float* current_data = sum_response->data.fl;

    switch (params.loss_function_type)
    // loss_function_type in
    // {SQUARED_LOSS, ABSOLUTE_LOSS, HUBER_LOSS, DEVIANCE_LOSS}
    {
        case SQUARED_LOSS:
        {
            for (int i=0; i<get_len(subsample_train); ++i)
            {
                int s_step = (sample_idx->cols > sample_idx->rows) ? 1
                             : sample_idx->step/CV_ELEM_SIZE(sample_idx->type);
                int idx = *(sample_data + subsample_data[i]*s_step);
                grad_data[idx] = resp_data[idx] - current_data[idx];
            }
        }; break;

        case ABSOLUTE_LOSS:
        {
            for (int i=0; i<get_len(subsample_train); ++i)
            {
                int s_step = (sample_idx->cols > sample_idx->rows) ? 1
                             : sample_idx->step/CV_ELEM_SIZE(sample_idx->type);
                int idx = *(sample_data + subsample_data[i]*s_step);
                grad_data[idx] = Sign(resp_data[idx] - current_data[idx]);
            }
        }; break;

        case HUBER_LOSS:
        {
            float alpha = 0.2f;
            int n = get_len(subsample_train);
            int s_step = (sample_idx->cols > sample_idx->rows) ? 1
                         : sample_idx->step/CV_ELEM_SIZE(sample_idx->type);

            float* residuals = new float[n];
            for (int i=0; i<n; ++i)
            {
                int idx = *(sample_data + subsample_data[i]*s_step);
                residuals[i] = fabs(resp_data[idx] - current_data[idx]);
            }
            icvSortFloat(residuals, n, 0.0f);

            delta = residuals[int(ceil(n*alpha))];

            for (int i=0; i<n; ++i)
            {
                int idx = *(sample_data + subsample_data[i]*s_step);
                float r = resp_data[idx] - current_data[idx];
                grad_data[idx] = (fabs(r) > delta) ? delta*Sign(r) : r;
            }
            delete[] residuals;

        }; break;

        case DEVIANCE_LOSS:
        {
            for (int i=0; i<get_len(subsample_train); ++i)
            {
                double exp_fk = 0;
                double exp_sfi = 0;
                int s_step = (sample_idx->cols > sample_idx->rows) ? 1
                             : sample_idx->step/CV_ELEM_SIZE(sample_idx->type);
                int idx = *(sample_data + subsample_data[i]*s_step);

                for (int j=0; j<class_count; ++j)
                {
                    double res;
                    res = current_data[idx + j*sum_response->cols];
                    res = exp(res);
                    if (j == k) exp_fk = res;
                    exp_sfi += res;
                }
                int orig_label = int(resp_data[idx]);
                /*
                grad_data[idx] = (float)(!(k-class_labels->data.i[orig_label]+1)) -
                                 (float)(exp_fk / exp_sfi);
                */
                int ensemble_label = 0;
                while (class_labels->data.i[ensemble_label] - orig_label)
                    ensemble_label++;

                grad_data[idx] = (float)(!(k-ensemble_label)) -
                                 (float)(exp_fk / exp_sfi);
            }
        }; break;

        default: break;
    }

} // CvGBTrees::find_gradient(...)