#include "infrastructure/gonogo/gonogo.hh"

#include <string>

namespace jet {

GoNoGo::GoNoGo() {
    gonogomessage_.bq_name = "";
    comms_factory_ = std::move(std::make_unique<jet::MqttCommsFactory>());
    publisher_ = comms_factory_->make_publisher("GoNoGo");
}

void GoNoGo::setName(std::string name) {
    gonogomessage_.bq_name = name;
}

void GoNoGo::go() {
    gonogomessage_.ready = true;
    // for now this is an empty message because the message type won't compile with an optional string
    gonogomessage_.status_message = "";
    publish_status();
}

void GoNoGo::nogo(const std::string &status_message) {
    gonogomessage_.ready = false;
    gonogomessage_.status_message = status_message;
    publish_status();
}

void GoNoGo::publish_status() {
    publisher_->publish(gonogomessage_);
}

} // namespace jet