#include "processing.h"


/*
*
* This element can act as a dynamic range expander. A expander changes the
* amplitude of all samples below a specific threshold with a specific ratio
* If soft-knee mode is selected the ratio is applied smoothly.
*
* parameters: ratio [0.0, 8.0)
*             threshold [0.0, 1.0)
*/



void audio_expander_init(AudioExpander_t * expander) {
	expander->ratio = expander_ratio;
	expander->threshold = expander_threshold;
}

void gst_audio_dynamic_transform_expander_double(AudioExpander_t * expander,
	DSPfract * data, DSPushort num_samples) {
	DSPfract val, threshold = expander->threshold, zero;
	DSPint i;

	/* Nothing to do for us here if threshold equals 0.0
	* or ratio equals 1.0 */
	if (expander->threshold == FRACT_NUM(0.0) || expander->ratio == FRACT_NUM(1.0))
		return;

	/* zero crossing of our function */
	if (expander->ratio != FRACT_NUM(0.0))
		zero = threshold - threshold / FRACT_NUM(expander->ratio);
	else
		zero = 0.0;

	if (zero < FRACT_NUM(0.0))
		zero = 0.0;

	for (i = 0; i < num_samples; i++) {
		val = data[i];

		if (val < threshold && val > zero) {
			val = expander->ratio * val + threshold * FRACT_NUM(1.0 - expander->ratio);
		}
		else if ((val <= zero && val > FRACT_NUM(0.0)) || (val >= -zero && val < FRACT_NUM(0.0))) {
			val = 0.0;
		}
		else if (val > -threshold && val < -zero) {
			val = expander->ratio * val - threshold * FRACT_NUM(1.0 - expander->ratio);
		}
		data[i] = (double)val;
	}
}

void process()
{
	DSPint i;
	AudioExpander_t expander;
	audio_expander_init(&expander);
	DSPfract * p0 = sampleBuffer[0];
	DSPfract * p1 = sampleBuffer[1];
	DSPfract * p2 = sampleBuffer[2];
	DSPfract * p3 = sampleBuffer[3];
	DSPfract * p4 = sampleBuffer[4];

	for (i = 0; i < BLOCK_SIZE; i++) // stage 1
	{
		*p0 = (*p0) * DECIBEL_GAIN_MINUS_6DB;
		*p4 = (*p4) * DECIBEL_GAIN_MINUS_6DB;
		p0++;
		p4++;
	}

	p0 = sampleBuffer[0];
	p4 = sampleBuffer[4];

	for (i = 0; i < BLOCK_SIZE; i++) // stage 2
	{
		*p2 = (*p0 + *p4) * DECIBEL_GAIN_MINUS_3DB;
		p2++;
		p0++;
		p4++;
	}

	p2 = sampleBuffer[2];
	p0 = sampleBuffer[0];
	p4 = sampleBuffer[4];

	gst_audio_dynamic_transform_expander_double(&expander, p0, BLOCK_SIZE);
	gst_audio_dynamic_transform_expander_double(&expander, p4, BLOCK_SIZE);

	for (i = 0; i < BLOCK_SIZE; i++) // stage 3
	{
		*p0 = (*p0) * DECIBEL_GAIN_MINUS_2DB;
		*p4 = (*p4) * DECIBEL_GAIN_MINUS_2DB;
		*p1 = (*p2) * DECIBEL_GAIN_MINUS_6DB;
		p0++;
		p4++;
		p1++;
		p2++;
	}

	p0 = sampleBuffer[0];
	p4 = sampleBuffer[4];
	p1 = sampleBuffer[1];
	p2 = sampleBuffer[2];

	for (i = 0; i < BLOCK_SIZE; i++) // final
	{
		*p0 = *p0 + *p1;
		*p4 = *p4 + *p1;
		*p3 = *p1;
		p0++;
		p1++;
		p4++;
		p3++;
	}
}
