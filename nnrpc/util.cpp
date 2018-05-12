#include "util.h"
#include <functional>

namespace util
{
	uint64_t strhash(const std::string &str)
	{
		std::hash<std::string> hs;
		return hs(str);
	}
}
