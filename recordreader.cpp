/*
 * recordreader.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: heconghui@gmail.com
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "logger.h"

#include "recordreader.h"

namespace {

class AddOptionVisitor : public boost::static_visitor<>
{
public:
  AddOptionVisitor(po::options_description &desc) : mItemDesc(desc) {}

  template <typename T>
  void operator()(const Record<T> *record) {
    mItemDesc.add_options()(record->name.c_str(),
        po::value<T>()->default_value(record->value),
        record->name.c_str());
  }

private:
    po::options_description &mItemDesc;
};

class ReadOptionVisitor : public boost::static_visitor<>
{
  typedef boost::variant<bool, short, int, long, float, double, std::string> generic_value_t;

public:
  ReadOptionVisitor(po::variables_map &map) : mVarMap(map) {}

  template <typename value_type>
  void operator()(Record<value_type> *record) {
    if (mVarMap.count(record->name)) {
      std::string name = record->name;
      record->value = mVarMap[name].as<value_type>();

      removeQuotes(record->value);
    }
  }

private:
  template <typename value_type>
  void removeQuotes(value_type &value) {
    generic_value_t variant(value);

    if ( std::string* pstr = boost::get<std::string>( &variant ) ) {
      boost::erase_all(*pstr, "\"");
    }

    value = *boost::get<value_type>(&variant);
  }

private:
  po::variables_map &mVarMap;

};

class PrintVisitor : public boost::static_visitor<>
{
public:
  template <typename T>
  void operator()(const Record<T> *record) {
    INFO() << record->name << " = " << record->value;
  }
};

} /// end of anonymous name space

void RecordReader::read(const std::string& filename) {
  registerRecord();

  AddOptionVisitor addVisitor(mRecordDesc);
  std::for_each(mRecordVector.begin(), mRecordVector.end(), boost::apply_visitor(addVisitor));

  this->stroeAndNotify(filename);

  ReadOptionVisitor readVisitor(mRecordMap);
  std::for_each(mRecordVector.begin(), mRecordVector.end(), boost::apply_visitor(readVisitor));

  this->postProcess();
}

void RecordReader::stroeAndNotify(const std::string& filename) {

  try {
    std::ifstream ifs(filename.c_str());

    if (!ifs) {
      ERROR() << "cannot open config file: " << filename;
      exit(EXIT_FAILURE);
    }

    po::store(po::parse_config_file(ifs, mRecordDesc), mRecordMap);
    notify(mRecordMap);

    ifs.close();
  } catch (std::exception &e) {
    ERROR() << e.what();
    exit(EXIT_FAILURE);
  }
}

void RecordReader::print() const {
  PrintVisitor visitor;
  std::for_each(mRecordVector.begin(), mRecordVector.end(), boost::apply_visitor(visitor));
}

RecordReader::RecordReader() : mRecordDesc("Allowed Options"), mRecordMap(), mRecordVector()
{

}

RecordReader::~RecordReader() {
}

