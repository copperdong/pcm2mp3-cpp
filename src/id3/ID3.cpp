/*
 * ID3Header.cpp
 *
 *  Created on: 29 Oct 2018
 *      Author: julianporter
 */

#include "ID3.hpp"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tstring.h>
#include <taglib/tpropertymap.h>

namespace  id3 {



ID3::ID3(const std::string &filename) : fields() {
	auto file = TagLib::FileRef(filename.c_str());
	auto props = file.tag()->properties();
	for(auto it=props.begin();it!=props.end();++it) {
		auto key=it->first.to8Bit();
		auto value=it->second.toString().to8Bit();
		fields[key]=value;
	}
}

std::string ID3::operator[](const std::string &key) const {
	return fields.at(key);
}
bool ID3::has(const std::string &key) const {
	return fields.find(key) != fields.end();
}

std::vector<std::string> ID3::keys() const {
	std::vector<std::string> k;
	for(auto it=fields.begin();it!=fields.end();++it) {
		k.push_back(it->first);
	}
	return k;
}

}

std::ostream &operator<<(std::ostream &o,const id3::ID3 &hdr) {
	for(auto it=hdr.cbegin();it!=hdr.cend();++it) {
		o << it->first << ": " << it->second << std::endl;
	}
	return o;
}

