#include "jbd_switch.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace jbd_bms {

static const char *const TAG = "jbd_bms.switch";

void JbdSwitch::dump_config() { LOG_SWITCH("", "JbdBms Switch", this); }
void JbdSwitch::write_state(bool state) {
  ESP_LOGD("JbdSwitch", "SW TOGGLE %d\n", state);
  switch (this->holding_register_) {
    case 0xFA:  // CONF_CHARGING
      this->parent_->must_send_charge_mos_state = true;
      break;
    case 0xF9:
      this->parent_->must_send_discharge_mos_state = true;
      break;
  }

  this->publish_state(state);
}

}  // namespace jbd_bms
}  // namespace esphome
