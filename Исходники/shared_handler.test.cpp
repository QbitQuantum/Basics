    void run()
    {
    #if ! BEAST_NO_STD_FUNCTION_CONSTRUCTIBLE
        static_assert (! std::is_constructible <
            std::function <void(void)>, int&&>::value,
                "Cannot construct std::function from int&&");

        static_assert (! std::is_constructible <
            std::function <void(void)>, int>::value,
                "Cannot construct std::function from int");

        static_assert (! std::is_constructible <
            asio::shared_handler <void(void)>, int>::value,
                "Cannot construct shared_handler from int");
    #endif

        static_assert (std::is_constructible <
            asio::shared_handler <void(int)>,
                asio::shared_handler <void(int)>>::value,
                    "Should construct <void(int)> from <void(int)>");

        static_assert (! std::is_constructible <
            asio::shared_handler <void(int)>,
                asio::shared_handler <void(void)>>::value,
                    "Can't construct <void(int)> from <void(void)>");

        // Hooks called when using the raw handler
        {
            test_results r;
            test_handler h (r);

            async_op (h);
            expect (r.call);
            expect (r.alloc);
            expect (r.dealloc);
            expect (r.cont);

            test_invokable f;
            boost_asio_handler_invoke_helpers::invoke (std::ref (f), h);
            expect (r.invoke);
            expect (f.call);
        }

        // Use of std::function shows the hooks not getting called
        {
            test_results r;
            std::function <void(void)> fh ((test_handler) (r));

            async_op (fh);
            expect (r.call);
            unexpected (r.alloc);
            unexpected (r.dealloc);
            unexpected (r.cont);

            test_invokable f;
            boost_asio_handler_invoke_helpers::invoke (std::ref (f), fh);
            unexpected (r.invoke);
            expect (f.call);
        }

        // Make sure shared_handler calls the hooks
        {
            test_results r;
            asio::shared_handler <void(void)> sh ((test_handler)(r));

            async_op (sh);
            expect (r.call);
            expect (r.alloc);
            expect (r.dealloc);
            expect (r.cont);

            test_invokable f;
            boost_asio_handler_invoke_helpers::invoke (std::ref (f), sh);
            expect (r.invoke);
            expect (f.call);
        }

        // Make sure shared_handler via implicit conversion calls hooks
        {
            test_results r;
            test_handler h (r);

            virtual_async_op ((test_handler) (r));
            expect (r.call);
            expect (r.alloc);
            expect (r.dealloc);
            expect (r.cont);
        }
    }