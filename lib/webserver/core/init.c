/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/list.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

static const char *errorPage = "<html><head><title>Internal Server Error</title></head><body><h1>Internal Server Error</h1></body></html>";
static const char *notFoundPage = "<html><head><title>Page not found</title></head><body><h1>Page Not Found</h1></body></html>";

WEBSERVER *webserver_new() {
    WEBSERVER *webserver = malloc(sizeof (struct webserver));
    if (!webserver)
        return NULL;

    memset(webserver, 0, sizeof (struct webserver));

    pthread_mutex_init(&webserver->mutex, NULL);

    webserver->port = 0;
    webserver->stack = 0;
    webserver->daemon4 = NULL;
    webserver->daemon6 = NULL;

    webserver->responseHandlers = hashmapCreate(10, hashmapStringHash, hashmapStringEquals);
    list_init(&webserver->handlers);

    // The static responses - these never change
    webserver->errorResponse = MHD_create_response_from_buffer(strlen(errorPage), (void*) errorPage, MHD_RESPMEM_PERSISTENT);
    webserver->notFoundResponse = MHD_create_response_from_buffer(strlen(notFoundPage), (void*) notFoundPage, MHD_RESPMEM_PERSISTENT);

    return webserver;
}

void webserver_enableIPv4(WEBSERVER *webserver) {
    webserver->stack |= STACK_IPv4;
}

void webserver_enableIPv6(WEBSERVER *webserver) {
    webserver->stack |= STACK_IPv6;
}

