#include <stdarg.h>
#include "asserts.h"
#include "logger.h"

void AssertFn(bool b, const char* file, int line, const char* format, ...) {
    if (!b) {
        va_list args;
        va_start(args, format);
        LogAssert(file, line, format, args);
        va_end(args);

        exit(1);
    }
}
