/*
 * Copyright (c) 2023 Pedro Falcato
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#pragma once

#include <stdint.h>
#include <sys/types.h>

// fw_cfg items

#define FW_CFG_SIGNATURE 0x0
#define FW_CFG_ID        0x1
#define FW_CFG_FILE_DIR  0x19

#define FW_CFG_INITRD_SIZE 0xb
#define FW_CFG_INITRD_DATA 0x12

#define QEMU_FW_CFG_EXPECTED_SIG "QEMU"


// Output of fw_cfg_file_dir

struct fwcfg_file
{
    u32 size;
    u16 select;
    u16 resv;
    char name[56];
};

struct fwcfg_files
{
    u32 count;
    struct fwcfg_file files[];
};

void fwcfg_open(const char *name);
