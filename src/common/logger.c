/*
 * This logger is a simple printf wrapper. The reason for wrapping is mainly to
 * make console printing work when using dynamic linking.
 *
 * The freopen call is used to set up standard streams so we can ouput to an attached console.
 * The issue is that the freopen state is not global across binaries. When we call
 * it here, that doesn't set up printf to work in the game code. However if we do
 * the printf statements within the scope of this library, then they use the correct state.
 */

#include <stdarg.h>
#include <stdio.h>
#include "libgame.h"
#include "asserts.h"

LogLevel logLevel = LOG_INFO;

void InitLogger() {
    FILE* result = NULL;

    result = freopen("CONOUT$", "w", stdout);
    Assert(result != NULL, "Failed to configure STDOUT");

    result = freopen("CONOUT$", "w", stderr);
    Assert(result != NULL, "Failed to configure STDERR");

    result = freopen("CONOUT$", "r", stdin);
    Assert(result != NULL, "Failed to configure STDIN");
}

void SetLogLevel(LogLevel level) {
    logLevel = level;
}

static const char* MapLevelToString(LogLevel level) {
    switch(level) {
        case LOG_DEBUG:
            return "DEBUG";
        case LOG_INFO:
            return "INFO";
        case LOG_WARNING:
            return "WARNING";
        case LOG_ERROR:
            return "ERROR";
        default:
            AssertFail("Failed to map log level to string. Unknown log level %d", level);
            return "UNKNOWN";
    }
}

void Log(LogLevel level, const char* format, ...) {
    if (level < logLevel) {
       return;
    }

    const char* levelPrefix = MapLevelToString(level);

    va_list args;
    va_start(args, format);

    if (level >= LOG_ERROR) {
        fprintf(stderr, "%s: ", levelPrefix);
        vfprintf(stderr, format, args);
    } else {
        fprintf(stdout, "%s: ", levelPrefix);
        vfprintf(stdout, format, args);
    }

    va_end(args);
}

 #define DECLARE_LOG_FN(name, level) \
     void name(const char* format, ...) { \
         va_list args; \
         va_start(args, format); \
         Log(level, format, args); \
         va_end(args); \
     }

DECLARE_LOG_FN(LogDebug, LOG_DEBUG)
DECLARE_LOG_FN(LogInfo, LOG_INFO)
DECLARE_LOG_FN(LogWarning, LOG_WARNING)
DECLARE_LOG_FN(LogError, LOG_ERROR)

void LogAssert(const char* file, int line, const char* format, ...) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "ASSERT: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n    at %s:%d\n", file, line);
    va_end(args);
}
