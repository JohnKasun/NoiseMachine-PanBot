#include "Panner.h"

Panner::Panner(float sampleRate, int numOutputChannels)
{
	if (sampleRate <= 0.0f) throw Exception("Invalid Sample Rate...");
	if (numOutputChannels <= 1) throw Exception("Invalid Number of Output Channels...");

	mSampleRate = sampleRate;
	mNumOutputChannels = numOutputChannels;
	mLfo.reset(new Lfo(mSampleRate));
}

Panner::~Panner()
{
	mLfo.reset();
}

void Panner::process(const float* inputBuffer, float** outputBuffer, const int numSamples)
{
}
