#ifndef DATA_PKG_HEAD_H
#define DATA_PKG_HEAD_H

#include <stdint.h>

#define DATA_PKG_HEAD_LEN 32
#define DATA_PKG_REMAIN_LEN 8
#define DATA_PKG_DATA_LEN 1320
#define DATA_PKG_END_LEN 8
#define DATA_PKG_LEN (DATA_PKG_HEAD_LEN + DATA_PKG_DATA_LEN + DATA_PKG_END_LEN)

typedef struct
{
    uint64_t pack_head;
    uint8_t version;
    uint8_t data_type;
    uint8_t src_dev;
    uint8_t dest_dev;
    uint32_t pack_idx;
    uint32_t data_len;
    uint32_t data_info;
} data_pkg_head_t;

typedef struct
{
    uint16_t frame_num;
    uint8_t subframe_num;
    uint8_t symbol_num;
    uint8_t subsymbol_num;
} data_info_t;

void get_data_pkg_head(data_pkg_head_t* h, const uint8_t* adcnt);

void print_data_pkg_head(data_pkg_head_t* h);

void unpack_data_info(data_info_t* h, uint32_t data_info);

void print_data_info(data_info_t* h);

#endif