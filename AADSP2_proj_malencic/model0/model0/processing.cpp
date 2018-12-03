#include "stdafx.h"
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
	double * data, unsigned int num_samples) {
	double val, threshold = expander->threshold, zero;
	int i;

	/* Nothing to do for us here if threshold equals 0.0
	* or ratio equals 1.0 */
	if (expander->threshold == 0.0 || expander->ratio == 1.0)
		return;

	/* zero crossing of our function */
	if (expander->ratio != 0.0)
		zero = threshold - threshold / expander->ratio;
	else
		zero = 0.0;

	if (zero < 0.0)
		zero = 0.0;

	for (i = 0; i < num_samples; i++) {
		val = data[i];

		if (val < threshold && val > zero) {
			val = expander->ratio * val + threshold * (1.0 - expander->ratio);
		}
		else if ((val <= zero && val > 0.0) || (val >= -zero && val < 0.0)) {
			val = 0.0;
		}
		else if (val > -threshold && val < -zero) {
			val = expander->ratio * val - threshold * (1.0 - expander->ratio);
		}
		data[i] = (double)val;
	}
}

void process(double sampleBuffers[MAX_NUM_CHANNEL][BLOCK_SIZE])
{
	int i;
	AudioExpander_t expander;
	double Ls_buffer[BLOCK_SIZE];
	double L_buffer[BLOCK_SIZE];
	double C_buffer[BLOCK_SIZE];
	double R_buffer[BLOCK_SIZE];
	double Rs_buffer[BLOCK_SIZE];
	audio_expander_init(&expander);


	for (i = 0; i < BLOCK_SIZE; i++) // stage 1
	{
		Ls_buffer[i] = sampleBuffers[0][i] * DECIBEL_GAIN_MINUS_6DB;
		L_buffer[i] = sampleBuffers[0][i] * DECIBEL_GAIN_MINUS_6DB;
		R_buffer[i] = sampleBuffers[1][i] * DECIBEL_GAIN_MINUS_6DB;
		Rs_buffer[i] = sampleBuffers[1][i] * DECIBEL_GAIN_MINUS_6DB;
	}


	for (i = 0; i < BLOCK_SIZE; i++) // stage 2
	{
		C_buffer[i] = L_buffer[i] + R_buffer[i];
		C_buffer[i] = C_buffer[i] * DECIBEL_GAIN_MINUS_3DB;
	}

	gst_audio_dynamic_transform_expander_double(&expander, Ls_buffer, BLOCK_SIZE);
	gst_audio_dynamic_transform_expander_double(&expander, Rs_buffer, BLOCK_SIZE);

	for (i = 0; i < BLOCK_SIZE; i++) // stage 3
	{
		Ls_buffer[i] = Ls_buffer[i] * DECIBEL_GAIN_MINUS_2DB;
		Rs_buffer[i] = Rs_buffer[i] * DECIBEL_GAIN_MINUS_2DB;
		L_buffer[i] = C_buffer[i] * DECIBEL_GAIN_MINUS_6DB;
		R_buffer[i] = C_buffer[i] * DECIBEL_GAIN_MINUS_6DB;
	}

	for (i = 0; i < BLOCK_SIZE; i++) // stage 4
	{
		Ls_buffer[i] = Ls_buffer[i] + L_buffer[i];
		Rs_buffer[i] = Rs_buffer[i] + R_buffer[i];
	}

	for (i = 0; i < BLOCK_SIZE; i++) // final
	{
		sampleBuffers[0][i] = Ls_buffer[i];
		sampleBuffers[1][i] = L_buffer[i];
		sampleBuffers[2][i] = C_buffer[i];
		sampleBuffers[3][i] = R_buffer[i];
		sampleBuffers[4][i] = Rs_buffer[i];
	}

}
