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

#include <lk/compiler.h>

__BEGIN_CDECLS

void libefi_set_bootloader(void *image, size_t len);

__END_CDECLS
