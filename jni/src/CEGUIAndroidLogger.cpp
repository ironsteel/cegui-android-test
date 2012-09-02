#include "CEGUIAndroidLogger.h"


AndroidLogger::AndroidLogger()
{
}

AndroidLogger::~AndroidLogger()
{
}

void AndroidLogger::logEvent(const String &message, LoggingLevel level)
{
    LOG(message.c_str());
}


void AndroidLogger::setLogFilename(const String &filename, bool append)
{
    // Stub. We re logging to android internal log
}    


