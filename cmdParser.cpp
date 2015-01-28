/*
 * cmdParser.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: Conghui He (heconghui@gmail.com)
 */

#include <exception>
#include <iostream>
#include <cstdlib>

#include "logger.h"
#include "cmdParser.h"

CMDParser::CMDParser(int argc, char** argv) :
  mDesc("Allowed options"), mVarMap(), mParfile()
{
  mDesc.add_options()
                      ("help,h", "produce this help message")
                      ("parfile,f", po::value<std::string>(&mParfile)->default_value("param.cfg"),
                          "parameter file, read param.cfg if it is not set")
                          ;

  po::variables_map &vm = mVarMap;
  po::store(po::parse_command_line(argc, argv, mDesc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << mDesc << "\n";
    exit(EXIT_SUCCESS);
  }

  if (mParfile == "param.cfg") {
    WARNING() << "parameter file is not set, use param.cfg as default";
  }

}

const std::string& CMDParser::getParfilePath() const {
  return mParfile;
}
