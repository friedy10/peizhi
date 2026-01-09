#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <address>"
    echo "Example: $0 0xdeadbeef"
    exit 1
fi

ADDR=$1
DEBUGFS_FILE="/sys/kernel/debug/e1000e_mod/next_rx_addr"

if [ ! -f "$DEBUGFS_FILE" ]; then
    echo "Error: DebugFS file $DEBUGFS_FILE not found."
    echo "Is the e1000e module loaded?"
    exit 1
fi

echo "Setting next RX buffer address to $ADDR"
echo "$ADDR" > "$DEBUGFS_FILE"

if [ $? -eq 0 ]; then
    echo "Success. Check dmesg for confirmation after sending a packet."
else
    echo "Failed to write to debugfs."
    exit 1
fi
