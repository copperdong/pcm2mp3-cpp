/*
 * ID3Frame.hpp
 *
 *  Created on: 29 Sep 2019
 *      Author: julianporter
 */

#ifndef PCM2MP3_CPP_SRC_ID3_ID3FRAME_HPP_
#define PCM2MP3_CPP_SRC_ID3_ID3FRAME_HPP_

#include <cstdint>
#include <string>
#include <vector>
#include <sstream>

namespace id3 {

class SyncSafeInteger {
private:
	uint32_t i32;
	char i8[4];

public:
	SyncSafeInteger(const uint32_t u);
	SyncSafeInteger(char *b);
	virtual ~SyncSafeInteger() = default;
	operator uint32_t() const { return i32; }
	operator char *() const { return i8; }
};

unsigned deSync(char *bytes);

class ID3Flags {
private:
	const static uint8_t unsynchronisation;
	const static uint8_t extendedHeader;
	const static uint8_t experimental;
	const static uint8_t footer;
	uint8_t raw;

public:
	ID3Flags() : raw(0) {};
	ID3Flags(const char c) : raw((uint8_t)c) {};
	virtual ~ID3Flags() = default;

	operator bool() const { return (raw & 0x0f)==0; }
	bool isUnsynchronised() const { return (raw & ID3Flags::unsynchronisation); }
	bool hasExtendedHeader() const { return (raw & ID3Flags::extendedHeader); }
	bool isExperimental() const { return (raw & ID3Flags::experimental); }
	bool hasFooter() const { return (raw & ID3Flags::footer); }

	operator unsigned() const { return raw>>4; }
};

struct ID3Version {
	const unsigned major;
	const unsigned minor;

	ID3Version(const char ma,const char mi) : major(ma), minor(mi) {};
	virtual ~ID3Version() = default;

	operator std::string() const {
		std::stringstream s;
		s << major << "." << minor;
		return s.str();
	}
	operator bool() const {
		return (major != 255) && (minor != 255);
	}
};

class ID3Frame {

private:
	char header[10];
	unsigned offset;
	const static std::string tagString;

	std::string tag;

public:
	using mdata_t = std::vector<char>;

	ID3Version version;
	ID3Flags flags;
	unsigned length;


	ID3Frame(const mdata_t &data,const unsigned o);
	static ID3Frame find(const mdata_t &data);
	virtual ~ID3Frame() = default;

	bool check() const;

};


} /* namespace id3 */

std::ostream & operator<<(std::ostream &o,const id3::ID3Frame &f);

#endif /* PCM2MP3_CPP_SRC_ID3_ID3FRAME_HPP_ */
