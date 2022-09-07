#pragma once

#include "Lfo.h"
#include "Exception.h"

class Panner {
public:
	Panner(float sampleRate, int numOutputChannels = 2);
	~Panner();

	void process(const float* inputBuffer, float** outputBuffer, const int numSamples);
private:
	float mSampleRate;
	int mNumOutputChannels;
	std::unique_ptr<Lfo> mLfo;
};