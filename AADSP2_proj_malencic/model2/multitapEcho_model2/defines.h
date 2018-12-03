#include "common.h"

#define BLOCK_SIZE 16
#define MAX_NUM_CHANNEL 8
#define DECIBEL_GAIN_MINUS_6DB FRACT_NUM(0.501187)
#define DECIBEL_GAIN_MINUS_3DB FRACT_NUM(0.707946)
#define DECIBEL_GAIN_MINUS_2DB FRACT_NUM(0.794328)

extern DSPfract expander_ratio;
extern DSPfract expander_threshold;
extern DSPfract sampleBuffer[MAX_NUM_CHANNEL][BLOCK_SIZE];
