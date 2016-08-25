/*
 * The embedded webserver
 */

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/list.h>
#include <area51/log.h>
#include <area51/webserver.h>

extern int verbose;

static int handler(void * cls,
        struct MHD_Connection * connection,
        const char * url,
        const char * method,
        const char * version,
        const char * upload_data,
        size_t * upload_data_size,
        void ** ptr) {

    if (0 != strcmp(method, "GET")) {
        /* unexpected method */
        return MHD_NO;
    }

    if (&verbose != *ptr) {
        /* The first time only the headers are valid,
           do not respond in the first round... */
        *ptr = &verbose;
        return MHD_YES;
    }

    if (0 != *upload_data_size) {
        /* upload data in a GET!? */
        return MHD_NO;
    }

    // if -vv then dump each requested url to the console
    if (verbose > 1)
        logconsole("GET %s", url);

    // Find a handler for this url. If we don't find one then the last one gets invoked as its only one with url NULL
    WEBSERVER_HANDLER *h = (WEBSERVER_HANDLER *) list_getHead(&webserver.handlers);
    while (list_isNode(&h->node)) {

        int nl = h->node.name ? strlen(h->node.name) : 0;

        bool match = false;

        // Dynamic paths ending in *
        if (nl > 0 && h->node.name[nl - 1] == '*')
            match = strncmp(url, h->node.name, nl - 1) == 0;

        // Static paths (Not ending in *)
        if (!match)
            match = strcmp(url, h->node.name) == 0;

        if (match) {
            // Clear the pointer
            *ptr = NULL;

            // Call the handler, if it returns MHD_NO then carry on searching
            if (h->handler(connection, h, url) == MHD_YES)
                return MHD_YES;
        }

        h = (WEBSERVER_HANDLER *) h->node.n_succ;
    }

    // Static content?
    if (staticHandler(connection, url) == MHD_YES)
        return MHD_YES;
    else
        return notFoundHandler(connection, NULL);
}

void webserver_start() {
    int flags = MHD_USE_THREAD_PER_CONNECTION;

    if (webserver.stack & STACK_IPv4) {
        if (verbose > 1)
            logconsole("Starting webserver on IPv4 port %d", webserver.port);

        webserver.daemon4 = MHD_start_daemon(
                flags,
                webserver.port,
                NULL, NULL,
                &handler, NULL,
                MHD_OPTION_END);
        if (webserver.daemon4 == NULL) {
            logconsole("Failed to create IPv4 webserver");
            return;
        }
    }

    if (webserver.stack & STACK_IPv6) {
        if (verbose > 1)
            logconsole("Starting webserver on IPv6 port %d", webserver.port);

        webserver.daemon6 = MHD_start_daemon(
                flags | MHD_USE_IPv6,
                webserver.port,
                NULL, NULL,
                &handler, NULL,
                MHD_OPTION_END);
        if (webserver.daemon6 == NULL) {
            logconsole("Failed to create IPv6 webserver");
            return;
        }
    }

    if (verbose > 1)
        logconsole("Webserver started");
}
