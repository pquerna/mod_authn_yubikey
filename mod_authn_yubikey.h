#ifndef MOD_AUTHN_YUBIKEY_H
# define MOD_AUTHN_YUBIKEY_H

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include "http_log.h"
#include "mod_auth.h"
#include "libykclient.h"
#include "ap_provider.h"
#include "apr_strings.h"
#include "apr_dbm.h"
#include "apr_time.h"
#include "http_core.h"
#include "http_request.h"

typedef struct
{
  /* This is the actual timeout after which the session finally expires,
   * there is NO recovery from this, so this timeout is not renewed everytime
   * a user makes a request
   */
  int timeoutSeconds;
  /* This flag requires the protected location to be accessed via an secure Url
   * this is especially useful if you use the two factor authentication,
   * since passwords would otherwise be sent in the clear.
   */
  int requireSecure;
  /* If any error happens, this will redirect you to the given error page,
   * or an internally generated error page will be shown. 
   * Use this is you want to customize the error page.
   */
  int externalErrorPage;
  /* This is the temporary filename authenticated user are saved in. 
   * This could possibly be done with an in memory version of s.th. similar
   * to the database
   */
  const char *tmpAuthDbFilename;
  /* This is the file where the actual user/password connection happens. So 
   * the module knows where it can find the file where the tokenId/username 
   * mapping happens.
   */
  const char *userAuthDbFilename;
  /*  
   * This is required to be given if you want to use another authentication 
   * provider which supports the yubikey token, but not via yubicos site.
   */
  const char *validationProtocol;
  const char *validationHost;
} yubiauth_dir_cfg;

static void *create_yubiauth_dir_cfg(apr_pool_t *pool, char *x);

static void *merge_yubiauth_dir_cfg(apr_pool_t *pool, void *BASE, void *ADD);

static const command_rec authn_yubikey_cmds[];

static void authn_yubikey_register_hooks(apr_pool_t *p);

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA authn_yubikey_module;

#endif
