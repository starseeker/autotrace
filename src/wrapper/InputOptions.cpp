//
// Created by nick on 7/30/18.
//

#include "InputOptions.h"

InputOptions::InputOptions() : _at_input_opts_type() {
  background_color = nullptr;
  charcode = 0;
}

InputOptions::InputOptions(json11::Json inputOptionsJson) :
    InputOptions() {

}

json11::Json InputOptions::toJson() {
  return json11::Json();
}
