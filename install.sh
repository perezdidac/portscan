#!/bin/bash

echo "Compiling..."
make
echo "Compilation completed"

echo "Installing the binaries..."
cp bin/portscan /usr/bin/.
echo "Binaries installed"

echo "Generating Doxygen documentation..."
doxygen
doxygen
echo "Doxygen documentation installed"

echo "Installing the man pages..."
cp doc/portscan.1 doc/portscan.1.bak
gzip doc/portscan.1
cp doc/portscan.1.gz /usr/share/man/man1/.
mv doc/portscan.1.bak doc/portscan.1
echo "Man pages installed"

man portscan

firefox doc/html/index.html &

echo "portscan 0.3 installation completed"
