//
// Created by dembi on 22/06/2025.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#ifndef CONTAINERS_EXCEPTIONS_H
#define CONTAINERS_EXCEPTIONS_H

#include <exception>
using namespace std;

namespace Containers{
    class ValueNotFound : public exception{
        public:
            const char* what() const noexcept override {
                return "Value does not exists in container";
            }
    }
    class ValueOutOfBound : public exception{
      public:
        const char* what() const noexcept override {
          return "Value is out of bounds";
        }
    }

}

#endif //CONTAINERS_EXCEPTIONS_H
#endif //EXCEPTIONS_H
