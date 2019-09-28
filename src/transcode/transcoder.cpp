/*
 * transcoder.cpp
 *
 *  Created on: 4 Dec 2017
 *      Author: julianporter
 */

#include "transcoder.hpp"
#include "MP3File.hpp"

namespace pylame {



data_t load(std::istream &stream) {
	stream.seekg (0, stream.end);
	auto length = stream.tellg();
	stream.seekg (0, stream.beg);

	data_t file(length,0);
	auto c=file.data();
	int pos=0;
	while(pos<length) {
		stream.read(c+pos,1024);
		pos+=stream.gcount();
	}
	return file;
}

template <typename T>
std::shared_ptr<pcm::PCMFile> make(const data_t &in) {
	auto p = std::make_shared<T>(in);
	return std::static_pointer_cast<pcm::PCMFile>(p);
}

pcm::PCMFile * select(const data_t &in) {
	if(pcm::WAVFile::isInstance(in)) {
			//std::cerr << "Is WAVFile" << std::endl;
			return new pcm::WAVFile(in);
		}
		else if(pcm::AIFFFile::isInstance(in)) {
			//std::cerr << "Is AIFFFile" << std::endl;
			return new pcm::AIFFFile(in);
		}
		else throw MP3Error("Unrecognised file format");
}


Transcode::Transcode(const data_t &in,const id3::ID3Header & parameters) : out()  {
	std::shared_ptr<pcm::PCMFile> infile(select(in));
	MP3File mp3(parameters);
	mp3.transcode(infile);
	out.assign(mp3.cbegin(),mp3.cend());
}


Transcode::Transcode(const pcm::file_t &pcm,const id3::ID3Header & parameters) : out() {
	MP3File mp3(parameters);
	mp3.transcode(pcm);
	out.assign(mp3.cbegin(),mp3.cend());
}



const char* Transcode::ptr() const {
	const unsigned char *u=out.data();
	const char *d=reinterpret_cast<const char *>(u);
	return d;
}

std::ostream & Transcode::output(std::ostream &o) const {
		o.write(ptr(),size());
		return o;
	};


}

std::ostream & operator<<(std::ostream &o,const pylame::Transcode &t) {
	return t.output(o);
}
std::istream & operator>>(std::istream &i,pylame::Transcode &t) {
	t=pylame::Transcode(i,pylame::id3::ID3Header());
	return i;
}


