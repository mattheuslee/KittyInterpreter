#include <kitty.hpp>
#include <kitty/stl_impl.hpp>
#include <ArduinoUnit.h>
#include <string>

#include <test/interpreter_test.hpp>
#include <test/parser_test.hpp>
#include <test/tokenizer_test.hpp>
#include <test/string_utils_test.hpp>

void setup() {
    Serial.begin(115200);
    while (!Serial);
    Test::exclude("*");
    Test::include("interpreter*");
    Test::include("parser*");
    //Test::include("tokenizer*");
    //Test::include("string_utils*");
}

void loop() {
    Test::run();
}