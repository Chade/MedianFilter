#ifndef _MEDIANFILTER_H_
#define _MEDIANFILTER_H_

#include "Arduino.h"

class MedianFilter
{
  public:
    MedianFilter(byte size = 3);
    ~MedianFilter();

    void add(int element);
    int get();
	
	static int multiMap (int val, const int *_in, const int *_out, const uint8_t& size)
	{
		// Take care the value is within range
		// val = constrain(val, _in[0], _in[size-1]);
		if (val <= _in[0]) return _out[0];
		if (val >= _in[size-1]) return _out[size-1];

		// Search right interval
		uint8_t pos = 1;  // _in[0] allready tested
		while (val > _in[pos]) pos++;

		// This will handle all exact "points" in the _in array
		if (val == _in[pos]) return _out[pos];

		// Interpolate in the right segment for the rest
		return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
	};

	static float multiMap (float val, const float *_in, const float *_out, const uint8_t& size)
	{
		// Take care the value is within range
		// val = constrain(val, _in[0], _in[size-1]);
		if (val <= _in[0]) return _out[0];
		if (val >= _in[size-1]) return _out[size-1];

		// Search right interval
		uint8_t pos = 1;  // _in[0] allready tested
		while (val > _in[pos]) pos++;

		// This will handle all exact "points" in the _in array
		if (val == _in[pos]) return _out[pos];

		// Interpolate in the right segment for the rest
		return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
	};	
	
    void printBuffer();
    void printSorted();

  private:
    byte filtersize;
    byte index;

    int* buffer;
    int* sorted;

    void sort(int array [], byte from, byte to);
};

#endif // _MEDIANFILTER_H_