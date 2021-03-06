/*
 * MP3Encoder.cpp
 *
 *  Created on: 30 Nov 2017
 *      Author: julianporter
 */

#include "MP3Encoder.hpp"
#include "PCMData.hpp"
#include <algorithm>

namespace pylame { namespace mp3 {



unsigned MP3Encoder::mp3SizeCalc(unsigned n) {
	return unsigned((double)n*1.25+7200.0);
}


MP3Encoder::MP3Encoder(const pcm::file_t &data_,const unsigned quality,const unsigned rate) :
		MP3Encoder(data_,id3::ID3Header(quality,rate)) {};
MP3Encoder::MP3Encoder(pcm::PCMFile *data_,const id3::ID3Header &parameters) :
		MP3Encoder(std::shared_ptr<pcm::PCMFile>(data_),parameters) {};

MP3Encoder::MP3Encoder(const pcm::file_t &data_,const id3::ID3Header &parameters_):
	data(data_), parameters(parameters_),nSamples(data->samplesPerChannel()), mp3Size(MP3Encoder::mp3SizeCalc(nSamples)), output() {
		
	gf = lame_init();
	if(gf==nullptr) throw MP3Error("Cannot initialise LAME transcoder");
	lame_set_num_channels(gf,data->nChans());
	lame_set_in_samplerate(gf,data->samplesPerSecond());
	lame_set_brate(gf,parameters.Rate());
	lame_set_mode(gf,data->mp3Mode());
	lame_set_quality(gf,parameters.Quality());
	
	lame_set_copyright(gf,parameters.isCopyright());
	lame_set_original(gf,parameters.isOriginal());
	parameters.publish();

	id3Size=parameters.size();
	output.resize(id3Size+mp3Size,0);
	auto response=lame_init_params(gf);
	if(response<0) throw MP3Error("Cannot initialise LAME transcoder options");

	//mp3Out = new unsigned char[mp3Size];

}



	
MP3Encoder::~MP3Encoder() {
	lame_close(gf);
	//delete[] mp3Out;
}	
	
void MP3Encoder::transcode() {

	try {

		auto d=data->bytes();
		mp3Out=output.data();
		int status=0;
		switch(d.format) {
		case pylame::SampleFormat::Int16: {
			pylame::pcm::Channels<int16_t> channels=d.channels<int16_t>();
			status=lame_encode_buffer(gf,channels.left.get(),channels.right.get(),nSamples,mp3Out,mp3Size);
			break; }
		case pylame::SampleFormat::Int32: {
			pylame::pcm::Channels<int32_t> channels=d.channels<int32_t>();
			status=lame_encode_buffer_int(gf,channels.left.get(),channels.right.get(),nSamples,mp3Out,mp3Size);
			break; }
		case pylame::SampleFormat::Float32: {
			pylame::pcm::Channels<float> channels=d.channels<float>();
			status=lame_encode_buffer_ieee_float(gf,channels.left.get(),channels.right.get(),nSamples,mp3Out,mp3Size);
			break; }
		default:
			throw MP3Error("Unacceptable sample type");
		}



		if(status<0) {
			switch(status) {
			case -1:
				throw MP3Error("Transcoding failed: insufficient memory allocated for transcoding");
				break;
			case -2:
				throw MP3Error("Transcoding failed: memory fault");
				break;
			case -3:
				throw MP3Error("Transcoding failed: liblamemp3 subsystem not initialised");
				break;
			case -4:
				throw MP3Error("Transcoding failed: psycho-acoustic problem");
				break;
			default:
				throw MP3Error("Transcoding failed");
				break;
			}
		}
		auto extra=lame_encode_flush(gf,mp3Out,status);

		mp3Size=status+extra;
		output.resize(status+extra+id3Size);
		for(unsigned i=0;i<id3Size;i++) output[mp3Size+i]=parameters[i];
	}
	catch(MP3Error &e) { throw e; }
	catch(std::exception &e) {
		throw MP3Error("Transcoding failed");
	}
}

}}

std::ostream & operator<<(std::ostream &o,const pylame::mp3::MP3Encoder &e) {
	const unsigned char *u=e.ptr();
	const char *d=reinterpret_cast<const char *>(u);
	o.write(d,e.size());
	return o;
}
     
