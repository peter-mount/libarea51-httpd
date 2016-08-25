#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <area51/log.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

int webserver_lock(WEBSERVER *webserver) {
    return pthread_mutex_lock(&webserver->mutex);
}

void webserver_unlock(WEBSERVER *webserver) {
    pthread_mutex_unlock(&webserver->mutex);
}
