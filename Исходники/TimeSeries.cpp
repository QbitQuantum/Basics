    /// get values between start and end date times
    Vector TimeSeries_Impl::values(const DateTime& startDateTime, const DateTime& endDateTime) const
    {
      boost::optional<int> calendarYear = m_firstReportDateTime.date().baseYear();

      DateTime startDateTimeCompare = startDateTime;
      if (!calendarYear && startDateTime.date().baseYear()){
        startDateTimeCompare = DateTime(Date(startDateTime.date().monthOfYear(), startDateTime.date().dayOfMonth()), startDateTime.time());
      }

      DateTime endDateTimeCompare = endDateTime;
      if (!calendarYear && endDateTime.date().baseYear()){
        endDateTimeCompare = DateTime(Date(endDateTime.date().monthOfYear(), endDateTime.date().dayOfMonth()), endDateTime.time());
      }

      DateTime firstReportDateTimeWithYear = m_firstReportDateTime;
      if (!calendarYear){
        firstReportDateTimeWithYear = DateTime(Date(m_firstReportDateTime.date().monthOfYear(), m_firstReportDateTime.date().dayOfMonth(), m_firstReportDateTime.date().year()), m_firstReportDateTime.time());
      }

      DateTime startDateTimeWithYear = startDateTime;
      if (!startDateTime.date().baseYear()){
        startDateTimeWithYear = DateTime(Date(startDateTime.date().monthOfYear(), startDateTime.date().dayOfMonth(), startDateTime.date().year()), startDateTime.time());
      }

      DateTime endDateTimeWithYear = endDateTime;
      if (!endDateTime.date().baseYear()){
        if (m_wrapAround){
          if (endDateTimeCompare < startDateTimeCompare){
            endDateTimeWithYear = DateTime(Date(endDateTime.date().monthOfYear(), endDateTime.date().dayOfMonth(), endDateTime.date().year() + 1), endDateTime.time());
          }else{
            endDateTimeWithYear = DateTime(Date(endDateTime.date().monthOfYear(), endDateTime.date().dayOfMonth(), endDateTime.date().year()), endDateTime.time());
          }
        }else{
          endDateTimeWithYear = DateTime(Date(endDateTime.date().monthOfYear(), endDateTime.date().dayOfMonth(), endDateTime.date().year()), endDateTime.time());
        }
      }

      double startSecondsFromFirstReport = (startDateTimeWithYear - firstReportDateTimeWithYear).totalSeconds();
      double endSecondsFromFirstReport = (endDateTimeWithYear - firstReportDateTimeWithYear).totalSeconds();

      unsigned numValues = m_values.size();
      OS_ASSERT(numValues == m_secondsFromFirstReport.size());

      Vector result(numValues);
      unsigned resultSize = 0;
      for (unsigned i = 0; i < numValues; ++i){
        if ((m_secondsFromFirstReport[i] >= startSecondsFromFirstReport) &&
            (m_secondsFromFirstReport[i] <= endSecondsFromFirstReport)){
          result[resultSize] = m_values[i];
          ++resultSize;
        }
      }

      result.resize(resultSize, true);

      return result;
    }