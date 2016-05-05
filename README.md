# mod_authn_yubikey


###### Setup local config files
To add the user frank.nord with the password foobar123 and the token id abcdefghijkl you have to do:

```
htpasswd -csb $your_yubikeyConfigLocation/…/yubikey/ykUserDb abcdefghijkl frank.nord:foobar123
```

```
cat ../yubikey/ykUserDb
abcdefghijkl:{SHA}l7xgM5Yq0sDBK6CYZmSwDKuEiAY=
```

Now you can edit your Apache Config (tested on Apache2 2.2.22-13+deb7u3 with Debian wheezy >=7.5)

###### Apache Sample Config
```
<Location /yubitest>
AuthType Basic
AuthBasicProvider yubikey
AuthName "Please Log In using your YubiKey"
AuthYubiKeyTimeout 30
AuthYubiKeyTmpFile yubikey/ykTmpDb
AuthYubiKeyUserFile yubikey/ykUserDb
AuthYubiKeyRequireSecure On
AuthYubiKeyExternalErrorPage Off

AuthYkValidationProtocol https
AuthYkValidationHost api.yubico.com

Require valid-user
</Location>
```

You can also define your fav. choice of your AuthYkValidationProtocol http or https or … 
