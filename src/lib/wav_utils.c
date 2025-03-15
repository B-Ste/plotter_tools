#include "wav_utils.h"

#define START_BUF_SIZE 0x14

typedef struct _WAV
{
    u_int16_t format_type;
    u_int16_t channels;
    u_int32_t sample_rate;
    u_int32_t byte_per_second;
    u_int16_t byte_per_block;
    u_int16_t bit_per_sample;
    u_int32_t size;
    void* data;
} WAV;

WAV* wav_open(char* path) {
    WAV* wav = malloc(sizeof(WAV));
    if (!wav) err(1, "Failed to allocate");

    FILE* fd = fopen(path, "r");
    if (!fd) err(2, "Failed to open WAV-File");

    char* buf = malloc(START_BUF_SIZE);
    if (!buf) err(1, "Failed to allocate");

    fread(buf, sizeof(char), START_BUF_SIZE, fd);

    // check for RIFF WAVE start and read header length
    if (buf[0] != 0x52 || buf[1] != 0x49 || buf[2] != 0x46 || buf[3] != 0x46 ||
    buf[8] != 0x57 || buf[9] != 0x41 || buf[10] != 0x56 || buf[11] != 0x45) err(4, "Invalid WAV-File\n");

    // read rest of header and fill out meta-data
    int32_t head_len_rem = *(int32_t*) (buf + 0x10);
    if (head_len_rem <= START_BUF_SIZE) memset(buf, 0, START_BUF_SIZE);
    else buf = realloc(buf, head_len_rem);
    fread(buf, sizeof(char), head_len_rem, fd);
    wav->format_type = *(u_int16_t*) buf;
    wav->channels = *(u_int16_t*) (buf+2);
    wav->sample_rate = *(u_int32_t*) (buf+4);
    wav->byte_per_second = *(u_int32_t*) (buf+8);
    wav->byte_per_block = *(u_int16_t*) (buf+12);
    wav->bit_per_sample = *(u_int16_t*) (buf+14);

    // read data section size
    memset(buf, 0, (head_len_rem > START_BUF_SIZE) ? head_len_rem : START_BUF_SIZE);
    fread(buf, sizeof(char), 8, fd);
    if (buf[0] != 0x64 || buf[1] != 0x61 || buf[2] != 0x74 || buf[3] != 0x61) err(4, "Invalid WAV-File\n");
    wav->size = *(uint32_t*) (buf+4);

    wav->data = malloc(wav->size);
    if (!wav->data) err(1, "Failed to allocate");

    fread(wav->data, sizeof(char), wav->size, fd);

    free(buf);
    fclose(fd);
    return wav;
}
