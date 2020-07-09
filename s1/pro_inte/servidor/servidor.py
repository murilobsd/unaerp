#!/usr/bin/env python3
#
# Copyright (c) 2020 Murilo Ijanc' <mbsd@m0x.ru>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

import os
import asyncio
import websockets

USUARIOS = set()


async def register(websocket):
    USUARIOS.add(websocket)


async def unregister(websocket):
    USUARIOS.remove(websocket)


async def notificar_usuarios(msg, websocket):
    if USUARIOS:
        await asyncio.wait([u.send(msg) for u in USUARIOS if u != websocket])


async def hello(websocket, path):
    await register(websocket)

    try:
        async for msg in websocket:
            await notificar_usuarios(msg, websocket)
    finally:
        await unregister(websocket)


def main(host, port):
    start_server = websockets.serve(hello, host, port)
    asyncio.get_event_loop().run_until_complete(start_server)
    print("Start server on: %s:%d" % (host, port))
    asyncio.get_event_loop().run_forever()


if __name__ == '__main__':
    host = os.environ.get("HOST", "192.168.15.38")
    port = int(os.environ.get("PORT", 1234))

    main(host, port)
