#pragma once
#include <ctime>
#include <string>

using std::string;
namespace Engine {
	static std::string getCurrentDateTime() {
		std::time_t now = std::time(nullptr);
		char buffer[26];
		if (ctime_s(buffer, sizeof(buffer), &now) != 0) {
			return "Error getting time";
		}
		buffer[24] = '\0';
		return std::string(buffer);
	}
}