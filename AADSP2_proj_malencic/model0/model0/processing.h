#include "defines.h"

typedef struct __AudioExpander {
	double threshold;
	double ratio;
} AudioExpander_t;


void audio_expander_init(AudioExpander_t * expander);
void gst_audio_dynamic_transform_expander_double(AudioExpander_t * expander,
	double * data, unsigned int num_samples);
void process(double sampleBuffers[MAX_NUM_CHANNEL][BLOCK_SIZE]);