/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

void webserver_set_defaults(WEBSERVER *webserver) {

    // Default to 8080 if not set on the command line
    if (!webserver->port) {
        webserver->port = 8080;
    }

    // If neither IPv4 or IPv6 selected on command line default to IPv4
    if (webserver->stack == 0) {
        webserver->stack = STACK_IPv4;
    }

}
