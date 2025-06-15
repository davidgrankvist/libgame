#ifndef logger_h
#define logger_h

// enables console output
InitLogger();

// internal util for asserts
void LogAssert(const char* file, int line, const char* format, ...);

#endif
