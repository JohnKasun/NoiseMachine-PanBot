#include "Panner.h"

Panner::Panner(float sampleRate)
{
	if (sampleRate <= 0.0f) throw Exception("Invalid Sample Rate...");

	mSampleRate = sampleRate;
	
	for (auto& lfo : mLfos) {
		lfo.reset(new Lfo(mSampleRate));
	}
	mLfos.at(1)->setParam(Lfo::phaseInRadians, M_PI);

	setSpeed(1.0f);
	setWidth(100.0f);
	setOffset(0.0f);
}

Panner::~Panner()
{
}

void Panner::setWidth(float widthInPercent)
{
	if (widthInPercent < 0.0f || widthInPercent > 100.0f) throw Exception("Invalid Width Parameter");

	float newAmplitude = (widthInPercent / 100.0f) / 2.0f;
	for (auto& lfo : mLfos) {
		lfo->setParam(Lfo::amplitude, newAmplitude);
	}
}

void Panner::setSpeed(float speedInHz)
{
	if (speedInHz < 0.0f || speedInHz > 5.0f) throw Exception("Invalid Speed Parameter");

	for (auto& lfo : mLfos) {
		lfo->setParam(Lfo::freqInHz, speedInHz);
	}
}

void Panner::setOffset(float offset)
{
	float offsetNorm = offset / 100.0f / 2.0f;

	mLfos.at(0)->setParam(Lfo::dc, 0.5f - offsetNorm);
	mLfos.at(1)->setParam(Lfo::dc, 0.5f + offsetNorm);
}

std::tuple<float, float> Panner::process(float input)
{
	auto leftLfoVal = std::max<float>(0.0f, std::min<float>(mLfos.at(0)->process(), 1.0f));
	auto rightLfoVal = std::max<float>(0.0f, std::min<float>(mLfos.at(1)->process(), 1.0f));
	auto leftChannel = input * leftLfoVal;
	auto rightChannel = input * rightLfoVal;
	auto out = std::make_tuple(leftChannel, rightChannel);
	return out;
}
