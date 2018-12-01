#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "info_pkg_head.h"
#include "data_pkg_head.h"

// #define PRINTF_DEFINE
#define STATISTICS

#define MAX_FRAME_NUM 100
#define RX_ANT_NUM 4

void unpack_vld_data_complex16(uint8_t *adcnt, uint32_t len, int16_t *datar, int16_t *datai);
void unpack_vld_data_int32(uint8_t *adcnt, uint32_t len, int32_t *data32);

int main(int argc, char **argv)
{
#ifndef PRINTF_DEFINE
    FILE *fr;
    FILE *fw;
    FILE *fwt;
    int32_t i;
    char *ptr_filename;
    info_pkg_head_t iph;
    data_pkg_head_t dph;
    data_info_t dit;

    switch (argc)
    {
    case 1:
        fr = fopen("vld_data.bin", "rb");
        if (fr == NULL)
        {
            printf("ERROR: FILE \"%s\" DOSE NOT EXISIT.\n", "vld_data.bin");
            return -1;
        }
        break;
    case 3:
        if (strcmp(argv[1], "-i") == 0)
        {
            fr = fopen(argv[2], "rb");
            if (fr == NULL)
            {
                printf("ERROR: FILE \"%s\" DOSE NOT EXISIT.\n", argv[2]);
                return -1;
            }
        }
        else
        {
            printf("USAGE ERROR.\nUSAGE: ./main [-f] [filename]\n");
            return -1;
        }
        break;
    default:
        printf("USAGE ERROR.\nUSAGE: ./main [-f] [filename]\n");
        return -1;
    }

    fw = fopen("data.txt", "w+");
    FILE *fw_t03a00r = fopen("type03/type03_ant00r.txt", "w+");
    FILE *fw_t03a00i = fopen("type03/type03_ant00i.txt", "w+");
    FILE *fw_t03a01r = fopen("type03/type03_ant01r.txt", "w+");
    FILE *fw_t03a01i = fopen("type03/type03_ant01i.txt", "w+");
    FILE *fw_t03a02r = fopen("type03/type03_ant02r.txt", "w+");
    FILE *fw_t03a02i = fopen("type03/type03_ant02i.txt", "w+");
    FILE *fw_t03a03r = fopen("type03/type03_ant03r.txt", "w+");
    FILE *fw_t03a03i = fopen("type03/type03_ant03i.txt", "w+");
    FILE *fw_t04a00r = fopen("type04/type04_ant00r.txt", "w+");
    FILE *fw_t04a00i = fopen("type04/type04_ant00i.txt", "w+");
    FILE *fw_t04a01r = fopen("type04/type04_ant01r.txt", "w+");
    FILE *fw_t04a01i = fopen("type04/type04_ant01i.txt", "w+");
    FILE *fw_t04a02r = fopen("type04/type04_ant02r.txt", "w+");
    FILE *fw_t04a02i = fopen("type04/type04_ant02i.txt", "w+");
    FILE *fw_t04a03r = fopen("type04/type04_ant03r.txt", "w+");
    FILE *fw_t04a03i = fopen("type04/type04_ant03i.txt", "w+");
    FILE *fw_t05a00 = fopen("type05/type05_ant00.txt", "w+");
    FILE *fw_t05a01 = fopen("type05/type05_ant01.txt", "w+");
    FILE *fw_t05a02 = fopen("type05/type05_ant02.txt", "w+");
    FILE *fw_t05a03 = fopen("type05/type05_ant03.txt", "w+");
    FILE *fw_t11a00sf02r = fopen("type11/type11_ant00_sf02r.txt", "w+");
    FILE *fw_t11a00sf02i = fopen("type11/type11_ant00_sf02i.txt", "w+");
    FILE *fw_t11a00sf03r = fopen("type11/type11_ant00_sf03r.txt", "w+");
    FILE *fw_t11a00sf03i = fopen("type11/type11_ant00_sf03i.txt", "w+");
    FILE *fw_t11a00sf04r = fopen("type11/type11_ant00_sf04r.txt", "w+");
    FILE *fw_t11a00sf04i = fopen("type11/type11_ant00_sf04i.txt", "w+");
    FILE *fw_t11a01sf02r = fopen("type11/type11_ant01_sf02r.txt", "w+");
    FILE *fw_t11a01sf02i = fopen("type11/type11_ant01_sf02i.txt", "w+");
    FILE *fw_t11a01sf03r = fopen("type11/type11_ant01_sf03r.txt", "w+");
    FILE *fw_t11a01sf03i = fopen("type11/type11_ant01_sf03i.txt", "w+");
    FILE *fw_t11a01sf04r = fopen("type11/type11_ant01_sf04r.txt", "w+");
    FILE *fw_t11a01sf04i = fopen("type11/type11_ant01_sf04i.txt", "w+");
    FILE *fw_t11a02sf02r = fopen("type11/type11_ant02_sf02r.txt", "w+");
    FILE *fw_t11a02sf02i = fopen("type11/type11_ant02_sf02i.txt", "w+");
    FILE *fw_t11a02sf03r = fopen("type11/type11_ant02_sf03r.txt", "w+");
    FILE *fw_t11a02sf03i = fopen("type11/type11_ant02_sf03i.txt", "w+");
    FILE *fw_t11a02sf04r = fopen("type11/type11_ant02_sf04r.txt", "w+");
    FILE *fw_t11a02sf04i = fopen("type11/type11_ant02_sf04i.txt", "w+");
    FILE *fw_t11a03sf02r = fopen("type11/type11_ant03_sf02r.txt", "w+");
    FILE *fw_t11a03sf02i = fopen("type11/type11_ant03_sf02i.txt", "w+");
    FILE *fw_t11a03sf03r = fopen("type11/type11_ant03_sf03r.txt", "w+");
    FILE *fw_t11a03sf03i = fopen("type11/type11_ant03_sf03i.txt", "w+");
    FILE *fw_t11a03sf04r = fopen("type11/type11_ant03_sf04r.txt", "w+");
    FILE *fw_t11a03sf04i = fopen("type11/type11_ant03_sf04i.txt", "w+");
    fwt = fopen("test.txt", "w+");
    uint8_t data[INFO_PKG_LEN];
    int16_t datar[DATA_PKG_DATA_LEN / 4];
    int16_t datai[DATA_PKG_DATA_LEN / 4];
    int32_t data32[DATA_PKG_DATA_LEN / 4];
    uint8_t *datav = data + INFO_PKG_HEAD_LEN + DATA_PKG_HEAD_LEN;

#ifdef STATISTICS
    int8_t start_flag = 0;
    uint16_t start_frame;
    while (fread(data, sizeof(uint8_t), INFO_PKG_LEN, fr))
    {
        get_info_pkg_head(&iph, data);
        get_data_pkg_head(&dph, data + INFO_PKG_HEAD_LEN);

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
                switch (dph.src_dev)
                {
                case 0x00:
                    switch (dit.subframe_num)
                    {
                    case 2:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a00sf02r, "%d ", datar[i]);
                            fprintf(fw_t11a00sf02i, "%d ", datai[i]);
                        }
                        break;
                    case 3:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a00sf03r, "%d ", datar[i]);
                            fprintf(fw_t11a00sf03i, "%d ", datai[i]);
                        }
                        break;
                    case 4:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a00sf04i, "%d ", datar[i]);
                            fprintf(fw_t11a00sf04r, "%d ", datai[i]);
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                case 0x01:
                    switch (dit.subframe_num)
                    {
                    case 2:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a01sf02r, "%d ", datar[i]);
                            fprintf(fw_t11a01sf02i, "%d ", datai[i]);
                        }
                        break;
                    case 3:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a01sf03r, "%d ", datar[i]);
                            fprintf(fw_t11a01sf03i, "%d ", datai[i]);
                        }
                        break;
                    case 4:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a01sf04i, "%d ", datar[i]);
                            fprintf(fw_t11a01sf04r, "%d ", datai[i]);
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                case 0x02:
                    switch (dit.subframe_num)
                    {
                    case 2:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a02sf02r, "%d ", datar[i]);
                            fprintf(fw_t11a02sf02i, "%d ", datai[i]);
                        }
                        break;
                    case 3:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a02sf03r, "%d ", datar[i]);
                            fprintf(fw_t11a02sf03i, "%d ", datai[i]);
                        }
                        break;
                    case 4:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a02sf04i, "%d ", datar[i]);
                            fprintf(fw_t11a02sf04r, "%d ", datai[i]);
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                case 0x03:
                    switch (dit.subframe_num)
                    {
                    case 2:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a03sf02r, "%d ", datar[i]);
                            fprintf(fw_t11a03sf02i, "%d ", datai[i]);
                        }
                        break;
                    case 3:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a03sf03r, "%d ", datar[i]);
                            fprintf(fw_t11a03sf03i, "%d ", datai[i]);
                        }
                        break;
                    case 4:
                        for (i = 0; i < dph.data_len; i++)
                        {
                            fprintf(fw_t11a03sf04i, "%d ", datar[i]);
                            fprintf(fw_t11a03sf04r, "%d ", datai[i]);
                        }
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case 0x03:
                unpack_vld_data_complex16(datav, dph.data_len, datar, datai);
                switch (dph.src_dev)
                {
                case 0x00:
                    for (i = 0; i < dph.data_len; i++)
                    {
                        fprintf(fw_t03a00r, "%d ", datar[i]);
                        fprintf(fw_t03a00i, "%d ", datai[i]);
                    }
                    break;
                case 0x01:
                    for (i = 0; i < dph.data_len; i++)
                    {
                        fprintf(fw_t03a01r, "%d ", datar[i]);
                        fprintf(fw_t03a01i, "%d ", datai[i]);
                    }
                    break;
                case 0x02:
                    for (i = 0; i < dph.data_len; i++)
                    {
                        fprintf(fw_t03a02r, "%d ", datar[i]);
                        fprintf(fw_t03a02i, "%d ", datai[i]);
                    }
                    break;
                case 0x03:
                    for (i = 0; i < dph.data_len; i++)
                    {
                        fprintf(fw_t03a03r, "%d ", datar[i]);
                        fprintf(fw_t03a03i, "%d ", datai[i]);
                    }
                    break;
                default:
                    break;
                }
                break;
            case 0x04:
                unpack_vld_data_complex16(datav, dph.data_len, datar, datai);
                switch (dph.src_dev)
                {
                case 0x00:
                    for (i = 0; i < dph.data_len; i++)
                    {
                        fprintf(fw_t04a00r, "%d ", datar[i]);
                        fprintf(fw_t04a00i, "%d ", datai[i]);
                    }
                    break;
                case 0x01:
                    for (i = 0; i < dph.data_len; i++)
                    {
                        fprintf(fw_t04a01r, "%d ", datar[i]);
                        fprintf(fw_t04a01i, "%d ", datai[i]);
                    }
                    break;
                case 0x02:
                    for (i = 0; i < dph.data_len; i++)
                    {
                        fprintf(fw_t04a02r, "%d ", datar[i]);
                        fprintf(fw_t04a02i, "%d ", datai[i]);
                    }
                    break;
                case 0x03:
                    for (i = 0; i < dph.data_len; i++)
                    {
                        fprintf(fw_t04a03r, "%d ", datar[i]);
                        fprintf(fw_t04a03i, "%d ", datai[i]);
                    }
                    break;
                default:
                    break;
                }
                break;
            case 0x05:
                unpack_vld_data_int32(datav, dph.data_len, data32);
                switch (dph.src_dev)
                {
                case 0x00:
                    for (i = 0; i < dph.data_len; i++)
                        fprintf(fw_t05a00, "%d ", data32[i]);
                    break;
                case 0x01:
                    for (i = 0; i < dph.data_len; i++)
                        fprintf(fw_t05a01, "%d ", data32[i]);
                    break;
                case 0x02:
                    for (i = 0; i < dph.data_len; i++)
                        fprintf(fw_t05a02, "%d ", data32[i]);
                    break;
                case 0x03:
                    for (i = 0; i < dph.data_len; i++)
                        fprintf(fw_t05a03, "%d ", data32[i]);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
    }
#endif

    fclose(fr);
    fclose(fw);
    fclose(fw_t03a00r);
    fclose(fw_t03a00i);
    fclose(fw_t03a01r);
    fclose(fw_t03a01i);
    fclose(fw_t03a02r);
    fclose(fw_t03a02i);
    fclose(fw_t03a03r);
    fclose(fw_t03a03i);
    fclose(fw_t04a00r);
    fclose(fw_t04a00i);
    fclose(fw_t04a01r);
    fclose(fw_t04a01i);
    fclose(fw_t04a02r);
    fclose(fw_t04a02i);
    fclose(fw_t04a03r);
    fclose(fw_t04a03i);
    fclose(fw_t05a00);
    fclose(fw_t05a01);
    fclose(fw_t05a02);
    fclose(fw_t05a03);
    fclose(fw_t11a00sf02r);
    fclose(fw_t11a00sf02i);
    fclose(fw_t11a00sf03r);
    fclose(fw_t11a00sf03i);
    fclose(fw_t11a00sf04r);
    fclose(fw_t11a00sf04i);
    fclose(fw_t11a01sf02r);
    fclose(fw_t11a01sf02i);
    fclose(fw_t11a01sf03r);
    fclose(fw_t11a01sf03i);
    fclose(fw_t11a01sf04r);
    fclose(fw_t11a01sf04i);
    fclose(fw_t11a02sf02r);
    fclose(fw_t11a02sf02i);
    fclose(fw_t11a02sf03r);
    fclose(fw_t11a02sf03i);
    fclose(fw_t11a02sf04r);
    fclose(fw_t11a02sf04i);
    fclose(fw_t11a03sf02r);
    fclose(fw_t11a03sf02i);
    fclose(fw_t11a03sf03r);
    fclose(fw_t11a03sf03i);
    fclose(fw_t11a03sf04r);
    fclose(fw_t11a03sf04i);
    fclose(fwt);
#else
    for (uint8_t i = 0x03; i <= 0x04; i++)
        for (uint8_t j = 0x00; j <= 0x03; j++)
        {
            printf("FILE *fw_t%02Xa%02Xr = fopen(\"type%02X/type%02X_ant%02Xr.txt\", \"w+\");\n", i, j, i, i, j);
            printf("FILE *fw_t%02Xa%02Xi = fopen(\"type%02X/type%02X_ant%02Xi.txt\", \"w+\");\n", i, j, i, i, j);
        }

    for (uint8_t i = 0x05; i <= 0x05; i++)
        for (uint8_t j = 0x00; j <= 0x03; j++)
            printf("FILE *fw_t%02Xa%02X = fopen(\"type%02X/type%02X_ant%02X.txt\", \"w+\");\n", i, j, i, i, j);

    for (uint8_t i = 0x11; i <= 0x11; i++)
        for (uint8_t j = 0x00; j <= 0x03; j++)
            for (uint8_t k = 0x02; k <= 0x04; k++)
            {
                printf("FILE *fw_t%02Xa%02Xsf%02Xr = fopen(\"type%02X/type%02X_ant%02X_sf%02Xr.txt\", \"w+\");\n", i, j, k, i, i, j, k);
                printf("FILE *fw_t%02Xa%02Xsf%02Xi = fopen(\"type%02X/type%02X_ant%02X_sf%02Xi.txt\", \"w+\");\n", i, j, k, i, i, j, k);
            }
    printf("\n");

    for (uint8_t i = 0x03; i <= 0x04; i++)
        for (uint8_t j = 0x00; j <= 0x03; j++)
        {
            printf("fclose(fw_t%02Xa%02Xr);\n", i, j);
            printf("fclose(fw_t%02Xa%02Xi);\n", i, j);
        }

    for (uint8_t i = 0x05; i <= 0x05; i++)
        for (uint8_t j = 0x00; j <= 0x03; j++)
            printf("fclose(fw_t%02Xa%02X);\n", i, j);

    for (uint8_t i = 0x11; i <= 0x11; i++)
        for (uint8_t j = 0x00; j <= 0x03; j++)
            for (uint8_t k = 0x02; k <= 0x04; k++)
            {
                printf("fclose(fw_t%02Xa%02Xsf%02Xr);\n", i, j, k);
                printf("fclose(fw_t%02Xa%02Xsf%02Xi);\n", i, j, k);
            }
#endif

    return 0;
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
    for (i = 0; i < len; i++)
    {
        *pw = pr[3];
        pw++;
        *pw = pr[2];
        pw++;
        *pw = pr[1];
        pw++;
        *pw = pr[0];
        pw++;
        pr += 4;
    }
}