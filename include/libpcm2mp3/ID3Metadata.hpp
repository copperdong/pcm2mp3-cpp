/*
 * Metadata.hpp
 *
 *  Created on: 28 Oct 2018
 *      Author: julianporter
 */

#ifndef PCM2MP3_CPP_SRC_ID3_ID3METADATA_HPP_
#define PCM2MP3_CPP_SRC_ID3_ID3METADATA_HPP_

#include <string>
#include <iostream>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <taglib/tpropertymap.h>
#include <taglib/id3v1tag.h>
#include <taglib/id3v2tag.h>
#include <taglib/tstring.h>
#include <taglib/tstringlist.h>



namespace pylame { namespace id3 {

using str_t = TagLib::String;

enum class ID3Field : unsigned {
	Title = 1,
	Artist = 2,
	Album = 3,
	Comment = 4,
	Genre = 5,
	Year = 6,
	Date = 7,
	Track = 8,
	TermsOfUse = 9,
	MediaType = 10,
	Copyright = 11,
	Duration =12,
	Unknown = 255
};







class Metadata {
public:
	using map_t=TagLib::PropertyMap;
	using iterator = map_t::Iterator;
	using const_iterator = map_t::ConstIterator;
private:

	map_t fields;



public:
	static std::map<ID3Field,str_t> id3str;
	static ID3Field field(const std::string &name);

	Metadata() : fields() {};
	Metadata(const Metadata &) = default;
	Metadata &operator=(const Metadata &) = default;
	virtual ~Metadata() = default;


	iterator begin() { return fields.begin(); }
	iterator end() { return fields.end(); }
	const_iterator cbegin() const { return fields.begin(); }
	const_iterator cend() const { return fields.end(); }

	unsigned size() const { return fields.size(); }
	bool empty() const { return fields.isEmpty(); }

	bool has(const ID3Field &f) const { return fields.contains(id3str[f]); }

	void set(const std::string &k,const std::string &v) { fields[str_t(k)]=str_t(v); }
	void set(const ID3Field &k,const std::string &v) { fields[id3str[k]]=str_t(v); }


	template<typename T,class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	void set(const ID3Field &k,const T v) { set(k,std::to_string(v)); }

	template<typename T,class = typename std::enable_if<std::is_arithmetic<T>::value>::type>
	void set(const std::string &k,const T v) { set(k,std::to_string(v)); }




	void clean() { fields.removeEmpty(); }

	using ID3v1 = TagLib::ID3v1::Tag;
	using ID3v2 = TagLib::ID3v2::Tag;
	struct ID3vX { ID3vX(){}; };

	template<int N>
	using id3_t = typename std::conditional<N==1,ID3v1,typename std::conditional<N==2,ID3v2,ID3vX>::type>::type;


	template<const int version,class tag_t = id3_t<version>>
	std::vector<char> publish() const {
		tag_t tag;
		TagLib::StringList unsupported=fields.unsupportedData();
		tag.setProperties(fields);
		tag.removeUnsupportedProperties(unsupported);

		TagLib::ByteVector bytes=tag.render();
		return std::vector<char>(bytes.begin(),bytes.end());
	}


};

}} /* namespace id3 */




#endif /* PCM2MP3_CPP_SRC_ID3_ID3METADATA_HPP_ */
