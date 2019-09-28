/*
 * mp3.cpp
 *
 *  Created on: 23 Apr 2018
 *      Author: julianporter
 */

#include <iostream>
#include <fstream>
#include "mp3info.hpp"
#include "../ArgParseStandalone.h"
#include "ID3.hpp"

int main(int argc,char *argv[]) {
	ArgParse::ArgParser parser("MP3 file verification and analysis");
	bool verbose = false;
	bool tags = false;
	std::string infile = "";

	parser.AddArgument("-t/--tags","List ID3 tags",&tags,ArgParse::Argument::Optional);
	parser.AddArgument("-v/--verbose","Produce verbose output",&verbose,ArgParse::Argument::Optional);
	parser.AddArgument("-i/--infile","File to analyse",&infile,ArgParse::Argument::Required);

	if(parser.ParseArgs(argc,argv)<0) {
		std::cerr << "Cannot parse arguments correctly" << std::endl;
		return -1;
	}
	if(parser.HelpPrinted()) return 0;



	try {
		std::cout << "Analysing " << infile;
		if(verbose) std::cout << " with verbose output";
		std::cout << std::endl;

		mp3::MP3Test test(infile);
		test.parse(verbose);
		auto result=test();
		std::cout << *result << std::endl;

		if(tags) {
			id3::ID3 hdr(infile);
			std::cout << hdr << std::endl;
		}



	}
	catch(std::exception &e) {
			std::cerr << "ERROR: " << e.what() << std::endl;
		}
		return 0;
}



