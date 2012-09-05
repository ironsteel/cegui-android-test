#ifndef CEGUIANDROIDLOGGER_H
#define CEGUIANDROIDLOGGER_H

#include <CEGUI/Logger.h>
#include <android/log.h>
using namespace CEGUI;

#define LOG(...) ((void)__android_log_print(ANDROID_LOG_INFO, "CEGUI", __VA_ARGS__))

class AndroidLogger : public Logger
{
public:
    AndroidLogger(void);
    ~AndroidLogger(void);
    
    void setLogFilename(const String &filename, bool append);
    void logEvent(const String &message, LoggingLevel level);
    
    
};


#endif // CEGUIANDROIDLOGGER_H
