/**
 * Senses gnu/linux console message.
 *
 * @param p0 the interrupt
 * @param p1 the mutex
 * @param p2 the sleep time
 * @param p3 the input stream
 */
void communicate_sensing_gnu_linux_console_message(void* p0, void* p1, void* p2, void* p3) {

    if (p3 != *NULL_POINTER_MEMORY_MODEL) {

        FILE* is = (FILE*) p3;

        if (p2 != *NULL_POINTER_MEMORY_MODEL) {

            double* st = (double*) p2;

            if (p1 != *NULL_POINTER_MEMORY_MODEL) {

                pthread_mutex_t* mt = (pthread_mutex_t*) p1;

                if (p0 != *NULL_POINTER_MEMORY_MODEL) {

                    int* irq = (int*) p0;

                    // CAUTION! DO NOT log this function call!
                    // This function is executed within a thread, but the
                    // logging is not guaranteed to be thread-safe and might
                    // cause unpredictable programme behaviour.
                    // Also, this function runs in an endless loop and would produce huge log files.
                    // log_terminated_message((void*) DEBUG_LEVEL_LOG_MODEL, (void*) L"Sense gnu/linux console message.");

                    // Lock gnu/linux console mutex.
                    //
                    // CAUTION! This lock has to stand not only before the interrupt request is set below,
                    // BUT ALSO BEFORE the next character is detected in the input stream!
                    //
                    // This is because the main thread might be reading characters from the
                    // input stream right now in parallel, while this thread tries to read as well.
                    //
                    // This was tested out and lead to errors, because the "ungetwc" function below
                    // was unexpectedly putting back a character such as ^ (escape) or [
                    // which (in the case of escape) caused the programme to exit
                    // and other inputs like arrow down not to be recognised properly.
                    pthread_mutex_lock(mt);

                    // Get character from gnu/linux console input stream,
                    // just to detect that some (event) character is available.
                    // This is also called "peeking ahead" at the input.
                    //
                    // CAUTION! Use 'wint_t' instead of 'int' as return type for
                    // 'getwchar()', since that returns 'WEOF' instead of 'EOF'!
                    wint_t c = fgetwc(is);

                    if (c == WEOF) {

                        // No valid character was returned.

                        // Sleep for some time.
                        // This is to give the central processing unit (cpu) some
                        // time to breathe, that is to be idle or to process other signals.
                        sleep(*st);

                    } else {

                        // Unread character, that is push it back on the stream to
                        // make it available to be input again from the stream, by the
                        // next call to fgetc or another input function on that stream.
                        //
                        // If c is EOF, ungetc does nothing and just returns EOF.
                        // This lets you call ungetc with the return value of getc
                        // without needing to check for an error from getc.
                        //
                        // The character that you push back doesn't have to be the same
                        // as the last character that was actually read from the stream.
                        // In fact, it isn't necessary to actually read any characters
                        // from the stream before unreading them with ungetc!
                        // But that is a strange way to write a program;
                        // usually ungetc is used only to unread a character that was
                        // just read from the same stream.
                        //
                        // The GNU C library only supports one character of pushback.
                        // In other words, it does not work to call ungetc twice without
                        // doing input in between.
                        // Other systems might let you push back multiple characters;
                        // then reading from the stream retrieves the characters in the
                        // reverse order that they were pushed.
                        //
                        // Pushing back characters doesn't alter the file;
                        // only the internal buffering for the stream is affected.
                        // If a file positioning function (such as fseek, fseeko or rewind)
                        // is called, any pending pushed-back characters are discarded.
                        //
                        // Unreading a character on a stream that is at end of file
                        // clears the end-of-file indicator for the stream, because it
                        // makes the character of input available.
                        // After you read that character, trying to read again will
                        // encounter end of file.
                        ungetwc(c, is);

                        // Set gnu/linux console interrupt request to indicate
                        // that a message has been received via gnu/linux console,
                        // which may now be processed in the main thread of this system.
                        *irq = *NUMBER_1_INTEGER_MEMORY_MODEL;
                    }

                    // Unlock gnu/linux console mutex.
                    pthread_mutex_unlock(mt);

                    while (*irq != *NUMBER_0_INTEGER_MEMORY_MODEL) {

                        // Sleep as long as the gnu/linux console interrupt is not handled and reset yet.
                        //
                        // This is to give the central processing unit (cpu) some
                        // time to breathe, that is to be idle or to process other signals.
                        //
                        // Also, many character inputs are processed at once in the main thread
                        // and only if there are no further characters to be read, the irq flag is reset,
                        // so that this endless loop can be left and new inputs detected.
                        sleep(*st);
                    }

                } else {

                    // CAUTION! DO NOT log this function call!
                    // This function is executed within a thread, but the
                    // logging is not guaranteed to be thread-safe and might
                    // cause unpredictable programme behaviour.
                    // log_terminated_message((void*) ERROR_LEVEL_LOG_MODEL, (void*) L"Could not sense gnu/linux console message. The interrupt is null.");
                }

            } else {

                // CAUTION! DO NOT log this function call!
                // This function is executed within a thread, but the
                // logging is not guaranteed to be thread-safe and might
                // cause unpredictable programme behaviour.
                // log_terminated_message((void*) ERROR_LEVEL_LOG_MODEL, (void*) L"Could not sense gnu/linux console message. The mutex is null.");
            }

        } else {

            // CAUTION! DO NOT log this function call!
            // This function is executed within a thread, but the
            // logging is not guaranteed to be thread-safe and might
            // cause unpredictable programme behaviour.
            // log_terminated_message((void*) ERROR_LEVEL_LOG_MODEL, (void*) L"Could not sense gnu/linux console message. The sleep time is null.");
        }

    } else {

        // CAUTION! DO NOT log this function call!
        // This function is executed within a thread, but the
        // logging is not guaranteed to be thread-safe and might
        // cause unpredictable programme behaviour.
        // log_terminated_message((void*) ERROR_LEVEL_LOG_MODEL, (void*) L"Could not sense gnu/linux console message. The input stream is null.");
    }
}