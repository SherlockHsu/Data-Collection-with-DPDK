#include <stdio.h>
#include <stdint.h>

#include "info_pkg_head.h"
#include "data_pkg_head.h"

// #define TRANSCODING
#define STATISTICS

#define MAX_FRAME_NUM 100

void unpack_vld_data_complex16(uint8_t *adcnt, uint32_t len, int16_t *datar, int16_t *datai);
void unpack_vld_data_int32(uint8_t *adcnt, uint32_t len, int32_t *data32);

int main()
{
    FILE *fr;
    FILE *fw;
    FILE *fwt;
    FILE *fw2r, *fw3r, *fw4r;
    FILE *fw2i, *fw3i, *fw4i;
    FILE *fw0x03r, *fw0x04r;
    FILE *fw0x03i, *fw0x04i;
    FILE *fw0x05;
    int32_t i;
    info_pkg_head_t iph;
    data_pkg_head_t dph;
    data_info_t dit;
    fr = fopen("vld_data.bin", "rb");
    fw = fopen("data.txt", "w+");
    fw2r = fopen("rx_U2r.txt", "w+");
    fw2i = fopen("rx_U2i.txt", "w+");
    fw3r = fopen("rx_U3r.txt", "w+");
    fw3i = fopen("rx_U3i.txt", "w+");
    fw4r = fopen("rx_U4r.txt", "w+");
    fw4i = fopen("rx_U4i.txt", "w+");
    fw0x03r = fopen("0x03r.txt", "w+");
    fw0x03i = fopen("0x03i.txt", "w+");
    fw0x04r = fopen("0x04r.txt", "w+");
    fw0x04i = fopen("0x04i.txt", "w+");
    fw0x05 = fopen("0x05.txt", "w+");
    fwt = fopen("test.txt", "w+");
    uint8_t data[INFO_PKG_LEN];
    int16_t datar[DATA_PKG_DATA_LEN / 4];
    int16_t datai[DATA_PKG_DATA_LEN / 4];
    int32_t data32[DATA_PKG_DATA_LEN / 4];
    uint8_t *datav = data + INFO_PKG_HEAD_LEN + DATA_PKG_HEAD_LEN;

#ifdef TRANSCODING
    for (i = 0; i < 12; i++)
    {
        fread(data, sizeof(uint8_t), INFO_PKG_LEN, fr);
        get_info_pkg_head(&iph, data);
        get_data_pkg_head(&dph, data + INFO_PKG_HEAD_LEN);
        // print_info_pkg_head(&iph);
        // printf("\n");
        if (dph.src_dev == 0X01)
        {
            print_data_pkg_head(&dph);
            unpack_data_info(&dit, dph.data_info);
            printf("\n");
            print_data_info(&dit);
            printf("\n");
            // unpack_vld_data_complex16(datav, dph.data_len, datar, datai);
            // for (i = 0; i < dph.data_len; i++)
            // {
            //     fprintf(fw2r, "%d ", datar[i]);
            //     fprintf(fw2i, "%d ", datai[i]);
            // }
        }
        for (i = 0; i < INFO_PKG_LEN; i++)
            fprintf(fw, "%02X ", data[i]);
        fprintf(fw, "\n");
    }
#endif

#ifdef STATISTICS
    int8_t start_flag = 0;
    uint16_t start_frame;
    while (fread(data, sizeof(uint8_t), INFO_PKG_LEN, fr))
    {
        get_info_pkg_head(&iph, data);
        get_data_pkg_head(&dph, data + INFO_PKG_HEAD_LEN);
        if (dph.src_dev == 0X01)
        {
            unpack_data_info(&dit, dph.data_info);
            if (start_flag == 0)
            {
                if (dit.subframe_num == 0x02 &&
                    dit.symbol_num == 0x00 &&
                    dit.subsymbol_num == 0x00)
                {
                    start_flag = 1;
                    start_frame = dit.frame_num;
                }
            }
            if (start_flag == 1)
            {                
                if (dit.frame_num == start_frame + MAX_FRAME_NUM)
                    break;
                for (i = 0; i < INFO_PKG_LEN; i++)
                    fprintf(fw, "%02X ", data[i]);
                fprintf(fw, "\n");
                
                switch (dph.data_type)
                {
                case 0x11:
                    unpack_vld_data_complex16(datav, dph.data_len, datar, datai);
                    switch (dit.subframe_num)
                    {
                    case 2:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw2r, "%d ", datar[i]);
                            fprintf(fw2i, "%d ", datai[i]);
                        }
                        break;
                    case 3:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw3r, "%d ", datar[i]);
                            fprintf(fw3i, "%d ", datai[i]);
                        }
                        break;
                    case 4:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw4r, "%d ", datar[i]);
                            fprintf(fw4i, "%d ", datai[i]);
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                case 0x03:
                    unpack_vld_data_complex16(datav, dph.data_len, datar, datai);
                    for (i = 0; i < dph.data_len; i++)
                    {
                        // for (i = 0; i < INFO_PKG_LEN; i++)
                        //     fprintf(fwt, "%02X ", data[i]);
                        // fprintf(fwt, "\n");
                        fprintf(fw0x03r, "%d ", datar[i]);
                        fprintf(fw0x03i, "%d ", datai[i]);
                    }
                    break;
                case 0x04:
                    unpack_vld_data_complex16(datav, dph.data_len, datar, datai);
                    for (i = 0; i < dph.data_len; i++)
                    {
                        fprintf(fw0x04r, "%d ", datar[i]);
                        fprintf(fw0x04i, "%d ", datai[i]);
                    }
                    break;
                case 0x05:
                    unpack_vld_data_int32(datav, dph.data_len, data32);
                    for (i = 0; i < dph.data_len; i++)
                        fprintf(fw0x05, "%d ", data32[i]);
                    break;
                default:
                    break;
                }
            }
        }
    }
#endif

    fclose(fr);
    fclose(fw);
    fclose(fw2r);
    fclose(fw2i);
    fclose(fw3r);
    fclose(fw3i);
    fclose(fw4r);
    fclose(fw4i);
    fclose(fw0x03r);
    fclose(fw0x03i);
    fclose(fw0x04r);
    fclose(fw0x04i);
    fclose(fw0x05);
    fclose(fwt);
}

void unpack_vld_data_complex16(uint8_t *adcnt, uint32_t len, int16_t *datar, int16_t *datai)
{
    int32_t i;
    uint8_t *pr;
    uint8_t *pwr, *pwi;
    pr = adcnt;
    pwr = (uint8_t *)datar;
    pwi = (uint8_t *)datai;
    for (i = 0; i < len; i++)
    {
        *pwr = pr[1];
        pwr++;
        *pwr = pr[0];
        pwr++;
        *pwi = pr[3];
        pwi++;
        *pwi = pr[2];
        pwi++;
        pr += 4;
    }
}

void unpack_vld_data_int32(uint8_t *adcnt, uint32_t len, int32_t *data32)
{
    int32_t i;
    uint8_t *pr, *pw;
    pr = adcnt;
    pw = (uint8_t *)data32;
    for(i=0;i<len;i++)
    {
        *pw = pr[3];
        pw++;
        *pw = pr[2];
        pw++;
        *pw = pr[1];
        pw++;
        *pw = pr[0];
        pw++;
        pr+=4;
    }
}