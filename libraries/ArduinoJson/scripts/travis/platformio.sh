#!/bin/sh -eux

pip install --user platformio

rm -r test

<<<<<<< HEAD
for EXAMPLE in JsonParserExample JsonGeneratorExample
do
	platformio ci examples/$EXAMPLE/$EXAMPLE.ino -l '.' -b $BOARD
=======
for EXAMPLE in $PWD/examples/*/*.ino; 
do
	platformio ci $EXAMPLE -l '.' -b $BOARD
>>>>>>> a85ee8ecf3a469793e1c498c42d585f92528171f
done
