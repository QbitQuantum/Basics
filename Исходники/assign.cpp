af_err af_assign_seq(af_array* out, const af_array lhs, const unsigned ndims,
                     const af_seq* index, const af_array rhs) {
    try {
        ARG_ASSERT(0, (lhs != 0));
        ARG_ASSERT(1, (ndims > 0));
        ARG_ASSERT(3, (rhs != 0));

        const ArrayInfo& lInfo = getInfo(lhs);

        if (ndims == 1 && ndims != lInfo.ndims()) {
            af_array tmp_in, tmp_out;
            AF_CHECK(af_flat(&tmp_in, lhs));
            AF_CHECK(af_assign_seq(&tmp_out, tmp_in, ndims, index, rhs));
            AF_CHECK(
                af_moddims(out, tmp_out, lInfo.ndims(), lInfo.dims().get()));
            AF_CHECK(af_release_array(tmp_in));
            // This can run into a double free issue if tmp_in == tmp_out
            // The condition ensures release only if both are different
            // Issue found on Tegra X1
            if (tmp_in != tmp_out) AF_CHECK(af_release_array(tmp_out));
            return AF_SUCCESS;
        }

        af_array res = 0;

        if (*out != lhs) {
            int count = 0;
            AF_CHECK(af_get_data_ref_count(&count, lhs));
            if (count > 1)
                AF_CHECK(af_copy_array(&res, lhs));
            else
                res = retain(lhs);
        } else {
            res = lhs;
        }

        try {
            if (lhs != rhs) {
                const dim4& outDims = getInfo(res).dims();
                const dim4& inDims  = getInfo(rhs).dims();

                vector<af_seq> inSeqs(ndims, af_span);
                for (unsigned i = 0; i < ndims; ++i) {
                    inSeqs[i] = convert2Canonical(index[i], outDims[i]);
                    ARG_ASSERT(3,
                               (inSeqs[i].begin >= 0. || inSeqs[i].end >= 0.));
                    if (signbit(inSeqs[i].step)) {
                        ARG_ASSERT(3, inSeqs[i].begin >= inSeqs[i].end);
                    } else {
                        ARG_ASSERT(3, inSeqs[i].begin <= inSeqs[i].end);
                    }
                }
                DIM_ASSERT(0, (outDims.ndims() >= inDims.ndims()));
                DIM_ASSERT(0, (outDims.ndims() >= (dim_t)ndims));

                const ArrayInfo& oInfo = getInfo(res);
                af_dtype oType         = oInfo.getType();
                switch (oType) {
                    case c64:
                        assign(getArray<cdouble>(res), inSeqs, rhs);
                        break;
                    case c32: assign(getArray<cfloat>(res), inSeqs, rhs); break;
                    case f64: assign(getArray<double>(res), inSeqs, rhs); break;
                    case f32: assign(getArray<float>(res), inSeqs, rhs); break;
                    case s32: assign(getArray<int>(res), inSeqs, rhs); break;
                    case u32: assign(getArray<uint>(res), inSeqs, rhs); break;
                    case s64: assign(getArray<intl>(res), inSeqs, rhs); break;
                    case u64: assign(getArray<uintl>(res), inSeqs, rhs); break;
                    case s16: assign(getArray<short>(res), inSeqs, rhs); break;
                    case u16: assign(getArray<ushort>(res), inSeqs, rhs); break;
                    case u8: assign(getArray<uchar>(res), inSeqs, rhs); break;
                    case b8: assign(getArray<char>(res), inSeqs, rhs); break;
                    default: TYPE_ERROR(1, oType); break;
                }
            }
        } catch (...) {
            af_release_array(res);
            throw;
        }
        swap(*out, res);
    }
    CATCHALL;
    return AF_SUCCESS;
}