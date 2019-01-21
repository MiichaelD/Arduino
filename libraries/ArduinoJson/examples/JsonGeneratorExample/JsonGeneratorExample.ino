<<<<<<< HEAD
// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
=======
// Copyright Benoit Blanchon 2014-2017
// MIT License
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
>>>>>>> a85ee8ecf3a469793e1c498c42d585f92528171f
// If you like this project, please add a star!

#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // wait serial port initialization
  }

  // Memory pool for JSON object tree.
  //
  // Inside the brackets, 200 is the size of the pool in bytes.
  // If the JSON object is more complex, you need to increase that value.
<<<<<<< HEAD
=======
  // See https://bblanchon.github.io/ArduinoJson/assistant/
>>>>>>> a85ee8ecf3a469793e1c498c42d585f92528171f
  StaticJsonBuffer<200> jsonBuffer;

  // StaticJsonBuffer allocates memory on the stack, it can be
  // replaced by DynamicJsonBuffer which allocates in the heap.
<<<<<<< HEAD
  // It's simpler but less efficient.
  //
  // DynamicJsonBuffer  jsonBuffer;
=======
  //
  // DynamicJsonBuffer  jsonBuffer(200);
>>>>>>> a85ee8ecf3a469793e1c498c42d585f92528171f

  // Create the root of the object tree.
  //
  // It's a reference to the JsonObject, the actual bytes are inside the
  // JsonBuffer with all the other nodes of the object tree.
  // Memory is freed when jsonBuffer goes out of scope.
  JsonObject& root = jsonBuffer.createObject();

  // Add values in the object
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do root.set<long>("time", 1351824120);
  root["sensor"] = "gps";
  root["time"] = 1351824120;

  // Add a nested array.
  //
  // It's also possible to create the array separately and add it to the
  // JsonObject but it's less efficient.
  JsonArray& data = root.createNestedArray("data");
<<<<<<< HEAD
  data.add(double_with_n_digits(48.756080, 6));
  data.add(double_with_n_digits(2.302038, 6));
=======
  data.add(48.756080);
  data.add(2.302038);
>>>>>>> a85ee8ecf3a469793e1c498c42d585f92528171f

  root.printTo(Serial);
  // This prints:
  // {"sensor":"gps","time":1351824120,"data":[48.756080,2.302038]}

  Serial.println();

  root.prettyPrintTo(Serial);
  // This prints:
  // {
  //   "sensor": "gps",
  //   "time": 1351824120,
  //   "data": [
  //     48.756080,
  //     2.302038
  //   ]
  // }
}

void loop() {
  // not used in this example
}
