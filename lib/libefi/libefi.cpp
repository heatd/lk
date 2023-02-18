/*
 * Copyright (c) 2023 Pedro Falcato
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#include "include/lib/libefi.h"

#include <assert.h>
#include <lk/compiler.h>
#include <lk/init.h>

namespace {

void *bootloader_start;
size_t bootloader_len;

};

void libefi_set_bootloader(void *image, size_t len)
{
    bootloader_start = image;
    bootloader_len = len;
}

void _libefi_do_boot(uint level)
{
    
}

LK_INIT_HOOK(libefi_do_boot, _libefi_do_boot, LK_INIT_LEVEL_APPS - 1);
