#pragma once

#include "Lfo.h"
#include "Exception.h"

#include <vector>
#include <tuple>

class PanBotEngine {
public:
	PanBotEngine(float sampleRate);
	~PanBotEngine();

	void setWidth(float widthInPercent);
	void setSpeed(float speedInHz);
	void setOffset(float offset);

	std::tuple<float, float> process(float input);
private:
	float mSampleRate;
	std::array<std::unique_ptr<Lfo>, 2> mLfos;
};