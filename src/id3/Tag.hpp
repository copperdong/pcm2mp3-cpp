/*
 * Tag.hpp
 *
 *  Created on: 28 Oct 2018
 *      Author: julianporter
 */

#ifndef PCM2MP3_CPP_SRC_ID3_TAG_HPP_
#define PCM2MP3_CPP_SRC_ID3_TAG_HPP_

#include <map>
#include <string>
#include <taglib/tag.h>
#include <taglib/id3v1tag.h>
#include <taglib/id3v2tag.h>
#include <memory>
#include <vector>
#include <type_traits>
#include <iostream>
#include <taglib/tstring.h>
#include <taglib/tbytevector.h>

namespace id3 {

using ID3v1 = TagLib::ID3v1::Tag;
using ID3v2 = TagLib::ID3v2::Tag;

enum class ID3Field {
	Title,
	Artist,
	Album,
	Comment,
	Genre,
	Year,
	Track
};

class FieldValue {
private:
	bool isInt;
	std::string s;
	unsigned u;

public:
	FieldValue() : s(), u(0), isInt(true) {}
	FieldValue(const std::string &s_) : s(s_), u(0), isInt(false) {}
	FieldValue(const unsigned u_) : s(), u(u_), isInt(true) {}
	virtual ~FieldValue() = default;

	operator unsigned() const { return u; }
	operator std::string() const { return s; }
	operator TagLib::String() const { return TagLib::String(s); }

	std::ostream & out(std::ostream &o) const {
		o << (isInt ? u : s);
		return o;
	}
};




class Tag {

public:
	using map_t = std::map<ID3Field,FieldValue>;
	using iterator = map_t::iterator;
	using const_iterator = map_t::const_iterator;

private:
	map_t fields;




public:


	Tag() : fields() {};
	Tag(const Tag&) = default;
	virtual ~Tag() = default;

	void set(const ID3Field &f,const unsigned u) { fields[f]=FieldValue(u); };
	void set(const ID3Field &f,const std::string &s) { fields[f]=FieldValue(s); };

	iterator begin() { return fields.begin(); }
	iterator end() { return fields.end(); }
	iterator cbegin() const { return fields.cbegin(); }
	iterator cend() const { return fields.cend(); }

	unsigned size() const { return fields.size(); }
	bool empty() const { return fields.size()==0; }
	bool has(const ID3Field &f) const { return fields.find(f)!=fields.end(); }
	void clear() { fields.clear(); }

	template<typename tag_t,
		class = typename std::enable_if<std::is_same<ID3v1,tag_t>::value || std::is_same<ID3v2,tag_t>::value>::type>
	std::vector<char> publish() const {
		tag_t tag;
		for(auto it=fields.begin();it!=fields.end();it++) {
			auto field=it->first;
			auto value=it->second;

			switch(field) {
			case ID3Field::Title:
				tag.setTitle(value);
				break;
			case ID3Field::Artist:
				tag.setArtist(value);
				break;
			case ID3Field::Album:
				tag.setAlbum(value);
				break;
			case ID3Field::Comment:
				tag.setComment(value);
				break;
			case ID3Field::Genre:
				tag.setGenre(value);
				break;
			case ID3Field::Year:
				tag.setYear(value);
				break;
			case ID3Field::Track:
				tag.setTrack(value);
				break;
			}
		}
		TagLib::ByteVector bytes=tag.render();
		return std::vector<char>(bytes.begin(),bytes.end());
	}

	template<typename tag_t,
			class = typename std::enable_if<std::is_same<ID3v1,tag_t>::value || std::is_same<ID3v2,tag_t>::value>::type>
	void dump() {
		auto v=publish<tag_t>();
		for(auto i=0;i<v.size();++i) {
			auto c=v[i];
			std::string pad=(c<16) ? "0" : "";
			std::cout << pad << std::hex << (unsigned)c;
			if(i==7) std::cout << std::endl;
			else std::cout << " ";
		}
		if(0!=(v.size()%8)) std::cout << std::endl;
	}




};

} /* namespace id3 */

std::ostream & operator<<(std::ostream &o,const id3::ID3Field &f);
std::ostream & operator<<(std::ostream &o,const id3::Tag &t);
std::ostream & operator<<(std::ostream &o,const id3::FieldValue &fv);

#endif /* PCM2MP3_CPP_SRC_ID3_TAG_HPP_ */
