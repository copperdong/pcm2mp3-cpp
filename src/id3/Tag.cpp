/*
 * Tag.cpp
 *
 *  Created on: 28 Oct 2018
 *      Author: julianporter
 */

#include <id3/Tag.hpp>

std::ostream & operator<<(std::ostream &o,const id3::FieldValue &fv) {
	return fv.out(o);
}

std::ostream & operator<<(std::ostream &o,const id3::ID3Field &f) {
	switch(f) {
	case id3::ID3Field::Title:
		o << "Title";
		break;
	case id3::ID3Field::Artist:
		o << "Artist";
		break;
	case id3::ID3Field::Album:
		o << "Album";
		break;
	case id3::ID3Field::Comment:
		o << "Comment";
		break;
	case id3::ID3Field::Genre:
		o << "Genre";
		break;
	case id3::ID3Field::Year:
		o << "Year";
		break;
	case id3::ID3Field::Track:
		o << "Track";
		break;
	}
	return o;
}

std::ostream & operator<<(std::ostream &o,const id3::Tag &t) {
	for(auto it=t.cbegin();it!=t.cend();it++) {
		o << it->first << ": " << it->second << std::endl;
	}
	return o;
}
