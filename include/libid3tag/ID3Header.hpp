/*
 * ID3Header.hpp
 *
 *  Created on: 29 Oct 2018
 *      Author: julianporter
 */

#ifndef PCM2MP3_CPP_SRC_ID3_ID3HEADER_HPP_
#define PCM2MP3_CPP_SRC_ID3_ID3HEADER_HPP_

#include "Metadata.hpp"
#include "Time.hpp"

namespace id3 {

enum class ID3Version {
	ID3v1,
	ID3v2,
	ID3v1v2
};

class ID3Header {
private:
	ID3Version version;
	Metadata metadata;

public:
	ID3Header(const ID3Version v=ID3Version::ID3v1v2);
	ID3Header(const std::string &title,const std::string &copyright,const ID3Version v=ID3Version::ID3v1v2);
	ID3Header(const ID3Header &) = default;
	ID3Header &operator=(const ID3Header &) = default;
	virtual ~ID3Header() = default;

	void set(const ID3Field &f,const std::string &v) ;
	void set(const ID3Field &f,const double v) ;
	void set(const std::string &k,const std::string &v);
	void set(const std::string &k,const double v);
	//void set(const ID3Field &f,const char *v) { set(f,std::string(v)); }

	void comment(const std::string &s) ;
	void terms(const std::string &s) ;

	std::vector<char> publish();
};

} /* namespace id3 */

#endif /* PCM2MP3_CPP_SRC_ID3_ID3HEADER_HPP_ */
