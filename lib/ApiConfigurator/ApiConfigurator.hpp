#ifndef ApiConfigurator_HPP
#define ApiConfigurator_HPP

#include <HTTPClient.h>
#include "Arduino.h"
class ApiConfigurator
{

private:
    String url;
    String token;
    String header;
    HTTPClient* httpClient;
    bool apiResponseError;
    String state;
    String previousState;

public:
    ApiConfigurator();
    void getTravisInfo();
    String getUrl();
    String getToken();
    void setUrl(String value);
    void setToken(String value);
    String getHeader();
    void setHeader(String value);
    bool getApiResponseError();
    void setApiResponseError(bool value);
    void setState(String value);
    String getState();
    String getPreviousState();
};

#endif