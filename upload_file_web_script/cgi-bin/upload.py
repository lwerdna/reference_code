#!/usr/bin/env python3

import cgi

# the browser expects this, as part of HTTP protocol
print("Content-Type: text/html\x0d\x0a\x0d\x0a", end='')

form = cgi.FieldStorage()

if 'file_name' in form:
    file_name = form['file_name'].value
    file_data = form['file_data'].value

    with open(file_name, 'wb') as fp:
        fp.write(file_data)

    print(f'Successfully saved {len(file_data)} bytes to {file_name}.')

else:
    print(f'ERROR: This shouldn\'t be accessed manually, but from the client\'s javascript.')
