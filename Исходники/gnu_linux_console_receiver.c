/**
 * Receives a gnu/linux console character.
 *
 * @param p0 the destination wide character array (Hand over as reference!)
 * @param p1 the destination wide character array count
 * @param p2 the destination wide character array size
 * @param p3 the loop break flag
 * @param p4 the input character
 * @param p5 the escape character mode
 * @param p6 the escape control sequence mode
 * @param p7 the source input stream
 * @param p8 the mutex
 */
void receive_gnu_linux_console_character(void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {

    if (p7 != *NULL_POINTER_MEMORY_MODEL) {

        FILE* s = (FILE*) p7;

        if (p6 != *NULL_POINTER_MEMORY_MODEL) {

            int* csi = (int*) p6;

            if (p5 != *NULL_POINTER_MEMORY_MODEL) {

                int* esc = (int*) p5;

                if (p4 != *NULL_POINTER_MEMORY_MODEL) {

                    wint_t* c = (wint_t*) p4;

                    if (p3 != *NULL_POINTER_MEMORY_MODEL) {

                        int* b = (int*) p3;

                        log_terminated_message((void*) DEBUG_LEVEL_LOG_MODEL, (void*) L"Receive gnu/linux console character.");

                        // Initialise error number.
                        // It is a global variable/ function and other operations
                        // may have set some value that is not wanted here.
                        //
                        // CAUTION! Initialise the error number BEFORE calling
                        // the function that might cause an error.
                        errno = *NUMBER_0_INTEGER_MEMORY_MODEL;

                        // Lock gnu/linux console mutex.
                        pthread_mutex_lock(p8);

                        // Receive character from source input stream of gnu/linux console.
                        //
                        // CAUTION! The multibyte- is converted to a wide character internally,
                        // so that the return value of type "wint_t" may be casted to "wchar_t".
                        // Function calls to "decode_utf_8_unicode_character_vector" are therefore NOT necessary here!
                        *c = fgetwc(s);

                        // Unlock gnu/linux console mutex.
                        pthread_mutex_unlock(p8);

                        if (errno != EILSEQ) {

                            if (*csi == *NUMBER_1_INTEGER_MEMORY_MODEL) {

                                // Reset escape control sequence flag.
                                *csi = *NUMBER_0_INTEGER_MEMORY_MODEL;

                                // Copy source character to destination character array.
                                overwrite_array(p0, p4, (void*) WIDE_CHARACTER_PRIMITIVE_MEMORY_ABSTRACTION, (void*) PRIMITIVE_MEMORY_MODEL_COUNT, p1, (void*) VALUE_PRIMITIVE_MEMORY_NAME, p1, p2);

                                // Set loop break flag.
                                // An escape character followed by a left square bracket character
                                // were received before. So this is an escape control sequence.
                                // Since all values have been received, the loop can be left now.
                                *b = *NUMBER_1_INTEGER_MEMORY_MODEL;

                            } else if (*esc == *NUMBER_1_INTEGER_MEMORY_MODEL) {

                                // Reset escape character flag.
                                *esc = *NUMBER_0_INTEGER_MEMORY_MODEL;

                                // An escape character was received before.

                                if (*c == *((wint_t*) LEFT_SQUARE_BRACKET_UNICODE_CHARACTER_CODE_MODEL)) {

                                    // The escape character received before is followed by an opening square bracket,
                                    // which means that this is the start of an escape control sequence.

                                    // Set escape control sequence flag.
                                    *csi = *NUMBER_1_INTEGER_MEMORY_MODEL;

                                    // Copy source character to destination character array.
                                    overwrite_array(p0, p4, (void*) WIDE_CHARACTER_PRIMITIVE_MEMORY_ABSTRACTION, (void*) PRIMITIVE_MEMORY_MODEL_COUNT, p1, (void*) VALUE_PRIMITIVE_MEMORY_NAME, p1, p2);

                                } else {

                                    // This is NOT going to be an escape control sequence.
                                    // An escape- followed by another, second character
                                    // (which is not an opening square bracket) has been detected.

                                    // Lock gnu/linux console mutex.
                                    pthread_mutex_lock(p8);

                                    // Unget this character so that it may be processed once more later on.
                                    ungetwc(*c, p7);

                                    // Unlock gnu/linux console mutex.
                                    pthread_mutex_unlock(p8);

                                    // Set loop break flag.
                                    *b = *NUMBER_1_INTEGER_MEMORY_MODEL;
                                }

                            } else if (*c == *((wint_t*) ESCAPE_CONTROL_UNICODE_CHARACTER_CODE_MODEL)) {

                                // Set escape character flag.
                                *esc = *NUMBER_1_INTEGER_MEMORY_MODEL;

                                // Copy source character to destination character array.
                                overwrite_array(p0, p4, (void*) WIDE_CHARACTER_PRIMITIVE_MEMORY_ABSTRACTION, (void*) PRIMITIVE_MEMORY_MODEL_COUNT, p1, (void*) VALUE_PRIMITIVE_MEMORY_NAME, p1, p2);

                            } else if (*c == WEOF) {

                                // The function "communicate_sensing_gnu_linux_console_message" filters out
                                // invalid (non-existing) characters recognised by the return value WEOF (-1).
                                // However, to be on the safe side, they are filtered out here once more.

                                // Set loop break flag.
                                *b = *NUMBER_1_INTEGER_MEMORY_MODEL;

                            } else {

                                // Copy source character to destination character array.
                                overwrite_array(p0, p4, (void*) WIDE_CHARACTER_PRIMITIVE_MEMORY_ABSTRACTION, (void*) PRIMITIVE_MEMORY_MODEL_COUNT, p1, (void*) VALUE_PRIMITIVE_MEMORY_NAME, p1, p2);

                                // Set loop break flag.
                                *b = *NUMBER_1_INTEGER_MEMORY_MODEL;
                            }

                        } else {

                            log_terminated_message((void*) ERROR_LEVEL_LOG_MODEL, (void*) L"Could not receive from gnu/linux console. The character reading failed.");

                            // Set loop break flag.
                            *b = *NUMBER_1_INTEGER_MEMORY_MODEL;
                        }

                    } else {

                        log_terminated_message((void*) ERROR_LEVEL_LOG_MODEL, (void*) L"Could not receive gnu/linux console character. The loop break flag is null.");
                    }

                } else {

                    log_terminated_message((void*) ERROR_LEVEL_LOG_MODEL, (void*) L"Could not receive gnu/linux console character. The input character is null.");
                }

            } else {

                log_terminated_message((void*) ERROR_LEVEL_LOG_MODEL, (void*) L"Could not receive gnu/linux console character. The escape character mode is null.");
            }

        } else {

            log_terminated_message((void*) ERROR_LEVEL_LOG_MODEL, (void*) L"Could not receive gnu/linux console character. The escape control sequence is null.");
        }

    } else {

        log_terminated_message((void*) ERROR_LEVEL_LOG_MODEL, (void*) L"Could not receive gnu/linux console character. The source input stream is null.");
    }
}