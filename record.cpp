/*
 * record.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: heconghui@gmail.com
 */

#include "record.h"

std::ostream &operator<<(std::ostream &os, const Record<std::string> &record) {
  if (!record.value.empty()) {
    os << record.name << "=" << record.value;
  }
  return os;
}


