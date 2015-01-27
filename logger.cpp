/*
 * log.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: heconghui@gmail.com
 */

#include <boost/log/core.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <string>
#include "logger.h"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;

void Logger::init(const std::string &logPrefix, int rank, severity_level_t logLevel) {
  using namespace boost::log;

  boost::format fmtr("%s_%%Y%%m%%d-%%H%%M%%S_%d.log");
  fmtr % logPrefix;
  fmtr % rank;

  this->setLogger(fmtr.str(), logLevel);
}

void Logger::init(const std::string& logPrefix, severity_level_t logLevel) {
  using namespace boost::log;

    boost::format fmtr("%s_%%Y%%m%%d-%%H%%M%%S.log");
    fmtr % logPrefix;

    this->setLogger(fmtr.str(), logLevel);
}

void Logger::setLogger(const std::string& filename, severity_level_t logLevel) {
  using namespace boost::log;

  boost::log::add_common_attributes();
  boost::log::add_console_log
  (
    std::cout,
    keywords::format =
    (
        expr::stream
        << "[" << std::setw(5) << std::left << logging::trivial::severity << "] "
        << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S") << ": "
        << expr::smessage
    )
  );

  logging::add_file_log
  (
      boost::log::keywords::file_name = filename,
      keywords::format =
      (
          expr::stream
          << "[" << std::setw(5) << std::left << logging::trivial::severity << "] "
          << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S") << ": "
          << expr::smessage
      ),
      boost::log::keywords::auto_flush = true
  );

  logging::core::get()->set_filter(logging::trivial::severity >= logLevel);
}

Logger& Logger::getInstance() {
  static Logger instance;
  return instance;
}
