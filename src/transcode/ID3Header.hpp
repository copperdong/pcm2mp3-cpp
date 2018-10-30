/*
 * ID3Header.hpp
 *
 *  Created on: 29 Oct 2018
 *      Author: julianporter
 */

#ifndef PCM2MP3_CPP_SRC_ID3_ID3HEADER_HPP_
#define PCM2MP3_CPP_SRC_ID3_ID3HEADER_HPP_

#include "ID3Metadata.hpp"
#include "Time.hpp"

namespace pylame { namespace id3 {

enum class ID3Version : unsigned {
	ID3v1 = 1,
	ID3v2 = 2,
	ID3v1v2 = 3
};

class ID3Header {
private:
	ID3Version version;
	Metadata metadata;
	std::vector<char> data;

public:
	using iterator = std::vector<char>::iterator;
	using const_iterator = std::vector<char>::const_iterator;

	ID3Header(const ID3Version v=ID3Version::ID3v1v2);
	ID3Header(const std::string &title,const std::string &copyright,const ID3Version v=ID3Version::ID3v1v2);
	ID3Header(const ID3Header &) = default;
	ID3Header &operator=(const ID3Header &) = default;
	virtual ~ID3Header() = default;

	void set(const ID3Field &f,const std::string &v) ;
	void set(const ID3Field &f,const double v) ;
	void set(const std::string &k,const std::string &v);
	void set(const std::string &k,const double v);

	void comment(const std::string &s) ;
	void terms(const std::string &s) ;
	bool has(const ID3Field &f) const;

	std::vector<char> publish();

	iterator begin() { return data.begin(); }
	iterator end() { return data.end(); }
	const_iterator cbegin() const { return data.begin(); }
	const_iterator cend() const { return data.end(); }

	unsigned size() const { return data.size(); }
	bool empty() const { return data.empty(); }
	const char *bytes() { return data.data(); }


};

}} /* namespace id3 */

#endif /* PCM2MP3_CPP_SRC_ID3_ID3HEADER_HPP_ */
