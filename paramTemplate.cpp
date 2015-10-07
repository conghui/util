/*
 * jobreader.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: heconghui@gmail.com
 */

#include "paramTemplate.h"

ParamTemplate::ParamTemplate() :
  mStringRecord(), mIntRecord(), mFloatRecord() {

}


void ParamTemplate::registerRecord() {
  ////////////////////////////////////////////////////////////////////////////////
  /// IMPORTANT:  IF YOU ADD OR CHANGE VALUES IN THIS SECTION, PLEASE UPDATE THE
  ///             CONFIG TEMPLATE FILES IN THE CONFIG DIRECTORY.
  ///             OTHERWISE, THE EXISTING CONFIG FILES WILL CONFUSE USERS
  ////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////// common /////////////////////////////////////
  std::string category("Common.");
  addRecord(mStringRecord.reset(category + "string_name", "."));
  addRecord(mIntRecord.reset(category + "int_name", 1));
  addRecord(mFloatRecord.reset(category + "float_name", 0.0002));

}

void ParamTemplate::postProcess() {
  /// do nothing in this function
}
