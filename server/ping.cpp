#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "settings.h"
#include "api/app/app.h"

using namespace std;

bool isActive = true;

void setInterval(std::function<void (void)> function) {
    thread pingThread([=]() {
        while(true) {
            std::this_thread::sleep_for(5s);
            function();
        }
    });
    pingThread.detach();
}


namespace ping {

    void receivePing() {
        isActive = true;
    }

    void pingTick() {
        if(!isActive) {
            app::exit();
        }
        isActive = false;
    }

    void startPingReceiver() {
        if(settings::getMode() == "browser") {
            setInterval([]() {
                pingTick();
            });
        }
    }

}
