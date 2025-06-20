/*
*  MIT License
*  
*  Copyright (c) 2025 Pawel Drzycimski
*  
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*  
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*  
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
*
*/

#ifndef SO_SIMPLELOG_H_
#define SO_SIMPLELOG_H_

#include <type_traits>
#include <sstream>
#include <iostream>
#include <chrono>

class SimpleLog
{
public:
  ~SimpleLog()
  {
    std::cout << m_ss.str() << std::endl;
  }

  template
  <
    typename T,
    typename
      std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, int>::type = 0
  > 
  SimpleLog& operator<<(T val)
  {
    m_ss << val;
    return *this;
  }

  SimpleLog& operator<<(const std::string &str)
  {
    m_ss << str;
    return *this;
  }

  SimpleLog& operator<<(std::string_view str)
  {
    m_ss << str;
    return *this;
  }

  SimpleLog& operator<<(const std::stringstream &ss)
  {
    m_ss << ss.str();
    return *this;
  }

  SimpleLog& operator<<(const char *c_str)
  {
    m_ss << c_str;
    return *this;
  }

  std::ostream& stream() const
  {
    return std::cout;
  }

private:
  std::stringstream m_ss;
};

#define LOG (SimpleLog{})

#define NOW() std::chrono::high_resolution_clock::now()
#define DURATION_S(start) std::chrono::duration_cast<std::chrono::seconds>(NOW() - start)
#define DURATION_MS(start) std::chrono::duration_cast<std::chrono::milliseconds>(NOW() - start)
#define DURATION_US(start) std::chrono::duration_cast<std::chrono::microseconds>(NOW() - start)

#endif
