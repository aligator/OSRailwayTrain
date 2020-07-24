#ifndef WEB_H_
#define WEB_H_

#include "Arduino.h"

class Web {
public:
    Web(const char* ssid, const char* wiFiPassword, const char* hostname, const uint16_t port, const char* otaPassword);
	virtual ~Web();

	void setup();
    void loop();
    
private:
	const char* ssid;
    const char* wiFiPassword;

    const char* hostname;
    uint16_t port;
	const char* otaPassword;


    void _openWiFi();
    void _setupOTA();
};

#endif /* WEB_H_ */