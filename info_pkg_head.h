#ifndef INFO_PKG_HEAD_H
#define INFO_PKG_HEAD_H

#include <stdint.h>
#include <stdio.h>

#define INFO_PKG_HEAD_LEN 48
#define INFO_PKG_REMAIN_LEN 20
#define MAX_PKG_LEN 1360
#define DATA_END_LEN 8

typedef struct
{
    // uint8_t send_en;
    // uint8_t data_vld;
    // uint8_t pack_type;
    // uint16_t pack_hd;
    // uint16_t pack_idx;
    // uint16_t pack_len;

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

void write_data(FILE *fp, const uint8_t *adcnt);

// int check_info_pkg_head(info_pkg_head_t *h, info_pkg_head_t *ph);

// int is_info_pkg_head_pre_right(info_pkg_head_t *h, info_pkg_head_t *ph);

// void init_pre_info_pkg_head(info_pkg_head_t *ph);

// void update_pre_info_pkg_head(info_pkg_head_t *h, info_pkg_head_t *ph);

// int is_pkg_len_legal(int len);

// int is_info_pkg_head_a_legal_begin(info_pkg_head_t *h);

// void write_data_pkg(info_pkg_head_t *h, uint8_t *adcnt);

// void wirte_data(FILE *fp, info_pkg_head_t *h, uint8_t *adcnt);

// void load_info_pkg_head_ul(info_pkg_head_t *h, uint8_t *adcnt);

// void load_info_pkg_head_dl(info_pkg_head_t *h, uint8_t *adcnt);

// void init_dl_info_pkg_head(info_pkg_head_t *h);

// void init_ul_info_pkg_head(info_pkg_head_t *h);

#endif