        ~Private()
        {
            if (userInfo)
                NetApiBufferFree(userInfo);

            delete[] sid;
        }