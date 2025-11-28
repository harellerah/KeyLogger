// encrypt.c
#define _WIN32_WINNT 0x0601
#include "encrypt.h"
#include <wincrypt.h>

int encrypt_buffer(const BYTE *input, DWORD inputSize, DATA_BLOB *output) {
    // TODO:
    // - Prepare input DATA_BLOB
    // - Call CryptProtectData()
    // - Fill output DATA_BLOB
    // - Return success/failure
    DATA_BLOB inputBlob;
    inputBlob.pbData = (BYTE *)input;
    inputBlob.cbData = inputSize;
    if (!CryptProtectData(&inputBlob, NULL, NULL, NULL, NULL, 0, output)) {
        return 0; // failure
    }
    return 1; // success
}
