#!/bin/bash
if [ "${BASH_SOURCE[0]}" -ef "$0" ]; then
    echo "Hey, you should source this script, not execute it!"
    exit 1
fi

export BOOST_TEST_LOG_LEVEL=message
