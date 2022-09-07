#include "Panner.h"

Panner::Panner(float sampleRate)
{
	if (sampleRate <= 0.0f) throw Exception("Invalid Sample Rate...");

	mSampleRate = sampleRate;
	
	for (auto& lfo : mLfos) {
		lfo.reset(new Lfo(mSampleRate));
		lfo->setParam(Lfo::amplitude, 0.5f);
		lfo->setParam(Lfo::freqInHz, 1.0f);
		lfo->setParam(Lfo::dc, 0.5f);
	}
	mLfos.at(1)->setParam(Lfo::phaseInRadians, M_PI);
}

Panner::~Panner()
{
}

std::tuple<float, float> Panner::process(float input)
{
	auto leftChannel = input * mLfos.at(0)->process();
	auto rightChannel = input * mLfos.at(1)->process();
	auto out = std::make_tuple(leftChannel, rightChannel);
	return out;
}
