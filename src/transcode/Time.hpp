/*
 * Time.hpp
 *
 *  Created on: 29 Oct 2018
 *      Author: julianporter
 */

#ifndef PCM2MP3_CPP_SRC_ID3_TIME_HPP_
#define PCM2MP3_CPP_SRC_ID3_TIME_HPP_

#include <string>

namespace pylame {

class Time {
private:
	using ts_t = struct tm *;
	static const unsigned MaxLength;
	static const char *format;
	static time_t timer();
	static ts_t utcnow();

public:
	static std::string timestamp();
	static unsigned year();
};

} /* namespace id3 */

#endif /* PCM2MP3_CPP_SRC_ID3_TIME_HPP_ */
