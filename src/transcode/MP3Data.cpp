/*
 * MP3Data.cpp
 *
 *  Created on: 2 May 2018
 *      Author: julianporter
 */

/*

#include "MP3Data.hpp"
#include <chrono>
#include <ctime>

namespace pylame { namespace mp3 {


bool MP3Parameters::has(const id3::ID3Field tag) const {
	return id3.has(tag);
}

MP3Parameters::MP3Parameters(const id3::ID3Header &id3_,const unsigned q,const unsigned r) :
		id3(id3_), original(false), quality(q),rate(r) {

	if(!id3.has(id3::ID3Field::Comment))
		id3.set(id3::ID3Field::Comment,"Converted by pcm2mp3 (c) JP Embedded Solutions 2018)");
	if(!id3.has(id3::ID3Field::Copyright))
			id3.set(id3::ID3Field::Copyright,"Lore Lixenberg 2018, all rights reserved");

	copyright=id3.has(id3::ID3Field::Copyright);

}

MP3Parameters::MP3Parameters(const unsigned q,const unsigned r) : MP3Parameters(id3::ID3Header(id3::ID3Version::ID3v2),q,r) {}


void MP3Parameters::set(const id3::ID3Field &tag,const std::string &s) {
	id3.set(tag,s);
	if(tag==id3::ID3Field::Copyright) copyright=true;
};


void MP3Parameters::write(lame_global_flags *gf) {

	lame_set_copyright(gf,copyright);
	lame_set_original(gf,original);
	id3.publish();



}

}}


*/
