/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <stdio.h>
#include <area51/log.h>
#include <area51/webserver.h>

extern int verbose;

void webserver_stop() {
    if (webserver.daemon6) {
        if (verbose > 1)
            logconsole("Stopping IPv6 webserver");

        MHD_stop_daemon(webserver.daemon6);
        webserver.daemon6 = NULL;
    }
    if (webserver.daemon4) {
        if (verbose > 1)
            logconsole("Stopping IPv4 webserver");

        MHD_stop_daemon(webserver.daemon4);
        webserver.daemon4 = NULL;
    }
}
