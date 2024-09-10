AbstractBuffer<int32_t> ADCensus::constructDisparityMap(const AbstractBuffer<pixel> *leftImage, const AbstractBuffer<pixel> *rightImage,
                                                        const AbstractBuffer<grayPixel> *leftGrayImage, const AbstractBuffer<grayPixel> *rightGrayImage) {
    // Initialization

    int width = leftImage->w;
    int height = leftImage->h;

    BaseTimeStatisticsCollector collector;
    Statistics outerStats;
    outerStats.setValue("H", height);
    outerStats.setValue("W", width);

    AbstractBuffer<int32_t> bestDisparities = AbstractBuffer<int32_t>(height, width);
    AbstractBuffer<COST_TYPE> minCosts = AbstractBuffer<COST_TYPE>(height, width);
    minCosts.fillWith(-1);

    // Disparity computation
    outerStats.startInterval();

    AbstractBuffer<int64_t> leftCensus  = AbstractBuffer<int64_t>(height, width);
    AbstractBuffer<int64_t> rightCensus = AbstractBuffer<int64_t>(height, width);
    makeCensus(leftGrayImage, leftCensus);
    makeCensus(rightGrayImage, rightCensus);
    outerStats.resetInterval("Making census");

    makeAggregationCrosses(leftImage);
    outerStats.resetInterval("Making aggregation crosses");

    for (uint i = 0; i < CORE_COUNT_OF(table1); i++)
    {
        table1[i] = robust(i, lambdaCT);
        table2[i] = robust(i, lambdaAD);
    }

    bool parallelDisp = true;

    parallelable_for(0, width / 3,
                     [this, &minCosts, &bestDisparities, &leftImage, &rightImage,
                     &leftCensus, &rightCensus, &collector, height, width, parallelDisp](const BlockedRange<int> &r)
    {
        for (int d = r.begin(); d != r.end(); ++d) {
            Statistics stats;
            stats.startInterval();
            AbstractBuffer<COST_TYPE> costs = AbstractBuffer<COST_TYPE>(height, width);
            stats.resetInterval("Matrix construction");

            parallelable_for(windowHh, height - windowHh,
                             [this, &costs, &leftImage, &rightImage, &leftCensus, &rightCensus, d, width](const BlockedRange<int> &r)
            {
                for (int y = r.begin(); y != r.end(); ++y) {
                    auto *im1 = &leftImage->element(y, windowWh + d);
                    auto *im2 = &rightImage->element(y, windowWh);

                    int64_t *cen1 = &leftCensus.element(y, windowWh + d);
                    int64_t *cen2 = &rightCensus.element(y, windowWh);

                    int x = windowWh + d;

#ifdef WITH_SSE
                    for (; x < width - windowWh; x += 8) {
                        FixedVector<Int16x8, 4> c1 = SSEReader8BBBB_DDDD::read((uint32_t *)im1);
                        FixedVector<Int16x8, 4> c2 = SSEReader8BBBB_DDDD::read((uint32_t *)im2);

                        UInt16x8 dr = SSEMath::difference(UInt16x8(c1[RGBColor::FIELD_R]), UInt16x8(c2[RGBColor::FIELD_R]));
                        UInt16x8 dg = SSEMath::difference(UInt16x8(c1[RGBColor::FIELD_G]), UInt16x8(c2[RGBColor::FIELD_G]));
                        UInt16x8 db = SSEMath::difference(UInt16x8(c1[RGBColor::FIELD_B]), UInt16x8(c2[RGBColor::FIELD_B]));

                        UInt16x8 ad = (dr + dg + db) >> 2;
                        Int16x8 cost_ad = Int16x8(robustLUTAD(ad[0]),
                                                  robustLUTAD(ad[1]),
                                                  robustLUTAD(ad[2]),
                                                  robustLUTAD(ad[3]),
                                                  robustLUTAD(ad[4]),
                                                  robustLUTAD(ad[5]),
                                                  robustLUTAD(ad[6]),
                                                  robustLUTAD(ad[7]));

                        Int64x2 cen10(&cen1[0]);
                        Int64x2 cen12(&cen1[2]);
                        Int64x2 cen14(&cen1[4]);
                        Int64x2 cen16(&cen1[6]);

                        Int64x2 cen20(&cen2[0]);
                        Int64x2 cen22(&cen2[2]);
                        Int64x2 cen24(&cen2[4]);
                        Int64x2 cen26(&cen2[6]);

                        Int64x2 diff0 = cen10 ^ cen20;
                        Int64x2 diff2 = cen12 ^ cen22;
                        Int64x2 diff4 = cen14 ^ cen24;
                        Int64x2 diff6 = cen16 ^ cen26;

                        Int16x8 cost_ct(robustLUTCen(_mm_popcnt_u64(diff0.getInt(0))), robustLUTCen(_mm_popcnt_u64(diff0.getInt(1))),
                                        robustLUTCen(_mm_popcnt_u64(diff2.getInt(0))), robustLUTCen(_mm_popcnt_u64(diff2.getInt(1))),
                                        robustLUTCen(_mm_popcnt_u64(diff4.getInt(0))), robustLUTCen(_mm_popcnt_u64(diff4.getInt(1))),
                                        robustLUTCen(_mm_popcnt_u64(diff6.getInt(0))), robustLUTCen(_mm_popcnt_u64(diff6.getInt(1))));

                        Int16x8 cost_total = cost_ad + cost_ct;
                        for (int i = 0; i < 8; ++i) {
                            costs.element(y, x + i) = cost_total[i];
                        }

                        im1 += 8;
                        im2 += 8;
                        cen1+= 8;
                        cen2+= 8;
                    }
#else
                    for (; x < width - windowWh; ++x) {
                        uint8_t c_ad = costAD(*im1, *im2);
                        uint8_t c_census = hammingDist(*cen1, *cen2);

                        costs.element(y, x) = robustLUTCen(c_census) + robustLUTAD(c_ad);

                        im1 ++;
                        im2 ++;
                        cen1++;
                        cen2++;
                    }
#endif
                }
            }, !parallelDisp
            );

            stats.resetInterval("Cost computation");

            aggregateCosts(&costs, windowWh + d, windowHh, width - windowWh, height - windowHh);

            stats.resetInterval("Cost aggregation");

            for (int x = windowWh + d; x < width - windowWh; ++x) {
                for (int y = windowHh; y < height - windowHh; ++y) {
                    tbb::mutex::scoped_lock(bestDisparitiesMutex);
                    if(costs.element(y, x) < minCosts.element(y, x)) {
                        minCosts.element(y, x) = costs.element(y, x);
                        bestDisparities.element(y, x) = d;

                        //result.element(y,x) = (bestDisparities.element(y, x) / (double)width * 255 * 3);
                    }
                }
            }
            //BMPLoader().save("../../result.bmp", result);

            stats.endInterval("Comparing with previous minimum");
            collector.addStatistics(stats);

        }
    }, parallelDisp);