static inline void clearTimesWithDynamicOrigins(Vector<SMILTimeWithOrigin>& timeList)
{
    for (int i = timeList.size() - 1; i >= 0; --i) {
        if (timeList[i].originIsScript())
            timeList.remove(i);
    }
}