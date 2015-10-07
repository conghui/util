/*
 * Record.h
 *
 *  Created on: Nov 13, 2014
 *      Author: heconghui@gmail.com
 */

#ifndef RECORD_H_
#define RECORD_H_

#include <string>
#include <fstream>
#include <boost/variant.hpp>

template <typename value_type>
struct Record {
  ///////////////////// member functions ////////////////
  Record() : name(), value(), default_value() { }
  Record(const std::string &n, const value_type &v) : name(n), value(v), default_value(v) {}
  Record<value_type> &reset(const std::string &n, const value_type &v);
  bool operator<(const Record &rhs) const;
  bool operator>=(const Record &rhs) const;

  ///////////////////// data members ///////////////////
  std::string name;
  value_type value;
  value_type default_value;
};

/***
 * define several type to record to be read
 */
typedef Record<bool>        bool_record_t;
typedef Record<short>       short_record_t;
typedef Record<int>         int_record_t;
typedef Record<long>        long_record_t;
typedef Record<float>       float_record_t;
typedef Record<double>       double_record_t;
typedef Record<std::string> string_record_t;

/////////////////////// function implementation /////////////////
template<typename value_type>
inline Record<value_type> &Record<value_type>::reset(const std::string &n,
                                                     const value_type &v) {
  name = n;
  value = v;
  default_value = v;
  return *this;
}

template <typename value_type>
std::ostream &operator<<(std::ostream &os, const Record<value_type> &record) {
  os << record.name << "=" << record.value;
  return os;
}

std::ostream &operator<<(std::ostream &os, const Record<std::string> &record);

template<typename value_type>
inline bool Record<value_type>::operator <(const Record &rhs) const {
  return value < rhs.value;
}

template<typename value_type>
inline bool Record<value_type>::operator >=(const Record &rhs) const {
  return !(*this < rhs);
}

#endif /* RECORD_H_ */
