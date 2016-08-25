#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

void *webserver_getUserData(WEBSERVER_REQUEST *r) {
    return r->handler ? r->handler->userdata : NULL;
}
