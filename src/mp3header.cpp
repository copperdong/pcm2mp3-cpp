/*
 * mp3header.cpp
 *
 *  Created on: 27 Oct 2018
 *      Author: julianporter
 */

#include "info/MP3.hpp"
#include "info/MP3Frame.hpp"
#include <iostream>
#include <regex>
#include "ArgParseStandalone.h"

const std::regex checker("([^0-9a-fA-F])+",std::regex_constants::ECMAScript);
const std::string replacement="";

int main(int argc,char *argv[]) {
	ArgParse::ArgParser parser("MP3 Header expansion");
	std::string hdr = "";
	bool expand=false;
	bool validate=false;
	uint32_t header=0;

	parser.AddArgument("-i/--header","Header (in hex)",&hdr,ArgParse::Argument::Required);
	parser.AddArgument("-x/--expand","Provide human readable output",&expand,ArgParse::Argument::Optional);
	parser.AddArgument("-v/--validate","Validate header",&validate,ArgParse::Argument::Optional);

	if(parser.ParseArgs(argc,argv)<0) {
			std::cerr << "Cannot parse arguments correctly" << std::endl;
			return -1;
		}
	if(parser.HelpPrinted()) return 0;

	try {

		if(hdr.size()>8) {
			std::cerr << "Header is 32 bits: must be no more than 8 hex characters" << std::endl;
			return -2;
		}
		if(std::regex_search(hdr,checker,std::regex_constants::match_any)) {
			std::cerr << "Header failed to convert correctly: must be specified in hex" << std::endl;
			return -3;
		}
		std::stringstream s(hdr);
		s >> std::hex >> header;
		mp3::MP3HeaderConverter c(header);
		auto head=c.header;

		if(expand) {
			mp3::MP3Frame frame(head);
			std::cout << frame << std::endl;
		}
		else {
			std::cout << head << std::endl;
		}
		if(validate) {
			mp3::MP3ValidFrame validator;
			auto failureMode = validator(head);
			if(failureMode.Fails()) {
				std::cout << "Header is invalid:" << std::endl << "    "
						<< failureMode << std::endl;
			}
			else {
				std::cout << "Header is valid" << std::endl;
			}
		}



		return 0;
	}
	catch(std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return -3;
	}

}




