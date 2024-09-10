            zero_index += 32;
            goto strlen_exit;
        }
        // Align address to the next 64 bytes for main loop.
        cur += 64;
    }
    else {
        // Align address to 64 bytes, and offset 32 bytes for misalignment.
        cur = (const char * )((size_t)cur & ((size_t)~(size_t)0x3F));

        // Load the src 32 bytes to XMM register
        src32_high = _mm256_load_si256((__m256i *)(cur + 32));
        // Compare with zero32 masks per byte.
        src32_high = _mm256_cmpeq_epi8(src32_high, zero32);
        // Package the compare result (32 bytes) to 32 bits.
        zero_mask_high = (size_t)_mm256_movemask_epi8(src32_high);
        // Skip 32 bytes.
        misalignment -= 32;
        // Remove last misalignment bits.
        zero_mask_high >>= misalignment;
        zero_mask_high <<= misalignment;

        // If it have any one bit is 1, mean it have a null terminator
        // inside this scaned strings (per 64 bytes).
        if (zero_mask_high != 0) {
            // Get the index of the first bit on set to 1.
            __BitScanForward(zero_index, zero_mask_high);
            zero_index += 32;
            goto strlen_exit;
        }
        // Align address to the next 64 bytes for main loop.