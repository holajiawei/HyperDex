#!/bin/sh

python2 "${HYPERDEX_SRCDIR}"/test/runner.py --space="space kv key k attributes document v" --daemons=1 -- \
    python2 "${HYPERDEX_SRCDIR}"/bench/documents/multidoc_atomic_add.py {HOST} {PORT}
