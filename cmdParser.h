/*
 * cmdParser.h
 *
 *  Created on: Jan 27, 2015
 *      Author: Conghui He (heconghui@gmail.com)
 */

#ifndef CMDPARSER_H_
#define CMDPARSER_H_

#include <boost/program_options.hpp>
#include <string>

namespace po = boost::program_options;

class CMDParser {
 public:
  CMDParser(int argc, char **argv);
  const std::string &getParfilePath() const;

 private:
  po::options_description mDesc;
  po::variables_map mVarMap;
  std::string mParfile;
};

#endif /* CMDPARSER_H_ */
