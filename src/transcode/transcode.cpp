/*
 * main.cpp
 *
 *  Created on: 30 Nov 2017
 *      Author: julianporter
 */
 
#include "transcode.hpp"
#include <regex>
#include <sstream>
#include "ID3Header.hpp"
#include "../ArgParseStandalone.h"


int main(int argc,char *argv[]) {
	ArgParse::ArgParser parser("PCM transcoding to MP3");
	std::string infile = "";
	std::string outfile = "";
	unsigned rate=8;
	unsigned quality=5;

	parser.AddArgument("-i/--infile","Input file name",&infile,ArgParse::Argument::Required);
	parser.AddArgument("-o/--outfile","Output file name",&outfile,ArgParse::Argument::Optional);
	parser.AddArgument("-b/--bitrate","Required bit rate (defaults to 8)",&rate,ArgParse::Argument::Optional);
	parser.AddArgument("-q/--quality","Quality of conversion (defaults to 5)",&quality,ArgParse::Argument::Optional);

	if(parser.ParseArgs(argc,argv)<0) {
			std::cerr << "Cannot parse arguments correctly" << std::endl;
			return -1;
		}
	if(parser.HelpPrinted()) return 0;

	std::string prefix;
	try {
		std::regex r("^([^.]+)");
		std::smatch matcher;
		std::regex_match(infile,matcher,r);
		std::stringstream s;
		s << matcher[1];
		prefix=s.str();
	}
	catch(...) {
		prefix=infile;
	}
	if(outfile.size()==0) {
		std::stringstream s;
		s << prefix << ".mp3";
		outfile=s.str();
	}
	std::cout << "Transcoding " << infile << " to " << outfile
			<< " with bitrate of " << rate << "kbps and quality " << quality << std::endl;

	try {
 		std::ifstream wav(infile,std::ifstream::binary);
 		pylame::id3::ID3Header parameters;
 		parameters.set(pylame::id3::ID3Field::Title,"Fred");
 		parameters.set(pylame::id3::ID3Field::Copyright,"Lore Lixenberg 2018");
 		parameters.setRate(rate);
 		parameters.setQuality(quality);
		pylame::Transcode transcoder(wav,parameters);
		std::ofstream out(outfile,std::ofstream::binary);
		out << transcoder;
		out.close();
		std::cout << "Completed" << std::endl;
	}
	catch(std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
 }




