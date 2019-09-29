/*
 * ID3Frame.cpp
 *
 *  Created on: 29 Sep 2019
 *      Author: julianporter
 */

#include <id3/ID3Frame.hpp>

namespace id3 {

SyncSafeInteger::SyncSafeInteger(const uint32_t u) : i32(u) {
		auto v=u;
		for(auto i=0;i<4;i++) {
			i8[3-i]=(char)(v&127);
			v>>=7;
		}
	}
SyncSafeInteger::SyncSafeInteger(char *b) {
		uint32_t v=0;
		for(auto i=0;i<4;i++) {
			i8[i]=b[i];
			v=(v<<7) + (127 & (uint32_t)b[i]);
		}
		i32=v;
	}

const uint8_t ID3Flags::unsynchronisation = 0b10000000;
const uint8_t ID3Flags::extendedHeader = 0b01000000;
const uint8_t ID3Flags::experimental      = 0b00100000;
const uint8_t ID3Flags::footer         = 0b00010000;

const std::string ID3Frame::tagString="ID3";

ID3Frame ID3Frame::find(const mdata_t &data) {
	auto offset=0;
	while(offset<data.size()-10) {
		try {
			ID3Frame f(data,offset);
			if(f.check()) return f;
		}
		catch(...) {}
		offset+=1;
	}
	throw std::runtime_error("No ID3");
}


ID3Frame::ID3Frame(const mdata_t &data,const unsigned o) : offset(o) {
	auto ptr=data.begin()+offset;
	std::copy_n(ptr,10,header);

	tag=std::string(header,3);
	version=std::make_pair((unsigned)header[3],(unsigned)header[4]);
	flags=ID3Flags(header[5]);
	length=SyncSafeInteger(header+6);
}

bool ID3Frame::check() const {
	if(tag!=ID3Frame::tagString) return false;
	if(!version) return false;
	if(!flags) return false;
	if(std::any_of(header+6,header+10,[](auto c) { return 127 < (unsigned)c; })) return false;
	return true;
}


} /* namespace id3 */

std::ostream & operator<<(std::ostream &o,const id3::ID3Frame &f) {
	o << "Version " << (std::string)f.version << std::endl;
	o << "Flags " << std::hex << (unsigned)f.flags << std::endl;
	o << "Length " << std::dec << f.length << std::endl;
	return o;
}
