ConnectedComponent::ConnectedComponent(
		std::array<char, 8> value,
		boost::shared_ptr<pixel_list_type> pixelList,
		pixel_list_type::const_iterator begin,
		pixel_list_type::const_iterator end) :

	_pixels(pixelList),
	_value(value),
	_boundingBox(0, 0, 0, 0),
	_center(0, 0),
	_centerDirty(true),
	_pixelRange(begin, end),
	_bitmapDirty(true) {

#ifdef __SSE4_1__

	// if there is at least one pixel
	if (begin != end) {

		unsigned int*__restrict__ pixels    = (unsigned int*)&*begin;
		unsigned int*__restrict__ pixelsEnd = (unsigned int*)&*end;

		// Prepare aligned, packed integer values.
		typedef union {
			__m128i v;
			unsigned int a[4];
		} xmm_uints;

		enum {X1, Y1, X2, Y2};

		__attribute__((aligned(16))) xmm_uints mins1;
		__attribute__((aligned(16))) xmm_uints maxs1;

		mins1.a[X1] = begin->x();
		maxs1.a[X1] = begin->x();
		mins1.a[Y1] = begin->y();
		maxs1.a[Y1] = begin->y();

		// Iterate through pixelList until 16-byte alignment is reached.
		while (((std::uintptr_t) pixels % 16) != 0 && pixels < pixelsEnd) {

			unsigned int x = pixels[X1];
			unsigned int y = pixels[Y1];

			mins1.a[X1] = std::min(mins1.a[X1], x);
			mins1.a[Y1] = std::min(mins1.a[Y1], y);
			maxs1.a[X1] = std::max(maxs1.a[X1], x);
			maxs1.a[Y1] = std::max(maxs1.a[Y1], y);

			pixels += 2;
		}

		// Guaranteed to have at least 8 XMM registers, so use 4 for cumulative
		// values and 2 for vector values. (Using 8+4 of 16 registers on 64-bit
		// arch yields no performance improvement.)
		mins1.a[X2] = mins1.a[X1];
		mins1.a[Y2] = mins1.a[Y1];
		maxs1.a[X2] = maxs1.a[X1];
		maxs1.a[Y2] = maxs1.a[Y1];
		__m128i mins2 = mins1.v;
		__m128i maxs2 = maxs1.v;

		// Vectorized loop. Strides two packed integer vectors, each containing
		// both X and Y for two pixels.
		while (pixels < pixelsEnd - 8) {

			__m128i pixelPair1 = _mm_load_si128((__m128i*)pixels);
			__m128i pixelPair2 = _mm_load_si128((__m128i*)(pixels + 4));
			pixels += 8; // Hint compiler to iterate while loads stall.
			_mm_prefetch(pixels, _MM_HINT_T0);
			mins1.v = _mm_min_epu32(mins1.v, pixelPair1);
			maxs1.v = _mm_max_epu32(maxs1.v, pixelPair1);
			mins2   = _mm_min_epu32(mins2,   pixelPair2);
			maxs2   = _mm_max_epu32(maxs2,   pixelPair2);
		}

		// Combine stride results.
		mins1.v = _mm_min_epu32(mins1.v, mins2);
		maxs1.v = _mm_max_epu32(maxs1.v, maxs2);

		// Iterate through any remaining pixels.
		while (pixels < pixelsEnd) {

			unsigned int x = pixels[X1];
			unsigned int y = pixels[Y1];

			mins1.a[X1] = std::min(mins1.a[X1], x);
			mins1.a[Y1] = std::min(mins1.a[Y1], y);
			maxs1.a[X1] = std::max(maxs1.a[X1], x);
			maxs1.a[Y1] = std::max(maxs1.a[Y1], y);

			pixels += 2;
		}

		// Readout packed vectors, compare with remaining results, and store.
		_boundingBox.min().x() = (int)std::min(mins1.a[X1], mins1.a[X2]);
		_boundingBox.min().y() = (int)std::min(mins1.a[Y1], mins1.a[Y2]);
		_boundingBox.max().x() = (int)std::max(maxs1.a[X1], maxs1.a[X2]) + 1;
		_boundingBox.max().y() = (int)std::max(maxs1.a[Y1], maxs1.a[Y2]) + 1;
	}