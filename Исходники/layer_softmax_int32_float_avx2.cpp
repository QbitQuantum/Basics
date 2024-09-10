    void run_softmax_int32_float_work_item_latency(nn_workload_item *const work_item)
    {
        nn_workload_data_t *input_view = work_item->input[0]->output;
        const auto &arguments = work_item->arguments.forward_softmax_fixedpoint;

        const auto input_width = input_view->parent->lengths.t[NN_DATA_COORD_z] * input_view->parent->lengths.t[NN_DATA_COORD_p];
        const auto output_width = work_item->output->view_end.t[NN_DATA_COORD_x] - work_item->output->view_begin.t[NN_DATA_COORD_x] + 1;

        const auto num_full_blocks = output_width / C_data_stride;
        const auto partial_block_size = (output_width / C_simd_width) % C_max_acc;
        const auto subsimd_block_size = output_width % C_simd_width;

        const auto output_view_start = work_item->output->view_begin.t[NN_DATA_COORD_x];

        const auto input_view_start = input_view->view_begin.t[NN_DATA_COORD_z] * input_view->parent->lengths.t[NN_DATA_COORD_p];

        const auto out_fraction = arguments.input_fraction;

        float * input_f = (float*)_mm_malloc(input_width * sizeof(float), 64);

        auto input_buffer = &static_cast<int32_t*>(input_view->parent->data_buffer)[input_view_start];

        auto shift = out_fraction;
        if (shift > 0)
        {
            for (uint32_t i = 0; i < input_width; i++)
                input_f[i] = (float)(input_buffer[i]) / (1 << shift);
        }
        else if (shift < 0)
        {
            for (uint32_t i = 0; i < input_width; i++)
                input_f[i] = (float)(input_buffer[i]) * (1 << -shift);
        }
        else
        {
            for (uint32_t i = 0; i < input_width; i++)
                input_f[i] = (float)(input_buffer[i]);
        }

        __m256 acc_sum = _mm256_setzero_ps();
        float subsimd_sum = 0.0f;
        {
            auto input_buffer = input_f;
            auto output_buffer = &static_cast<float*>(work_item->output->parent->data_buffer)[output_view_start];

            for (auto block = 0u; block < num_full_blocks; ++block)
            {
                // Run computation.
                softmax_compute_block<C_max_acc>(input_buffer, output_buffer, acc_sum);
            }

            switch (partial_block_size)
            {
            case  0: break;
            case  1: softmax_compute_block< 1>(input_buffer, output_buffer, acc_sum); break;
            case  2: softmax_compute_block< 2>(input_buffer, output_buffer, acc_sum); break;
            case  3: softmax_compute_block< 3>(input_buffer, output_buffer, acc_sum); break;
            case  4: softmax_compute_block< 4>(input_buffer, output_buffer, acc_sum); break;
            case  5: softmax_compute_block< 5>(input_buffer, output_buffer, acc_sum); break;
            case  6: softmax_compute_block< 6>(input_buffer, output_buffer, acc_sum); break;
            case  7: softmax_compute_block< 7>(input_buffer, output_buffer, acc_sum); break;
            case  8: softmax_compute_block< 8>(input_buffer, output_buffer, acc_sum); break;
            case  9: softmax_compute_block< 9>(input_buffer, output_buffer, acc_sum); break;
            case 10: softmax_compute_block<10>(input_buffer, output_buffer, acc_sum); break;
            case 11: softmax_compute_block<11>(input_buffer, output_buffer, acc_sum); break;
            case 12: softmax_compute_block<12>(input_buffer, output_buffer, acc_sum); break;
            case 13: softmax_compute_block<13>(input_buffer, output_buffer, acc_sum); break;
            case 14: softmax_compute_block<14>(input_buffer, output_buffer, acc_sum); break;
            default: NN_UNREACHABLE_CODE;
            }

            switch (subsimd_block_size)
            {
            case 0: break;
            case 1: softmax_compute_subsimd<1>(input_buffer, output_buffer, subsimd_sum); break;
            case 2: softmax_compute_subsimd<2>(input_buffer, output_buffer, subsimd_sum); break;
            case 3: softmax_compute_subsimd<3>(input_buffer, output_buffer, subsimd_sum); break;
            case 4: softmax_compute_subsimd<4>(input_buffer, output_buffer, subsimd_sum); break;
            case 5: softmax_compute_subsimd<5>(input_buffer, output_buffer, subsimd_sum); break;
            case 6: softmax_compute_subsimd<6>(input_buffer, output_buffer, subsimd_sum); break;
            case 7: softmax_compute_subsimd<7>(input_buffer, output_buffer, subsimd_sum); break;
            default: NN_UNREACHABLE_CODE;
            }
        }

        {
            __m256 intermediate_sum = _mm256_hadd_ps(acc_sum, acc_sum);
            intermediate_sum = _mm256_permutevar8x32_ps(intermediate_sum, _mm256_set_epi32(0, 1, 4, 5, 2, 3, 6, 7));
            intermediate_sum = _mm256_hadd_ps(intermediate_sum, intermediate_sum);
            intermediate_sum = _mm256_hadd_ps(intermediate_sum, intermediate_sum);

            acc_sum = _mm256_add_ps(intermediate_sum, _mm256_set1_ps(subsimd_sum));
            subsimd_sum = _mm_cvtss_f32(_mm256_extractf128_ps(acc_sum, 0));

            acc_sum = _mm256_div_ps(_mm256_set1_ps(1.0f), acc_sum);
            subsimd_sum = 1.0f / subsimd_sum;
        }

        {
            auto output_buffer = &static_cast<float*>(work_item->output->parent->data_buffer)[output_view_start];

            for (auto block = 0u; block < num_full_blocks; ++block)
            {
                // Run computation.
                softmax_finalize_block<C_max_acc>(output_buffer, acc_sum);
            }

            switch (partial_block_size)
            {
            case  0: break;
            case  1: softmax_finalize_block< 1>(output_buffer, acc_sum); break;
            case  2: softmax_finalize_block< 2>(output_buffer, acc_sum); break;
            case  3: softmax_finalize_block< 3>(output_buffer, acc_sum); break;
            case  4: softmax_finalize_block< 4>(output_buffer, acc_sum); break;
            case  5: softmax_finalize_block< 5>(output_buffer, acc_sum); break;
            case  6: softmax_finalize_block< 6>(output_buffer, acc_sum); break;
            case  7: softmax_finalize_block< 7>(output_buffer, acc_sum); break;
            case  8: softmax_finalize_block< 8>(output_buffer, acc_sum); break;
            case  9: softmax_finalize_block< 9>(output_buffer, acc_sum); break;
            case 10: softmax_finalize_block<10>(output_buffer, acc_sum); break;
            case 11: softmax_finalize_block<11>(output_buffer, acc_sum); break;
            case 12: softmax_finalize_block<12>(output_buffer, acc_sum); break;
            case 13: softmax_finalize_block<13>(output_buffer, acc_sum); break;
            case 14: softmax_finalize_block<14>(output_buffer, acc_sum); break;
            default: NN_UNREACHABLE_CODE;
            }

            switch (subsimd_block_size)
            {
            case 0: break;
            case 1: softmax_finalize_subsimd<1>(output_buffer, subsimd_sum); break;
            case 2: softmax_finalize_subsimd<2>(output_buffer, subsimd_sum); break;
            case 3: softmax_finalize_subsimd<3>(output_buffer, subsimd_sum); break;
            case 4: softmax_finalize_subsimd<4>(output_buffer, subsimd_sum); break;
            case 5: softmax_finalize_subsimd<5>(output_buffer, subsimd_sum); break;
            case 6: softmax_finalize_subsimd<6>(output_buffer, subsimd_sum); break;
            case 7: softmax_finalize_subsimd<7>(output_buffer, subsimd_sum); break;
            default: NN_UNREACHABLE_CODE;
            }
        }
        _mm_free(input_f);
    }