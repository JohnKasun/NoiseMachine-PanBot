#include "Panner.h"

Panner::Panner(float sampleRate, int numOutputChannels)
{
	if (sampleRate <= 0.0f) throw Exception("Invalid Sample Rate...");
	if (numOutputChannels <= 1) throw Exception("Invalid Number of Output Channels...");

	mSampleRate = sampleRate;
	mNumOutputChannels = numOutputChannels;
	mLfo.reset(new Lfo(mSampleRate));
	mLfo->setParam(Lfo::amplitude, 1.0f);
	mLfo->setParam(Lfo::dc, mLfo->getParam(Lfo::amplitude) * 0.5f); 
}

Panner::~Panner()
{
	mLfo.reset();
}

void Panner::process(const float* inputBuffer, float** outputBuffer, const int numSamples)
{
	// Left Channel : inputBuffer[i] * mLfo.process()
	// Right Channel : inputBufer[i] * (1 - mLfo.process())
}
