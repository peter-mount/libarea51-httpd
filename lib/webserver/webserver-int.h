
#ifndef WEBSERVER_INT_H
#define WEBSERVER_INT_H

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/hashmap.h>
#include <area51/list.h>
#include <area51/webserver.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct webserverRequest {
        // The underlying WEBSERVER
        WEBSERVER *webserver;
        // The handler invoking the request
        WEBSERVER_HANDLER *handler;
        // The underlying connection for the request
        struct MHD_Connection *connection;
        // the url requested
        const char *url;
        // the method, eg "GET"
        const char *method;
        // Http version
        const char *version;
        // Uploaded data
        const char *upload_data;
        size_t *upload_data_size;
        // Request scope parameters (optional)
        Hashmap *requestScope;
    } WEBSERVER_REQUEST;

    struct webserver {
        // The port we will listen on
        int port : 16;
        // 1 IPv4 support, 2 IPv6, 4=both
        int stack : 2;
        // Our static response handlers
        Hashmap *responseHandlers;
        //
        struct MHD_Response *homePageResponse;
        // Not found Response
        struct MHD_Response *notFoundResponse;
        // redirection page to the index
        struct MHD_Response *redirectResponse;
        // Internal server error response
        struct MHD_Response *errorResponse;
        // mutex for updating any responses
        pthread_mutex_t mutex;
        // The webserver, one daemon per stack as a single dual stack one listens on ipv6 only
        struct MHD_Daemon *daemon4;
        struct MHD_Daemon *daemon6;
        // Our handlers
        List handlers;
    };

    /**
     * A handler that will respond to a specific URI on the website
     */
    struct webserverHandler {
        Node node;
        // The function to handle this request
        int (*handler)(WEBSERVER_REQUEST *);
        // optional userdata
        void *userdata;
    };

    extern int webserver_lock(WEBSERVER *);
    extern void webserver_unlock(WEBSERVER *);

    extern int webserver_notFoundHandler(WEBSERVER_REQUEST *);
    extern int webserver_staticHandler(WEBSERVER_REQUEST *);

    extern void webserver_freeScope(Hashmap *);
    extern void *webserver_getAttribute(Hashmap *, char *);
    extern int webserver_setAttribute(Hashmap *, char *, void *, void (*)(void *));

#ifdef __cplusplus
}
#endif

#endif /* WEBSERVER_INT_H */

