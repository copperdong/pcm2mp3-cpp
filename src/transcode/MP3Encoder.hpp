/*
 * MP3Encoder.hpp
 *
 *  Created on: 30 Nov 2017
 *      Author: julianporter
 */

#ifndef MP3ENCODER_HPP_
#define MP3ENCODER_HPP_

#include "PCMFile.hpp"
#include "ID3Header.hpp"
#include <lame/lame.h>
#include "base.hpp"





namespace pylame { namespace mp3 {



class MP3Encoder {
private:
	pcm::file_t data;
	id3::ID3Header parameters;
	unsigned nSamples;
	unsigned mp3Size;
	unsigned id3Size;
	unsigned char *mp3Out;
	lame_global_flags *gf; 
	cdata_t output;
	
	static unsigned mp3SizeCalc(unsigned);

public:
	MP3Encoder() : data(nullptr), parameters(id3::ID3Version::ID3v2), nSamples(0), mp3Size(0), id3Size(0), mp3Out(nullptr), gf(nullptr), output() {};
	MP3Encoder(const pcm::file_t &data_,const unsigned quality,const unsigned rate);
	MP3Encoder(const pcm::file_t &data_,const id3::ID3Header &parameters);
	MP3Encoder(pcm::PCMFile *data_,const id3::ID3Header &parameters);
	virtual ~MP3Encoder();
	
	void transcode();
	unsigned size() { return mp3Size+id3Size; };

	cdata_t::const_iterator cbegin() const { return output.cbegin(); };
	cdata_t::const_iterator cend() const { return output.cend(); };
	unsigned size() const { return mp3Size; };
	const unsigned char *ptr() const { return output.data(); };
	cdata_t & operator()() { return output; };

};

}}

std::ostream & operator<<(std::ostream &o,const pylame::mp3::MP3Encoder &e);



#endif /* MP3ENCODER_HPP_ */
