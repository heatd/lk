/*
 * Copyright (c) 2021 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */

#include <string.h>
#include <stdio.h>
#include <lk/debug.h>
#include <lk/trace.h>
#include <app.h>
#include <lib/minip.h>
#include <kernel/thread.h>

#define LOCAL_TRACE 1

#define IRC_SERVER IPV4(88,99,244,30) // irc.sortix.org
//#define IRC_SERVER IPV4(192,168,1,110) // localhost
#define IRC_USER "geist"
#define IRC_NICK "geist-lk"
#define IRC_CHAN "#sortix"

static void irc_entry(const struct app_descriptor *app, void *args) {
    LTRACE_ENTRY;
    printf("welcome to IRC!\n");

    tcp_socket_t *sock;
    status_t err = tcp_connect(&sock, IRC_SERVER, 6667);
    if (err < 0) {
        printf("err %d connecting to server\n", err);
        return;
    }

    thread_sleep(1000);

    // send USER and NICK
    char buf[1024];
    snprintf(buf, sizeof(buf), "USER %s host server :geist\r\n", IRC_USER);
    err = tcp_write(sock, buf, strlen(buf));
    if (err < 0) {
        printf("error %d writing to server\n", err);
        goto exit;
    }

    snprintf(buf, sizeof(buf), "NICK %s\r\n", IRC_NICK);
    err = tcp_write(sock, buf, strlen(buf));
    if (err < 0) {
        printf("error %d writing to server\n", err);
        goto exit;
    }

    snprintf(buf, sizeof(buf), "JOIN %s\r\n", IRC_CHAN);
    err = tcp_write(sock, buf, strlen(buf));
    if (err < 0) {
        printf("error %d writing to server\n", err);
        goto exit;
    }

    for (;;) {
        ssize_t r = tcp_read(sock, buf, sizeof(buf));
        if (r < 0) {
            break;
        }

        for (ssize_t i = 0; i < r; i++) {
            putchar(buf[i]);
        }
    }


exit:
    tcp_close(sock);

    LTRACE_EXIT;
}

APP_START(irc)
.entry = irc_entry,
.flags = APP_FLAG_NO_AUTOSTART,
APP_END

