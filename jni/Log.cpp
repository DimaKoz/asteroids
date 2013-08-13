#include "Log.hpp"

#include <stdarg.h>
#include <android/log.h>

namespace gm_serv {
void Log::info(const char* pMessage, ...) {
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_INFO, "dima_koz", pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_INFO, "dima_koz", "\n");
	va_end(lVarArgs);
}

void Log::error(const char* pMessage, ...) {
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_ERROR, "dima_koz", pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_ERROR, "dima_koz", "\n");
	va_end(lVarArgs);
}

void Log::warn(const char* pMessage, ...) {
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_WARN, "dima_koz", pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_WARN, "dima_koz", "\n");
	va_end(lVarArgs);
}

void Log::debug(const char* pMessage, ...) {
	va_list lVarArgs;
	va_start(lVarArgs, pMessage);
	__android_log_vprint(ANDROID_LOG_DEBUG, "dima_koz", pMessage, lVarArgs);
	__android_log_print(ANDROID_LOG_DEBUG, "dima_koz", "\n");
	va_end(lVarArgs);
}
}
