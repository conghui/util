/*
 * log.h
 *
 *  Created on: Oct 19, 2014
 *      Author: heconghui@gmail.com
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <boost/log/trivial.hpp>
#include <boost/format.hpp>
#include <cstdlib>

using boost::format;

/**
 * macros for users, the severity level from lightest to heaviest is:
 * trace < debug < info < warning < error < fatal
 */
#define LOG(logLevel) BOOST_LOG_SEV(Logger::instance().get(), logLevel)
#define TRACE() LOG(boost::log::trivial::trace) << "  "
#define DEBUG() LOG(boost::log::trivial::debug)
#define INFO()  LOG(boost::log::trivial::info)
#define WARNING() LOG(boost::log::trivial::warning)
#define ERROR() LOG(boost::log::trivial::error)
#define FATAL() LOG(boost::log::trivial::fatal)

/**
 * This class is a singleton class that takes charge of logging
 * each process (counting from 0) will keep its log to a different file
 * name after its rank.
 */
class Logger {
 public:
  enum LOG_FILENAME_TIMESTAMP {
    NO_TIMESTAMP, ADD_TIMESTAMP
  };

 public:
  typedef boost::log::trivial::severity_level severity_level_t;
  typedef boost::log::sources::severity_logger<severity_level_t> logger_t;

 public:
  static Logger &instance();

  logger_t &get() {
    return mLg;
  }

  void init(const std::string &logPrefix,
            severity_level_t logLevel = boost::log::trivial::debug,
            LOG_FILENAME_TIMESTAMP timestamp = NO_TIMESTAMP,
            int rank = -1);

 private:
  void setLogger(const std::string &filename, severity_level_t logLevel);

  Logger() : mLg() {}
  Logger(const Logger &);
  Logger &operator=(const Logger &);

 private:
  logger_t mLg;
};

#endif /* LOG_H_ */
