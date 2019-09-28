/*
 * ID3Header.hpp
 *
 *  Created on: 29 Oct 2018
 *      Author: julianporter
 */

#ifndef PCM2MP3_CPP_SRC_ID3_ID3HEADER_HPP_
#define PCM2MP3_CPP_SRC_ID3_ID3HEADER_HPP_


#include <iostream>
#include <map>

namespace id3 {




class ID3 {
private:

	std::map<std::string,std::string> fields;

public:
	using iterator = std::map<std::string,std::string>::iterator;
	using const_iterator = std::map<std::string,std::string>::const_iterator;
	ID3(const std::string &filename);
	virtual ~ID3() = default;

	std::string operator[](const std::string &key) const;
	bool has(const std::string &key) const;
	std::vector<std::string> keys() const;

	iterator begin() { return fields.begin(); }
	iterator end() { return fields.end(); }
	const_iterator cbegin() const { return fields.cbegin(); }
	const_iterator cend() const { return fields.cend(); }
	unsigned size() const { return fields.size(); }

};

} /* namespace id3 */


std::ostream &operator<<(std::ostream &o,const id3::ID3 &hdr);

#endif /* PCM2MP3_CPP_SRC_ID3_ID3HEADER_HPP_ */
