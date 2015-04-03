/*
 * main_param.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: heconghui@gmail.com
 */

#include "logger.h"
#include "paramTemplate.h"
#include "cmdParser.h"

int main(int argc, char **argv) {
  DEBUG() << "HELLO";
  INFO() << "INFO";

  CMDParser cmdParser(argc, argv);
  ParamTemplate job;
  job.read(cmdParser.getParfilePath());
  INFO() << job.getStringRecord();
  INFO() << job.getIntRecord();
  INFO() << job.getFloatRecord();
  job.print();

  return 0;
}


