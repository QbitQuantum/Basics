size_t zLog::print(const string& status, const string& classname, const list<string>& buf) const
{
#if defined(_WIN32)
 return write(buf);
#else
#if defined(__GNUG__) || defined(__CYGWIN__) || defined(__linux__)
 if(buf.size() == 0) return 0;
 string q;
 time_t ltime = ::time(NULL);
 struct tm tmtime;
#if defined(_WIN32)
 localtime_s(&tmtime,&ltime);
#else
#if defined(__GNUG__) || defined(__CYGWIN__) || defined(__linux__)
 localtime_r(&ltime, &tmtime);
#endif // _WIN32
#endif // __GNUG__
 q+='[';
 if(tmtime.tm_mday < 10) q+='0';
 q+=ZNSTR::toString(static_cast<int>(tmtime.tm_mday));
 q+='/';
 if(tmtime.tm_mon < 10) q+='0';
 q+=ZNSTR::toString(static_cast<int>(tmtime.tm_mon));
 q+='/';
// if(tmtime.tm_year < 10) q+='0';
 q+=ZNSTR::toString(static_cast<int>(tmtime.tm_year));
 q+=' ';

 if(tmtime.tm_hour < 10) q+='0';
 q+=ZNSTR::toString(static_cast<int>(tmtime.tm_hour));
 q+=':';
 if(tmtime.tm_min < 10) q+='0';
 q+=ZNSTR::toString(static_cast<int>(tmtime.tm_min));
 q+=':';
 if(tmtime.tm_sec < 10) q+='0';
 q+=ZNSTR::toString(static_cast<int>(tmtime.tm_sec));

 q+="] "+status+' '+classname+' ';
 string s;
 for(list<string>::const_iterator k=buf.begin(); k != buf.end(); ++k) { s+=(q+*k); }
 return write(s);
#endif // _WIN32
#endif // __GNUG__
};