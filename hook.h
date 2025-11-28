// hook.h
#ifndef HOOK_H
#define HOOK_H

#include <windows.h>

// Install the WH_KEYBOARD_LL hook
int install_keyboard_hook(void);

// Remove the hook
void uninstall_keyboard_hook(void);

// Hook procedure (callback)
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

#endif
