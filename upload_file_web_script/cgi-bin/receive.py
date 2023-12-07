#!/usr/bin/env python3

import cgi

# the browser expects this, as part of HTTP protocol
print("Content-Type: text/html\x0d\x0a\x0d\x0a", end='')

form = cgi.FieldStorage()

if 'file' in form:
    field = form['file']
    with open(field.filename, 'wb') as fp:
        fp.write(field.value)

    print('OK')
else:
    print('ERROR')
