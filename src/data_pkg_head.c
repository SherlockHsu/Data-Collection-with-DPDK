#include "data_pkg_head.h"
#include <stdio.h>

void get_data_pkg_head(data_pkg_head_t* h, const uint8_t* adcnt)
{
    const uint8_t* p;
    uint8_t* pw;

    p = adcnt;

    pw = (uint8_t*)(&(h->pack_head));
    pw[7] = *p;p++;
    pw[6] = *p;p++;
    pw[5] = *p;p++;
    pw[4] = *p;p++;
    pw[3] = *p;p++;
    pw[2] = *p;p++;
    pw[1] = *p;p++;
    pw[0] = *p;p++;
    h->version = *p;p++;
    h->data_type = *p;p++;
    h->src_dev = *p;p++;
    h->dest_dev = *p;p++;
    pw = (uint8_t*)(&(h->pack_idx));
    pw[3] = *p;p++;
    pw[2] = *p;p++;
    pw[1] = *p;p++;
    pw[0] = *p;p++;
    pw = (uint8_t*)(&(h->data_len));
    pw[3] = *p;p++;
    pw[2] = *p;p++;
    pw[1] = *p;p++;
    pw[0] = *p;p++;
    h->data_len++;
    pw = (uint8_t*)(&(h->data_info));
    pw[3] = *p;p++;
    pw[2] = *p;p++;
    pw[1] = *p;p++;
    pw[0] = *p;p++;
}

void print_data_pkg_head(data_pkg_head_t *h)
{
    printf("pack_head:\t%016lX\n", h->pack_head);
    printf("version:\t%02X\n", h->version);
    printf("data_type:\t%02X\n", h->data_type);
    printf("src_dev:\t%02X\n", h->src_dev);
    printf("dest_dev:\t%02X\n", h->dest_dev);
    printf("pack_idx:\t%08X\n", h->pack_idx);
    printf("data_len:\t%08X(%d)\n", h->data_len, h->data_len);
    printf("data_info:\t%08X\n", h->data_info);
}

void unpack_data_info(data_info_t* h, uint32_t data_info)
{
    uint8_t *pr = (uint8_t *)(&data_info);
    h->subsymbol_num = pr[0];
    h->symbol_num = pr[1] & 0x0F;
    h->subframe_num = pr[1] >> 4;
    h->frame_num = ((uint16_t *)pr)[1];
}

void print_data_info(data_info_t* h)
{
    printf("frame_num:\t%04X\n", h->frame_num);
    printf("subframe_num:\t%02X\n", h->subframe_num);
    printf("symbol_num:\t%02X\n", h->symbol_num);
    printf("subsymbol_num:\t%02X\n", h->subsymbol_num);
}