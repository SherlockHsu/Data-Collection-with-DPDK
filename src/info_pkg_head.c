#include <stdio.h>
#include "info_pkg_head.h"

void get_info_pkg_head(info_pkg_head_t* h, const uint8_t* adcnt)
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
    pw = (uint8_t*)(&(h->data_vld));
    pw[3] = *p;p++;
    pw[2] = *p;p++;
    pw[1] = *p;p++;
    pw[0] = *p;p++;
    pw = (uint8_t*)(&(h->ldx_sum));
    pw[7] = *p;p++;
    pw[6] = *p;p++;
    pw[5] = *p;p++;
    pw[4] = *p;p++;
    pw[3] = *p;p++;
    pw[2] = *p;p++;
    pw[1] = *p;p++;
    pw[0] = *p;p++;
    h->pack_typ = *p;p++;
    h->pack_num = *p;p++;
    h->pack_idx = *p;p++;
    h->dev_num = *p;p++;
    pw = (uint8_t*)(&(h->packet_len));
    pw[1] = *p;p++;
    pw[0] = *p;p++;
    pw = (uint8_t*)(&(h->data_len));
    pw[1] = *p;p++;
    pw[0] = *p;p++;

}

void print_info_pkg_head(info_pkg_head_t *h)
{
    printf("pack_head:\t%016lX\n", h->pack_head);
    printf("data_vld:\t%02X\n", h->data_vld);
    printf("ldx_sum:\t%016lX\n", h->ldx_sum);
    printf("pack_typ:\t%02X\n", h->pack_typ);
    printf("pack_num:\t%02X\n", h->pack_num);
    printf("pack_idx:\t%02X\n", h->pack_idx);
    printf("dev_num:\t%02X\n", h->dev_num);
    printf("packet_len:\t%04X(%d)\n", h->packet_len, (h->packet_len + 1) * 8);
    printf("data_len:\t%04X(%d)\n", h->data_len, (h->data_len + 1) * 8);
}