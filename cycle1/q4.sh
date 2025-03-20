#!/bin/bash

# Check if a username is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <username>"
    exit 1
fi

username=$1

# Keep checking every 30 seconds until the user logs in
while true; do
    if who | grep -w "$username" > /dev/null; then
        echo "User '$username' has logged in!"
        exit 0
    else
        echo "Checking... User '$username' not logged in yet."
        sleep 30
    fi
done
