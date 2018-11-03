/*
 * Metadata.cpp
 *
 *  Created on: 28 Oct 2018
 *      Author: julianporter
 */

#include "ID3Metadata.hpp"
#include <map>



namespace pylame { namespace id3 {



std::map<ID3Field,str_t> Metadata::id3str = {
		{ ID3Field::Title, "title" },
		{ ID3Field::Artist, "ARTIST" },
		{ ID3Field::Album, "ALBUM" },
		{ ID3Field::Comment, "COMMENT" },
		{ ID3Field::Genre, "GENRE" },
		{ ID3Field::Date, "date" },
		{ ID3Field::Track, "TRACK" },
		{ ID3Field::TermsOfUse, "USER" },
		{ ID3Field::MediaType, "TMED" },
		{ ID3Field::Copyright, "copyright" },
		{ ID3Field::Duration, "TLEN" }
};

ID3Field Metadata::field(const std::string &name) {
		str_t s=str_t(name).upper();
		auto it=std::find_if(id3str.begin(),id3str.end(),[s](auto kv) {
			return kv.second==s;
		});
		if(it==id3str.end()) throw std::runtime_error("No such metadata key");
		return it->first;
	}



}} /* namespace id3 */
