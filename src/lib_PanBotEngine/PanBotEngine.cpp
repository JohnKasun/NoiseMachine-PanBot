#include "PanBotEngine.h"

PanBotEngine::PanBotEngine(float sampleRate)
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

PanBotEngine::~PanBotEngine()
{
}

void PanBotEngine::setWidth(float widthInPercent)
{
	if (widthInPercent < 0.0f || widthInPercent > 100.0f) throw Exception("Invalid Width Parameter");

	float newAmplitude = widthInPercent / 200.0f;
	for (auto& lfo : mLfos) {
		lfo->setParam(Lfo::amplitude, newAmplitude);
	}
}

void PanBotEngine::setSpeed(float speedInHz)
{
	if (speedInHz < 0.0f || speedInHz > 5.0f) throw Exception("Invalid Speed Parameter");

	for (auto& lfo : mLfos) {
		lfo->setParam(Lfo::freqInHz, speedInHz);
	}
}

void PanBotEngine::setOffset(float offset)
{
	if (offset < -100.0f || offset > 100.0f) throw Exception("Invalid Offset Parameter");
	float offsetNorm = offset / 200.0f;

	mLfos.at(0)->setParam(Lfo::dc, 0.5f - offsetNorm);
	mLfos.at(1)->setParam(Lfo::dc, 0.5f + offsetNorm);
}

std::pair<float, float> PanBotEngine::process(float input)
{
	auto leftLfoVal = std::max<float>(0.0f, std::min<float>(mLfos.at(0)->process(), 1.0f));
	auto rightLfoVal = std::max<float>(0.0f, std::min<float>(mLfos.at(1)->process(), 1.0f));
	auto leftChannel = input * leftLfoVal;
	auto rightChannel = input * rightLfoVal;
	auto out = std::make_pair(leftChannel, rightChannel);
	return out;
}
