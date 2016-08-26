#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <area51/hashmap.h>
#include <area51/memory.h>
#include <area51/webserver.h>
#include "../webserver-int.h"

static bool freeScopeEntry(void *k, void *v, void *c) {
    if (hashmapRemove((Hashmap *) c, k) == v) {
        free(k);
        freeable_free((Freeable *) v);
    }
    return true;
}

void webserver_freeScope(Hashmap *scope) {
    if (scope) {
        hashmapForEach(scope, freeScopeEntry, scope);
        hashmapFree(scope);
    }
}

void *webserver_getAttribute(Hashmap *scope, char *key) {
    if (!key || !key[1] || !scope)
        return NULL;

    return freeable_get((Freeable *) hashmapGet(scope, key));
}

int webserver_setAttribute(Hashmap *scope, char *k, void *v, void (*f)(void *)) {
    if (!scope)
        return EXIT_FAILURE;

    Freeable *val = hashmapGet(scope, k);
    if (val) {
        freeable_set(val, v, f);
    } else {
        char *key = strdup(k);
        if (!key)
            return EXIT_FAILURE;

        val = freeable_new(v, f);
        if (!val) {
            free(key);
            return EXIT_FAILURE;
        }

        hashmapPut(scope, key, val);
    }

    return EXIT_SUCCESS;
}

void *webserver_getRequestAttribute(WEBSERVER_REQUEST *r, char *key) {
    return webserver_getAttribute(r->requestScope, key);
}

int webserver_setRequestAttribute(WEBSERVER_REQUEST *r, char *k, void *v, void (*f)(void *)) {
    if (!r->requestScope)
        r->requestScope = hashmapCreate(10, hashmapStringHash, hashmapStringEquals);

    return webserver_setAttribute(r->requestScope, k, v, f);
}
