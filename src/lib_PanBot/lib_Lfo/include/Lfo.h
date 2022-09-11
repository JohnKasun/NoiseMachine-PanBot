#pragma once

#include <array>
#include <memory>

#include "ErrorDef.h"
#include "RingBuffer.h"
#include "Util.h"
#include "Wavetable.h"

class Lfo {
 public:
  enum Param_t {
    amplitude,
    freqInHz,
    phaseInRadians,
    dc,

    numParams
  };

  enum Waveform_t {
    Sine,
    Triangle,

    numWaveforms
  };

  Lfo(float sampleRate);
  ~Lfo() = default;

  void setParam(Param_t param, float value);
  void setWaveform(Waveform_t waveform);
  float getParam(Param_t param) const;
  Waveform_t getWaveform() const;

  float process();

 private:
  static const size_t mBufferSize = 1 << 9;
  std::array<std::unique_ptr<CRingBuffer<float>>, numWaveforms> mBuffers;
  float mParamValues[numParams]{};
  Waveform_t mCurrentWaveform = Waveform_t::Sine;

  float mSampleRate = 44100.0f;
  float mCurrentIndex = 0.0f;
};