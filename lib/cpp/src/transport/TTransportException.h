#ifndef _THRIFT_TRANSPORT_TTRANSPORTEXCEPTION_H_
#define _THRIFT_TRANSPORT_TTRANSPORTEXCEPTION_H_ 1

#include <boost/lexical_cast.hpp>
#include <string>

namespace facebook { namespace thrift { namespace transport { 

/**
 * Error codes for the various types of exceptions.
 */
enum TTransportExceptionType {
  TTX_UNKNOWN = 0,
  TTX_NOT_OPEN = 1,
  TTX_TIMED_OUT = 2,
  TTX_EOF = 3,
};

/**
 * Class to encapsulate all the possible types of transport errors that may
 * occur in various transport systems. This provides a sort of generic
 * wrapper around the shitty UNIX E_ error codes that lets a common code
 * base of error handling to be used for various types of transports, i.e.
 * pipes etc.
 *
 * @author Mark Slee <mcslee@facebook.com>
 */
class TTransportException : public facebook::thrift::TException {
 public:
  TTransportException() :
    facebook::thrift::TException(),
    type_(TTX_UNKNOWN) {}

  TTransportException(TTransportExceptionType type) :
    facebook::thrift::TException(), 
    type_(type) {}

  TTransportException(const std::string message) :
    facebook::thrift::TException(message),
    type_(TTX_UNKNOWN) {}

  TTransportException(TTransportExceptionType type, const std::string message) :
    facebook::thrift::TException(message),
    type_(type) {}

  virtual ~TTransportException() throw() {}

  /**
   * Returns an error code that provides information about the type of error
   * that has occurred.
   *
   * @return Error code
   */
  TTransportExceptionType getType() {
    return type_;
  }

  virtual const char* what() const throw() {
    if (message_.empty()) {
      return (std::string("Default Transport Exception: ") +
        boost::lexical_cast<std::string>(type_)).c_str();
    } else {
      return message_.c_str();
    }
  }
 
 protected:
  /** Error code */
  TTransportExceptionType type_;

};

}}} // facebook::thrift::transport

#endif // #ifndef _THRIFT_TRANSPORT_TTRANSPORTEXCEPTION_H_
