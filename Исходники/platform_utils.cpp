        time_t IgniteTimeGm(const tm& time)
        {
            tm tmc = time;

            return _mkgmtime(&tmc);
        }