
#include <Arduino.h>
#include <unity.h>
#include <LightManager.hpp>

LightManager light;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_set_state_passed(void) {
    light.setLight(0,255,0,3);
    String color = "Green";
    String actual = light.getColor();
    TEST_ASSERT_EQUAL_STRING(color.c_str(), actual.c_str());
}

void test_set_state_failed(void) {
    light.setLight(255,0,0,3);
    String color = "Red";
    String actual = light.getColor();
    TEST_ASSERT_EQUAL_STRING(color.c_str(), actual.c_str());
}

void test_set_state_started(void) {
    light.setLight(255,255,0,3);
    String color = "Yellow";
    String actual = light.getColor();
    TEST_ASSERT_EQUAL_STRING(color.c_str(), actual.c_str());
}

void test_set_state_canceled(void) {
    light.setLight(192,192,192,3);
    String color = "Gray";
    String actual = light.getColor();
    TEST_ASSERT_EQUAL_STRING(color.c_str(), actual.c_str());
}

void setup()
{
    delay(2000); // service delay
    UNITY_BEGIN();
    RUN_TEST(test_set_state_passed);
    RUN_TEST(test_set_state_failed);
    RUN_TEST(test_set_state_started);
    RUN_TEST(test_set_state_canceled);
    UNITY_END(); // stop unit testing
}

void loop(){
}
