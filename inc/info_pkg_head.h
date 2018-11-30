#ifndef INFO_PKG_HEAD_H
#define INFO_PKG_HEAD_H

#include <stdint.h>
#include <stdio.h>

#define INFO_PKG_HEAD_LEN 48
#define INFO_PKG_REMAIN_LEN 20
#define INFO_PKG_DATA_LEN 1360
#define INFO_PKG_END_LEN 8
#define INFO_PKG_LEN (INFO_PKG_HEAD_LEN + INFO_PKG_DATA_LEN + INFO_PKG_END_LEN)

typedef struct
{

    uint64_t pack_head;
    uint32_t data_vld;
    uint64_t ldx_sum;
    uint8_t pack_typ;
    uint8_t pack_num;
    uint8_t pack_idx;
    uint8_t dev_num;
    uint16_t packet_len;
    uint16_t data_len;

} info_pkg_head_t;

void get_info_pkg_head(info_pkg_head_t* h, const uint8_t* adcnt);

void print_info_pkg_head(info_pkg_head_t* h);

#endif