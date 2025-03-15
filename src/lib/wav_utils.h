#ifndef WAV_UTILS_H
#define WAV_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <err.h>

typedef struct _WAV WAV;

WAV* wav_open(char*);

#endif