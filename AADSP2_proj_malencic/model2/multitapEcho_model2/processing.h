#include "defines.h"

typedef struct __AudioExpander {
	DSPaccum threshold;
	DSPaccum ratio;
} AudioExpander_t;


void audio_expander_init(AudioExpander_t * expander);
void gst_audio_dynamic_transform_expander_double(AudioExpander_t * expander,
	DSPfract * data, DSPushort num_samples);
void process();

