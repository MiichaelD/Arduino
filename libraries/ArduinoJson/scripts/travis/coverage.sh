#!/bin/sh -eux

curl https://cmake.org/files/v3.4/cmake-3.4.0-Linux-x86_64.tar.gz | tar xz -C /tmp --strip 1

/tmp/bin/cmake -DCOVERAGE=true .
make 
make test

<<<<<<< HEAD
pip install --user cpp-coveralls
=======
pip install --user cpp-coveralls 'requests[security]'
>>>>>>> a85ee8ecf3a469793e1c498c42d585f92528171f
coveralls --exclude third-party --gcov-options '\-lp'; fi
