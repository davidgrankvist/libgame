#include <stdio.h>
#include "platform_setup.h"
#include "asserts.h"

PlatformConsole platformConsole = {};

void InitPlatformConsole(PlatformConsole pfc) {
    platformConsole = pfc;

    if (getenv("DEBUG_CONSOLE")) {
        InitConsole();
    }
}

static void InitConsoleLogger() {
    FILE* result = NULL;

    result = freopen(platformConsole.stdoutName, "w", stdout);
    Assert(result != NULL, "Failed to configure STDOUT");

    result = freopen(platformConsole.stderrName, "w", stderr);
    Assert(result != NULL, "Failed to configure STDERR");

    result = freopen(platformConsole.stdinName, "r", stdin);
    Assert(result != NULL, "Failed to configure STDIN");
}

void InitConsole() {
    platformConsole.AttachConsole();
    InitConsoleLogger();
}
