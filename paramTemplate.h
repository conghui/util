/*
 * paramTemplate.h
 *
 *  Created on: Nov 14, 2014
 *      Author: heconghui@gmail.com
 */

#ifndef PARAMTEMPLATE_H_
#define PARAMTEMPLATE_H_

#include "recordreader.h"
#include "logger.h"

class ParamTemplate: public RecordReader {
public:
  ParamTemplate();

public: /// getters
  /// template getters
  std::string getStringRecord() const { return mStringRecord.value; }
  int getIntRecord() const { return mIntRecord.value; }
  float getFloatRecord() const { return mFloatRecord.value; }

protected: /// virtual function
  virtual void registerRecord();
  virtual void postProcess();

private:
  /// template data members
  string_record_t mStringRecord;
  int_record_t    mIntRecord;
  float_record_t  mFloatRecord;

};

#endif /* PARAMTEMPLATE_H_ */
