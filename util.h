// util.h
#ifndef UTIL_H
#define UTIL_H

#include <windows.h>
#include <wchar.h>

void util_get_timestamp(wchar_t *buf, int bufSize);

void util_get_active_window_title(wchar_t *buf, int bufSize);

void util_vkey_to_string(DWORD vkCode, wchar_t *buf, int bufSize);

#endif
