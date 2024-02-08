#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <exception>
using namespace std;

class Not_Found : public exception {
public:
    const char* what() const noexcept override ;
};
class Bad_request: public exception {
public:
    const char* what() const noexcept override ;
};
class Permission_denied : public exception {
public:
    const char* what() const noexcept override ;
};

#endif