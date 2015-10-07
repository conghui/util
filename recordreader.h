/*
 * recordreader.h
 *
 *  Created on: Nov 14, 2014
 *      Author: heconghui@gmail.com
 */

#ifndef RECORDREADER_H_
#define RECORDREADER_H_

#include <boost/variant.hpp>
#include <boost/program_options.hpp>
#include <vector>
#include "record.h"

namespace po = boost::program_options;

class RecordReader {
 public:
  RecordReader();
  virtual ~RecordReader();
  void read(const std::string &filename);
  void print() const;

 protected:
  virtual void registerRecord() = 0;
  virtual void postProcess() {};

 protected:
  template <typename T> void addRecord(Record<T> &record);
  template <typename T> void addRecord(std::vector<Record<T> > &recordVec);
  void stroeAndNotify(const std::string &filename);

 protected:
  RecordReader(const RecordReader &);
  void operator=(const RecordReader &);

 private:
  typedef boost::variant<bool_record_t *, short_record_t *,
          int_record_t *,  float_record_t *,
          double_record_t *, string_record_t *> generic_record_t;

  po::options_description mRecordDesc;
  po::variables_map mRecordMap;
  std::vector<generic_record_t> mRecordVector;
};

template<typename T>
inline void RecordReader::addRecord(Record<T> &record) {
  mRecordVector.push_back(&record);
}

template<typename T>
inline void RecordReader::addRecord(std::vector<Record<T> > &recordVec) {
  for (typename std::vector<Record<T> >::iterator it = recordVec.begin();
       it != recordVec.end(); ++it) {
    mRecordVector.push_back(&(*it));
  }
}

#endif /* RECORDREADER_H_ */
