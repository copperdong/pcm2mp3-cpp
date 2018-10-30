/*
 * main.cpp
 *
 *  Created on: 28 Oct 2018
 *      Author: julianporter
 */


#include <iostream>
#include <string>
#include "ID3Header.hpp"
#include "../ArgParseStandalone.h"

void dump(const std::vector<char> &v) {
	for(unsigned i=0;i<v.size();++i) {
		auto c=(unsigned char)v[i];
		std::string pad=(c<16) ? "0" : "";
		std::cout << pad << std::hex << (unsigned)c;
		if((i%8)==7) std::cout << std::endl;
		else std::cout << " ";
		}
		if(7!=(v.size()%8)) std::cout << std::endl;
	}

id3::ID3Version setVersion(const bool v1,const bool v2) {
	if(v1 && v2) return id3::ID3Version::ID3v1v2;
	else if(v1) return id3::ID3Version::ID3v1;
	else if(v2) return id3::ID3Version::ID3v2;
	else throw std::runtime_error("No version selected");
}

int main(int argc,char *argv[]) {

	ArgParse::ArgParser parser("ID3 header generation");
	bool v1 = false;
	bool v2 = false;

	parser.AddArgument("--v1","Produce ID3v1 output",&v1,ArgParse::Argument::Optional);
	parser.AddArgument("--v2","Produce ID3v2 output",&v2,ArgParse::Argument::Optional);

	if(parser.ParseArgs(argc,argv)<0) {
		std::cerr << "Cannot parse arguments correctly" << std::endl;
		return -1;
	}
	if(parser.HelpPrinted()) return 0;

	try {
		id3::ID3Header tag("The title","ME ME ME ME ME",setVersion(v1,v2));

		tag.comment("This is a comment");
		auto v=tag.publish();
		dump(v);
		}
	catch(std::exception &e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	return 0;

}

