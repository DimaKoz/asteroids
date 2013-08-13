#ifndef _GM_SERV_LOG_HPP_
#define _GM_SERV_LOG_HPP_

namespace gm_serv {
class Log {
public:
	static void error(const char* pMessage, ...);
	static void warn(const char* pMessage, ...);
	static void debug(const char* pMessage, ...);
	static void info(const char* pMessage, ...);

};
}

#ifndef NDEBUG
#define gm_serv_Log_debug(...) gm_serv::Log::debug(__VA_ARGS__)
#else
#define gm_serv_Log_debug(...)
#endif

#endif
