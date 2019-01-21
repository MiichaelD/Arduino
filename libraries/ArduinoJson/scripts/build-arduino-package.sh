#!/bin/bash

TAG=$(git describe)
OUTPUT="ArduinoJson-$TAG.zip"

cd $(dirname $0)/../..

# remove existing file
rm -f $OUTPUT

# create zip
7z a $OUTPUT \
	ArduinoJson/CHANGELOG.md \
	ArduinoJson/examples \
<<<<<<< HEAD
	ArduinoJson/include \
=======
	ArduinoJson/src \
>>>>>>> a85ee8ecf3a469793e1c498c42d585f92528171f
	ArduinoJson/keywords.txt \
	ArduinoJson/library.properties \
	ArduinoJson/LICENSE.md \
	ArduinoJson/README.md \
	ArduinoJson/ArduinoJson.h
