const VSFrameRef* YadifMod2::
getFrame(int n, VSCore* core, const VSAPI* api, VSFrameContext* ctx)
{
    int ft = field;
    if (mode == 1 || mode == 3) {
        ft = (n & 1) ? 1 - order : order;
        n /= 2;
    }

    auto edeint = eclip ? api->getFrameFilter(n, eclip, ctx)
                : nullptr;
    auto curr = api->getFrameFilter(n, clip, ctx);
    auto prev = api->getFrameFilter(n == 0 ? prevFirst : n - 1, clip, ctx);
    auto next = api->getFrameFilter(std::min(n + 1, nfSrc), clip, ctx);
    auto dst = api->newVideoFrame(vi.format, vi.width, vi.height, curr, core);

    for (int p = 0; p < vi.format->numPlanes; ++p) {
        auto currp = api->getReadPtr(curr, p);
        auto prevp = api->getReadPtr(prev, p);
        auto nextp = api->getReadPtr(next, p);

        size_t width = api->getFrameWidth(curr, p);
        size_t rowsize = width * vi.format->bytesPerSample;
        size_t height = api->getFrameHeight(curr, p);
        int cstride = api->getStride(curr, p);
        int pstride = api->getStride(prev, p);
        int nstride = api->getStride(next, p);

        int begin = 2 + ft;
        int count = (height - 4 + ft - begin) / 2 + 1;

        const uint8_t *fm_prev, *fm_next;
        int fm_pstride, fm_nstride;
        if (ft != order) {
            fm_pstride = cstride * 2;
            fm_nstride = nstride * 2;
            fm_prev = prevp + begin + cstride;
            fm_next = nextp + begin * nstride;
        } else {
            fm_pstride = pstride * 2;
            fm_nstride = cstride * 2;
            fm_prev = prevp + begin * pstride;
            fm_next = currp + begin * cstride;
        }

        const uint8_t* edeintp = nullptr;
        int estride = 0;
        if (eclip) {
            edeintp = api->getReadPtr(edeint, p);
            estride = api->getStride(edeint, p);
        }

        auto dstp = api->getWritePtr(dst, p);
        int dstride = api->getStride(dst, p);

        if (ft == 0) {
            memcpy(dstp, currp + cstride, rowsize);
            if (edeintp) {
                memcpy(dstp + dstride * (height - 2),
                       edeintp + estride * (height - 2), rowsize);
            } else {
                interp(dstp + dstride * (height - 2),
                       currp + cstride * (height - 3), cstride, width);
            }
        } else {
            if (edeintp) {
                memcpy(dstp + dstride, edeintp + estride, rowsize);
            } else {
                interp(dstp + dstride, currp, cstride, width);
            }
            memcpy(dstp + dstride * (height - 1),
                   currp + cstride * (height - 2), rowsize);
        }
        bitblt(dstp + (1 - ft) * dstride, dstride * 2,
               currp + (1 - ft) * cstride, cstride * 2, rowsize, height / 2);

        mainProc(currp + begin * cstride, prevp + begin * pstride,
                 nextp + begin * nstride, fm_prev, fm_next,
                 edeintp + begin * estride, dstp + begin * dstride, width,
                 cstride, pstride, nstride, fm_pstride, fm_nstride, estride * 2,
                 dstride * 2, count);
    }

    return dst;

}