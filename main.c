// main.c
#include <windows.h>
#include "hook.h"
#include "logger.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrev, PWSTR cmd, int show) {
    // TODO: initialize logger (open file, etc.)
    logger_init();

    // TODO: install keyboard hook
    if (!install_keyboard_hook()) {
        // TODO: handle hook install failure
        return 1;
    }

    // Standard Windows message loop (required for hook to run)
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        // No need to process messages, just dispatch
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // TODO: cleanup
    uninstall_keyboard_hook();
    logger_cleanup();

    return 0;
}

int main() {
    return wWinMain(GetModuleHandle(NULL), NULL, GetCommandLineW(), SW_SHOW);
}
