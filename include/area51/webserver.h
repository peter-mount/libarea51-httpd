/* 
 * File:   webserver.h
 * Author: peter
 *
 * Created on February 5, 2014, 8:40 PM
 */

#ifndef AREA51_WEBSERVER_H
#define AREA51_WEBSERVER_H

#include <pthread.h>
#include <microhttpd.h>
#include <stdint.h>
#include <area51/bytebuffer.h>
#include <area51/charbuffer.h>
#include <area51/list.h>
#include <area51/hashmap.h>

#define STACK_IPv4 1
#define STACK_IPv6 2

typedef struct webserverHandler WEBSERVER_HANDLER;

typedef struct webserverRequest WEBSERVER_REQUEST;

typedef struct webserver WEBSERVER;

/**
 * Atomically replaces destResponse with newResponse, disposing the original
 * @param server WEBSERVER
 * @param destResponse Pointer to the pointer to update
 * @param newResponse New response
 */
extern void webserver_replaceResponse(WEBSERVER *webserver, const char *, struct MHD_Response *);
extern void webserver_replaceResponseArray(WEBSERVER *webserver, const char *, void *, int, const char *);
extern void webserver_replaceResponseByteBuffer(WEBSERVER *webserver, const char *, struct bytebuffer *, const char *);
extern void webserver_replaceResponseCharBuffer(WEBSERVER *webserver, const char *, CharBuffer *, const char *);

extern void webserver_setNotFoundResponse(WEBSERVER *, struct MHD_Response *);
extern void webserver_setErrorResponse(WEBSERVER *, struct MHD_Response *);

/**
 * Returns the current value of reponse atomically
 * @param server WEBSERVER
 * @param response Pointer to the pointer to get
 * @return The value at response at the time of the call, NULL if not able to get it
 */
extern struct MHD_Response *webserver_getResponse(WEBSERVER *webserver, const char *);

/**
 * Queues a response to a connection. This does it atomically so that the response will be queued even if another
 * thread replaces the response, i.e. a new camera image.
 * @param connection
 * @param server
 * @param response
 * @return 
 */
extern int webserver_queueResponse(WEBSERVER_REQUEST *, struct MHD_Response **);

extern int webserver_sendResponse(WEBSERVER_REQUEST *, int status, struct MHD_Response *);

extern WEBSERVER_HANDLER *webserver_add_handler(WEBSERVER *, const char *, int (*)(WEBSERVER_REQUEST *), void *);
extern void webserver_add_response_handler(WEBSERVER *, const char *);
extern WEBSERVER *webserver_new();
extern int webserver_getPort(WEBSERVER *);
extern void webserver_setPort(WEBSERVER *, int);
extern void webserver_enableIPv4(WEBSERVER *);
extern void webserver_enableIPv6(WEBSERVER *);
extern void webserver_set_defaults(WEBSERVER *);
extern void webserver_start(WEBSERVER *);
extern void webserver_stop(WEBSERVER *);

extern struct MHD_Connection *webserver_getRequestConnection(WEBSERVER_REQUEST *);
extern const char *webserver_getRequestParameter(WEBSERVER_REQUEST *, const char *);
extern const char *webserver_getRequestMethod(WEBSERVER_REQUEST *);
extern const char *webserver_getRequestUrl(WEBSERVER_REQUEST *);
extern const char *webserver_getRequestVersion(WEBSERVER_REQUEST *);
extern const char *webserver_getRequestUploadData(WEBSERVER_REQUEST *, size_t *);

extern void *webserver_getUserData(WEBSERVER_REQUEST *);

#endif /* AREA51_WEBSERVER_H */

