QSharedPointer<Terrain> BrushTool::tip(QPoint origin)
{
    bool needToGenerate = false;
    if (!tip_) {
        tip_ = QSharedPointer<Terrain>::create(QSize(parameters_.size, parameters_.size));
        needToGenerate = true;
    }
    if (origin.x() < -500) {
        origin = lastTipOrigin_;
    }
    if (origin != lastTipOrigin_) {
        switch (parameters_.tipType) {
        case BrushTipType::Mountains:
            needToGenerate = true;
            break;
        default:
            // position invariant
            break;
        }
    }
    if (needToGenerate) {
        Terrain *t = tip_.data();
        auto size = parameters_.size;

        float scale = 1.f / size;

        switch (parameters_.tipType) {
        case BrushTipType::Mountains:
            {
                // Set rounding mode (required by CoherentNoiseGenerator)
                SseRoundingModeScope roundingModeScope(_MM_ROUND_DOWN);
                (void) roundingModeScope;

                if (noiseGenSeed != parameters_.seed) {
                    noiseGenSeed = parameters_.seed;
                    noiseGen.randomize(static_cast<std::uint_fast32_t>(noiseGenSeed));
                }

                auto noise = noiseGen.sampler();
                __m128i originMM = _mm_setr_epi32(origin.x(), origin.y(), 0, 0);
                float noiseScale = 10.f / parameters_.scale;

                for (int y = 0; y < size; ++y) {
                    for (int x = 0; x < size; ++x) {
                        int cx = (x << 1) - size + 1;
                        int cy = (y << 1) - size + 1;
                        float sq = 1.f - sqrtf(cx * cx + cy * cy) * scale;
                        float alt;
                        if (sq <= 0.f) {
                            alt = 0.f;
                        } else {
                            auto posI = _mm_add_epi32(_mm_setr_epi32(x, y, 0, 0), originMM);
                            auto pos = _mm_cvtepi32_ps(posI);
                            pos = _mm_mul_ps(pos, _mm_set1_ps(noiseScale));
                            auto pos1 = _mm_mul_ps(pos, _mm_set1_ps(0.1f));
                            pos = _mm_unpacklo_ps(_mm_hadd_ps(pos, pos), _mm_hsub_ps(pos, pos));
                            auto pos2 = _mm_mul_ps(pos, _mm_set1_ps(0.15f));
                            auto pos3 = _mm_mul_ps(pos, _mm_set1_ps(0.3f));
                            auto pos4 = _mm_mul_ps(pos, _mm_set1_ps(0.03f));
                            float noiseVal = noise.sample(pos1);
                            noiseVal += noise.sample(pos2) * .3f;
                            noiseVal += noise.sample(pos3) * .15f;
                            noiseVal += noise.sample(pos4) * 1.5f;
                            noiseVal = std::max(std::min(0.5f + noiseVal * 1.1f, 1.f), 0.f);

                            float sqBase = sq;
                            sq *= sq * (3.f - 2.f * sq) * 0.8f;
                            sq *= sq;
                            sq -= 0.1f;
                            sq += (sqBase - sq) * std::abs(noiseVal);
                            alt = std::max(0.f, sq);
                        }
                        t->landform(x, y) = alt;
                    }
                }
            }
            break;
        case BrushTipType::Bell:
            for (int y = 0; y < size; ++y) {
                for (int x = 0; x < size; ++x) {
                    int cx = (x << 1) - size + 1;
                    int cy = (y << 1) - size + 1;
                    float sq = 1.f - sqrtf(cx * cx + cy * cy) * scale;
                    float alt;
                    if (sq <= 0.f) {
                        alt = 0.f;
                    } else {
                        sq *= sq * (3.f - 2.f * sq);
                        alt = sq;
                    }
                    t->landform(x, y) = alt;
                }
            }
            break;
        case BrushTipType::Cone:
            for (int y = 0; y < size; ++y) {
                for (int x = 0; x < size; ++x) {
                    int cx = (x << 1) - size + 1;
                    int cy = (y << 1) - size + 1;
                    float sq = 1.f - sqrtf(cx * cx + cy * cy) * scale;
                    float alt;
                    if (sq <= 0.f) {
                        alt = 0.f;
                    } else {
                        alt = sq;
                    }
                    t->landform(x, y) = alt;
                }
            }
            break;
        case BrushTipType::Sphere:
            scale *= scale;
            for (int y = 0; y < size; ++y) {
                for (int x = 0; x < size; ++x) {
                    int cx = (x << 1) - size + 1;
                    int cy = (y << 1) - size + 1;
                    float sq = 1.f - (cx * cx + cy * cy) * scale;
                    float alt;
                    if (sq <= 0.f) {
                        alt = 0.f;
                    } else {
                        alt = std::sqrt(sq);
                    }
                    t->landform(x, y) = alt;
                }
            }
            break;
        case BrushTipType::Cylinder:
            for (int y = 0; y < size; ++y) {
                for (int x = 0; x < size; ++x) {
                    int cx = (x << 1) - size + 1;
                    int cy = (y << 1) - size + 1;
                    float sq = size * size - (cx * cx + cy * cy);
                    float alt;
                    if (sq <= 0.f) {
                        alt = 0.f;
                    } else {
                        alt = 1.f;
                    }
                    t->landform(x, y) = alt;
                }
            }
            break;
        case BrushTipType::Square:
            for (int y = 0; y < size; ++y) {
                for (int x = 0; x < size; ++x) {
                    t->landform(x, y) = 1.f;
                }
            }
            break;
        }

    }
    return tip_;
}