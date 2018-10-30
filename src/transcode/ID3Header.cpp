/*
 * ID3Header.cpp
 *
 *  Created on: 29 Oct 2018
 *      Author: julianporter
 */

#include "ID3Header.hpp"

namespace pylame { namespace id3 {

	ID3Header::ID3Header(const ID3Version v) : version(v), metadata(), data() {
		//metadata.set(ID3Field::Year,std::to_string(Time::year()));
		metadata.set(ID3Field::Date,Time::timestamp());
		metadata.set(ID3Field::MediaType,std::string("DIG"));
	};
	ID3Header::ID3Header(const std::string &title,const std::string &copyright,const ID3Version v) :
		ID3Header(v) {
		metadata.set(ID3Field::Title,title);
		metadata.set(ID3Field::Copyright,copyright);
	};
	void ID3Header::set(const ID3Field &f,const std::string &v) { metadata.set(f,v); }
	void ID3Header::set(const ID3Field &f,const double v) { metadata.set(f,v); }
	void ID3Header::set(const std::string &k,const std::string &v) { set(Metadata::field(k),v); }

	void ID3Header::set(const std::string &k,const double v) { set(Metadata::field(k),v); }
	bool ID3Header::has(const ID3Field&f) const { return metadata.has(f); }
	void ID3Header::comment(const std::string &s) { set(ID3Field::Comment,s); }
	void ID3Header::terms(const std::string &s) { set(ID3Field::TermsOfUse,s); };

	std::vector<char> ID3Header::publish() {
			switch(version) {
			case ID3Version::ID3v1:
				data=metadata.publish<1>();
				break;
			case ID3Version::ID3v2:
				data=metadata.publish<2>();
				break;
			case ID3Version::ID3v1v2: {
				std::vector<char> v1(metadata.publish<1>());
				std::vector<char> v2(metadata.publish<2>());
				data.resize(v1.size()+v2.size(),0);
				for(unsigned i=0;i<v1.size();i++) data[i]=v1[i];
				for(unsigned i=0;i<v2.size();i++) data[i+v1.size()]=v2[i];
				break;
			}
			default:
				data.clear();
				break;
			}
			return data;
		}

}}



