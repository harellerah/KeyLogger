// encrypt.h
#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <windows.h>

// Encrypts input buffer using DPAPI
// Caller provides input buffer + size
// Output is a DATA_BLOB (allocated)
int encrypt_buffer(const BYTE *input, DWORD inputSize, DATA_BLOB *output);

#endif
