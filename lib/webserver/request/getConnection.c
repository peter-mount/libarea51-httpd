#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

struct MHD_Connection *webserver_getRequestConnection(WEBSERVER_REQUEST *r) {
    return r->connection;
}
