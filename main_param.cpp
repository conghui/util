/*
 * main_param.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: heconghui@gmail.com
 */

#include "logger.h"
#include "paramTemplate.h"

int main() {
  DEBUG() << "HELLO";
  INFO() << "INFO";

  ParamTemplate job;
  job.read("param.cfg");
  INFO() << job.getStringRecord();
  INFO() << job.getIntRecord();
  INFO() << job.getFloatRecord();
  job.print();

  return 0;
}


