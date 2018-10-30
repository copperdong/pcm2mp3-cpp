/*
 * Time.cpp
 *
 *  Created on: 29 Oct 2018
 *      Author: julianporter
 */

#include "Time.hpp"
#include <chrono>
#include <ctime>

namespace id3 {

	const unsigned Time::MaxLength=80;
	const char *Time::format="%FT%T";

	time_t Time::timer() {
		time_t t;
		std::time(&t);
		return t;
	}

	Time::ts_t Time::utcnow() {
	auto t=timer();
	return std::gmtime(&t);
}

std::string Time::timestamp() {
	char buffer[MaxLength];

	std::strftime(buffer,MaxLength,format,utcnow());
	return std::string(buffer);
}

unsigned Time::year() {
	return (unsigned)utcnow()->tm_year;
}

} /* namespace id3 */
