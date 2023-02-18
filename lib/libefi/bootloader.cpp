/*
 * Copyright (c) 2023 Pedro Falcato
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#include "include/lib/libefi.h"
#include <lk/err.h>
#include <lk/init.h>

extern char _binary_lib_libefi_vmlinuz_start[];
extern char _binary_lib_libefi_vmlinuz_size[];

void __bldr_init(uint level)
{
    libefi_set_bootloader(_binary_lib_libefi_vmlinuz_start, (size_t) &_binary_lib_libefi_vmlinuz_size);
}

LK_INIT_HOOK(_bldr_init, __bldr_init, LK_INIT_LEVEL_APPS - 1);
