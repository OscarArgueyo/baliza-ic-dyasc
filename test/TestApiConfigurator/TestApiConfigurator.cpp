
#include <Arduino.h>
#include <unity.h>
#include <ApiConfigurator.hpp>

ApiConfigurator apiConf;

void setUp(void) {
    // set stuff up here
    apiConf.setUrl(String("https://api.travis-ci.org/repo/25849455/builds?limit=1"));
    apiConf.setToken(String("token sN-LuhyiLh61-Ya2zK-2Xw"));
}

void tearDown(void) {
    // clean stuff up here
    apiConf.setUrl(String(""));
    apiConf.setToken(String(""));
}

void test_get_api_url(void) {
    String urlRepo = "https://api.travis-ci.org/repo/25849455/builds?limit=1";
    String actual = apiConf.getUrl();
    TEST_ASSERT_EQUAL_STRING(urlRepo.c_str(), actual.c_str());
}

void setup()
{
    delay(2000); // service delay
    UNITY_BEGIN();
    RUN_TEST(test_get_api_url);
    UNITY_END(); // stop unit testing
}

void loop(){
}
