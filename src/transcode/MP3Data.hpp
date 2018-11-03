/*
 * MP3Data.hpp
 *
 *  Created on: 2 May 2018
 *      Author: julianporter
 */

#ifndef LIB_MP3DATA_HPP_
#define LIB_MP3DATA_HPP_

/*

#include "base.hpp"
#include <lame/lame.h>
#include "ID3Header.hpp"

namespace pylame { namespace mp3 {



class MP3Parameters {
private:
	id3::ID3Header id3;
	int copyright;
	int original;

	unsigned quality;
	unsigned rate;

	bool has(const id3::ID3Field tag) const;

public:
	using iterator=id3::ID3Header::iterator;
	using const_iterator=id3::ID3Header::const_iterator;

	MP3Parameters(const unsigned q=5,const unsigned r=64);
	MP3Parameters(const id3::ID3Header &id3,const unsigned q=5,const unsigned r=8);
	MP3Parameters(const MP3Parameters &) = default;
	MP3Parameters & operator=(const MP3Parameters &) = default;
	virtual ~MP3Parameters() = default;

	void set(const id3::ID3Field &tag,const std::string &s);
	void isCopyright(const bool c)  { copyright=(c) ? 1 : 0; };
	void isOriginal(const bool c)  { original=(c) ? 1 : 0; };


	unsigned Quality() const { return quality; }
	unsigned Rate() const { return rate; }
	void setQuality(const unsigned q)  { quality=q; }
	void setRate(unsigned r)  { rate=r; }

	iterator begin() { return id3.begin(); }
	iterator end() { return id3.end(); }
	const_iterator cbegin() const { return id3.cbegin(); }
	const_iterator cend() const { return id3.cend(); }

	unsigned size() const { return id3.size(); }
	const char * data() { return id3.bytes(); }


	void write(lame_global_flags *gf);
};



}}


*/



#endif /* LIB_MP3DATA_HPP_ */
