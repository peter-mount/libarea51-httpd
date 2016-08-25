#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

const char *webserver_getRequestUploadData(WEBSERVER_REQUEST *r, size_t *size) {
    if (size)
        *size = r->upload_data_size ? *(r->upload_data_size) : 0;
    return r->upload_data;
}
