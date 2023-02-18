/*
 * Copyright (c) 2023 Pedro Falcato
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#include <string.h>
#include <stdio.h>
#include <arch/x86.h>
#include <endian.h>

#include <lk/err.h>
#include <lk/init.h>
#include "include/fwcfg.h"

#define QEMU_X86_IOSEL 0x510
#define QEMU_X86_DATA  0x511
#define QEMU_X86_DMA   0x514

#ifdef __x86_64__
#define IOSEL_REG QEMU_X86_IOSEL
#define DATA_REG QEMU_X86_DATA
#define DMA_REG QEMU_X86_DMA
#else
#error "Platform not implemented"
#endif

static void fw_cfg_read(u8 *data, u32 len)
{
     while (len--)
        *data++ = inp(DATA_REG);
}

static void fw_cfg_sel(u16 sel)
{
    outpw(IOSEL_REG, sel);
}

static void fw_cfg_read_sel(u16 sel, u8 *data, u32 len)
{
    fw_cfg_sel(sel);
    fw_cfg_read(data, len);
}


// TODO(ask geist): does bool exist in lk?
int fwcfg_is_present(void)
{
    char sig[4];
    fw_cfg_read_sel(FW_CFG_SIGNATURE, (u8*) sig, 4);

    return !memcmp(sig, QEMU_FW_CFG_EXPECTED_SIG, 4);
}

void fwcfg_open(const char *name)
{
    if (fwcfg_is_present())
    {
        printf("fwcfg is present\n");
    }
    else
        return;

    struct fwcfg_files files;
    u8 files_bytes[sizeof(u32)];

    // Go through every file
    fw_cfg_read_sel(FW_CFG_FILE_DIR, files_bytes, sizeof(u32));

    memcpy(&files, files_bytes, sizeof(u32));

    files.count = BE32(files.count);

    printf("number of files: %u\n", files.count);

    for (u32 i = 0; i < files.count; i++)
    {
        struct fwcfg_file file;
        u8 raw[sizeof(file)];

        fw_cfg_read(raw, sizeof(file));

        memcpy(&file, raw, sizeof(file));

        file.size = BE32(file.size);

        printf("fw_cfg file: %s size %u\n", file.name, file.size);        
    }
}

static u32 fw_cfg_read_u32(void)
{
    u32 proper;
    u8 bytes[sizeof(u32)];

    fw_cfg_read(bytes, sizeof(u32));

    memcpy(&proper, bytes, sizeof(u32));
    return proper;
}

void _fwcfg_init(uint level)
{
    fwcfg_open("bazel");
    fw_cfg_sel(FW_CFG_INITRD_SIZE);
    printf("initrd size: %u\n", fw_cfg_read_u32());
}

LK_INIT_HOOK(_fwcfg_init, _fwcfg_init, LK_INIT_LEVEL_APPS - 1);
