  _declspec(dllexport) DiffResult __stdcall diff_img(Image left, Image right, DiffOptions options) {
    if (options.ignoreColor) {
      makeGreyscale(left);
      makeGreyscale(right);
    }

    float* imgMem = (float*)_aligned_malloc(left.width * left.height * sizeof(float) * 4, 16);
    int colorOffset = left.width * left.height;
    Image diff = { left.width, left.height, left.stride, imgMem, imgMem + colorOffset, imgMem + colorOffset * 2, imgMem + colorOffset * 3 };

    float* drp = diff.r;
    float* dgp = diff.g;
    float* dbp = diff.b;
    float* dap = diff.a;

    float* lrp = left.r;
    float* lgp = left.g;
    float* lbp = left.b;
    float* lap = left.a;

    float* rrp = right.r;
    float* rgp = right.g;
    float* rbp = right.b;
    float* rap = right.a;

    Color error = ConvertToFloat(options.errorColor);

    auto er = _mm_set_ps1(error.r);
    auto eg = _mm_set_ps1(error.g);
    auto eb = _mm_set_ps1(error.b);
    auto ea = _mm_set_ps1(error.a);

    auto tolerance = _mm_set_ps1(options.tolerance);
    auto overlayTransparency = _mm_set_ps1(options.overlayTransparency);

    OverlayType overlayType = options.overlayType;
    byte weightByDiffPercentage = options.weightByDiffPercentage;

    auto diffPixelCount = _mm_set_epi32(0, 0, 0, 0);
    auto onei = _mm_set1_epi32(1);
    auto one = _mm_set1_ps(1);
    auto zero = _mm_set1_ps(0);

    for (int y = 0; y < left.height; y++) {
      for (int x = 0; x < left.width; x+=4) {
        auto lr = _mm_load_ps(lrp);
        auto lg = _mm_load_ps(lgp);
        auto lb = _mm_load_ps(lbp);
        auto la = _mm_load_ps(lap);

        auto rr = _mm_load_ps(rrp);
        auto rg = _mm_load_ps(rgp);
        auto rb = _mm_load_ps(rbp);
        auto ra = _mm_load_ps(rap);

        auto rdiff = _mm_sub_ps(rr, lr);
        auto gdiff = _mm_sub_ps(rg, lg);
        auto bdiff = _mm_sub_ps(rb, lb);
        auto adiff = _mm_sub_ps(ra, la);

        auto distance = _mm_mul_ps(rdiff, rdiff);
        distance = _mm_add_ps(distance, _mm_mul_ps(gdiff, gdiff));
        distance = _mm_add_ps(distance, _mm_mul_ps(bdiff, bdiff));
        distance = _mm_add_ps(distance, _mm_mul_ps(adiff, adiff));
        distance = _mm_sqrt_ps(distance);

        auto t = overlayTransparency;
        if (weightByDiffPercentage) {
          t = _mm_mul_ps(t, distance);
        }

        auto isdiff = _mm_cmpgt_ps(distance, tolerance);

        t = _mm_min_ps(one, _mm_max_ps(zero, t));
        auto mlr = rr;
        auto mlg = rg;
        auto mlb = rb;
        auto mla = ra;

        if (overlayType == OverlayType::Movement) {
          mlr = _mm_mul_ps(mlr, er);
          mlg = _mm_mul_ps(mlg, eg);
          mlb = _mm_mul_ps(mlb, eb);
          mla = _mm_mul_ps(mla, ea);
        }

        auto oneMinusT = _mm_sub_ps(one, t);

        auto mixedR = _mm_add_ps(_mm_mul_ps(mlr, oneMinusT), _mm_mul_ps(er, t));
        auto mixedG = _mm_add_ps(_mm_mul_ps(mlg, oneMinusT), _mm_mul_ps(eg, t));
        auto mixedB = _mm_add_ps(_mm_mul_ps(mlb, oneMinusT), _mm_mul_ps(eb, t));
        auto mixedA = one;

        if (overlayType != OverlayType::Movement) {
          mixedA = _mm_add_ps(_mm_mul_ps(mla, oneMinusT), _mm_mul_ps(ea, t));
        }

        // (((b ^ a) & mask)^a)
        auto dr = _mm_xor_ps(lr, _mm_and_ps(isdiff, _mm_xor_ps(mixedR, lr)));
        auto dg = _mm_xor_ps(lg, _mm_and_ps(isdiff, _mm_xor_ps(mixedG, lg)));
        auto db = _mm_xor_ps(lb, _mm_and_ps(isdiff, _mm_xor_ps(mixedB, lb)));
        auto da = _mm_xor_ps(la, _mm_and_ps(isdiff, _mm_xor_ps(mixedA, la)));

        diffPixelCount = _mm_xor_si128(diffPixelCount,
          _mm_and_si128(_mm_castps_si128(isdiff),
            _mm_xor_si128(_mm_add_epi32(diffPixelCount, onei),
              diffPixelCount)));

        _mm_store_ps(drp, dr);
        _mm_store_ps(dgp, dg);
        _mm_store_ps(dbp, db);
        _mm_store_ps(dap, da);

        drp+=4;
        dgp+=4;
        dbp+=4;
        dap+=4;

        lrp+=4;
        lgp+=4;
        lbp+=4;
        lap+=4;

        rrp+=4;
        rgp+=4;
        rbp+=4;
        rap+=4;
      }
    }

    int* pixelCounts = (int*)_aligned_malloc(4 * sizeof(int), 16);
    _mm_store_si128((__m128i*)pixelCounts, diffPixelCount);

    int totalCount = pixelCounts[0] + pixelCounts[1] + pixelCounts[2] + pixelCounts[3];
    _aligned_free(pixelCounts);

    return{ diff, 1.0f - float(totalCount) / (left.height * left.width - left.height * left.stride) };
  }