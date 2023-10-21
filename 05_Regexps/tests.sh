#!/bin/bash

if [ "$(echo '123123' | sed -E 's/(12|23)/0/')" != "$(./esub '(12|23)' '0' '123123')" ]; then
    echo "Tests failed."
    exit 1
fi

if [ "$(echo '123\123' | sed -E 's/\\/0/')" != "$(./esub '\\' '0' '123\123')" ]; then
    echo "Tests failed."
    exit 1
fi

if [ "$(echo '123123' | sed -E 's/([12]).*\1/0/')" != "$(./esub '([12]).*\1' '0' '123123')" ]; then
    echo "Tests failed."
    exit 1
fi
