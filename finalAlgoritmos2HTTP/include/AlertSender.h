#pragma once
#include <iostream>

class IAlertSender {
public:
    virtual void sendAlert() = 0;
    virtual ~IAlertSender() = default;
};

class MailAlertSender : public IAlertSender {
public:
    void sendAlert() override {
    std::cout << "Sending alert via mail" << std::endl;
};
};
