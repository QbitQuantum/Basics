int memcpyTest(MemcpyType type, bool callKernel, void *(*memcpy_fn)(void *, const void *, size_t n))
{
	int error = 0;

	ecl::config globalSize (1);
	ecl::config localSize (1);

	ecl::error ret;
	ecl::kernel kernel("null", ret);
	assert(ret == eclSuccess);

	uint8_t *baseSrc = NULL;
	uint8_t *eclSrc = NULL;
	uint8_t *eclDst = NULL;

	baseSrc = (uint8_t *)malloc(maxCount);
	init(baseSrc, int(maxCount), 0xca);
	for (size_t count = minCount; count <= maxCount; count *= 2) {
		fprintf(stderr, "ALLOC: "FMT_SIZE"\n", count);

		if (type == GMAC_TO_GMAC) {
			assert(ecl::malloc((void **)&eclSrc, count) == eclSuccess);
			assert(ecl::malloc((void **)&eclDst, count) == eclSuccess);
		} else if (type == HOST_TO_GMAC) {
			eclSrc = (uint8_t *)malloc(count);
			assert(ecl::malloc((void **)&eclDst, count) == eclSuccess);
		} else if (type == GMAC_TO_HOST) {
			assert(ecl::malloc((void **)&eclSrc, count) == eclSuccess);
			eclDst = (uint8_t *)malloc(count);
		}

		for (size_t stride = 0, i = 1; stride < count/3; stride = i, i =  i * 2 - (i == 1? 0: 1)) {
			for (size_t copyCount = 1; copyCount < count/3; copyCount *= 2) {
				init(eclSrc + stride, int(copyCount), 0xca);
				if (stride == 0) {
					init(eclDst + stride, int(copyCount) + 1, 0);
				} else {
					init(eclDst + stride - 1, int(copyCount) + 2, 0);
				}
				assert(stride + copyCount <= count);

				if (callKernel) {
					ret = kernel.callNDRange(globalSize, localSize);
					assert(ret == eclSuccess);
				}
				memcpy_fn(eclDst + stride, eclSrc + stride, copyCount);

				int ret = memcmp(eclDst + stride, baseSrc + stride, copyCount);
				if (stride == 0) {
					ret = ret && (eclDst[stride - 1] == 0 && eclDst[stride + copyCount] == 0);
				} else {
					ret = ret && (eclDst[stride - 1] == 0 && eclDst[stride + copyCount] == 0);
				}

				if (ret != 0) {
#if 0
					fprintf(stderr, "Error: eclToGmacTest size: %zd, stride: %zd, copy: %zd\n",
						count    ,
						stride   ,
						copyCount);
#endif
					abort();
					error = 1;
					goto exit_test;
				}
#if 0
				for (unsigned k = 0; k < count; k++) {
					int ret = baseDst[k] != eclDst[k];
					if (ret != 0) {
						fprintf(stderr, "Error: eclToGmacTest size: %zd, stride: %zd, copy: %zd. Pos %u\n", count    ,
							stride   ,
							copyCount, k);
						error = 1;
					}
				}
#endif
			}
		}

		if (type == GMAC_TO_GMAC) {
			assert(ecl::free(eclSrc) == eclSuccess);
			assert(ecl::free(eclDst) == eclSuccess);
		} else if (type == HOST_TO_GMAC) {
			free(eclSrc);
			assert(ecl::free(eclDst) == eclSuccess);
		} else if (type == GMAC_TO_HOST) {
			assert(ecl::free(eclSrc) == eclSuccess);
			free(eclDst);
		}
	}
	free(baseSrc);

	return error;

exit_test:
	if (type == GMAC_TO_GMAC) {
		assert(ecl::free(eclSrc) == eclSuccess);
		assert(ecl::free(eclDst) == eclSuccess);
	} else if (type == HOST_TO_GMAC) {
		free(eclSrc);
		assert(ecl::free(eclDst) == eclSuccess);
	} else if (type == GMAC_TO_HOST) {
		assert(ecl::free(eclSrc) == eclSuccess);
		free(eclDst);
	}

	free(baseSrc);

	return error;
}