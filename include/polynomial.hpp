// Copyright 2018 Your Name <your_email>
#include <cmath>
#include <limits>
#ifndef INCLUDE_POLYNOMIAL_HPP_
#define INCLUDE_POLYNOMIAL_HPP_
template <class T>
class Polynom {
 private:
  T* Data;
  size_t dd;

 public:
  //Коструктор копирования
  Polynom(Polynom<T>& c) {
    dd = c.dd;
    if (dd != 0) {
      Data = new T[dd];
      for (size_t i = 0; i < dd; i++) {
        Data[i] = c[i];
      }
    } else {
      Data = nullptr;
    }
  }

  //Конструктор по умолчанию
  Polynom() {
    dd = 0;
    Data = nullptr;
  }

  //Пользовательский конструктор
  Polynom(const size_t d, const T* k) {
    if ((k == nullptr) || (d == 0)) {
      dd = 0;
      Data = nullptr;
    } else {
      dd = d;
      Data = new T[dd];
      for (size_t i = 0; i < dd; i++) {
        Data[i] = k[i];
      }
    }
  }

  //Деструктор
  ~Polynom() { delete[] Data; }

  Polynom& operator=(const Polynom& a) {
    if (&a != this) {
      delete[] Data;
      dd = a.dd;
      if (dd != 0) {
        Data = new T[a.dd];
        for (size_t i = 0; i < dd; i++) {
          Data[i] = a.Data[i];
        }
      } else {
        Data = nullptr;
      }
    }
    return *this;
  }

  bool operator==(const Polynom& a) const {
    bool flag = true;
    if (dd == a.dd) {
      if (std::is_floating_point<T>::value) {
        for (size_t i = 0; i < dd; i++) {
          if (abs(Data[i] - a.Data[i]) > std::numeric_limits<T>::epsilon()) {
            flag = false;
            break;
          }
        }
      } else {
        for (size_t i = 0; i < dd; i++) {
          if (Data[i] != a.Data[i]) {
            flag = false;
            break;
          }
        }
      }
    } else {
      flag = false;
    }
    return flag;
  }

  bool operator!=(const Polynom& a) const {
    bool flag = false;
    if (dd == a.dd) {
      if (std::is_floating_point<T>::value) {
        for (size_t i = 0; i < dd; i++) {
          if (abs(Data[i] - a.Data[i]) > std::numeric_limits<T>::epsilon()) {
            flag = true;
            break;
          }
        }
      } else {
        for (size_t i = 0; i < dd; i++) {
          if (Data[i] != a.Data[i]) {
            flag = true;
            break;
          }
        }
      }
    } else {
      flag = true;
    }
    return flag;
  }

  T operator[](const size_t i) const { return Data[i]; }
  T& operator[](const size_t i) { return (Data[i]); }

  //Степень
  [[nodiscard]] size_t Degree() const {
    size_t degree = 0;
    if (Data != nullptr) {
      for (size_t i = dd - 1; i >= 0; i--) {
        if (Data[i] != 0) {
          degree = i;
          break;
        }
        if (i == 0) {
          break;
        }
      }
    }
    return degree;
  }

  Polynom<T>& operator+=(const Polynom<T>& b) {
    size_t newdeg;
    size_t min;
    bool flag = true;
    if (Degree() < b.Degree()) {
      newdeg = b.Degree() + 1;
      min = Degree() + 1;
    } else {
      newdeg = Degree() + 1;
      min = b.Degree() + 1;
      flag = false;
    }
    if (Degree() == b.Degree()) {
      size_t i = Degree();
      while ((Data[i] + b[i] == 0) && (i >= 0) && (i <= Degree())) {
        if (i != 0) {
          newdeg--;
          min--;
          i--;
        } else {
          newdeg--;
          min--;
          break;
        }
      }
    }
    T* res;
    if (newdeg == 0) {
      res = nullptr;
    } else {
      res = new T[newdeg];
      for (size_t i = 0; i < min; i++) {
        res[i] = Data[i] + b[i];
      }
      if (flag) {
        for (size_t j = min; j < newdeg; j++) {
          res[j] = b[j];
        }
      } else {
        for (size_t j = min; j < newdeg; j++) {
          res[j] = Data[j];
        }
      }
    }
    delete[] Data;
    dd = newdeg;
    if (newdeg != 0) {
      Data = new T[newdeg];
      for (size_t i = 0; i < dd; i++) {
        Data[i] = res[i];
      }
    } else {
      Data = nullptr;
    }
    delete[] res;
    return *this;
    313413434
  }
  Polynom<T>& operator*(const T& d) {
    for (size_t i = 0; i < dd; i++) {
      Data[i] *= d;
    }
    return *this;
  }

  Polynom<T>& operator-=(const Polynom<T>& b) {
    size_t newdeg;
    size_t min;
    bool flag = true;
    if (Degree() < b.Degree()) {
      newdeg = b.Degree() + 1;
      min = Degree() + 1;
    } else {
      newdeg = Degree() + 1;
      min = b.Degree() + 1;
      flag = false;
    }
    if (Degree() == b.Degree()) {
      size_t i = Degree();
      while ((Data[i] - b[i] == 0) && (i >= 0) && (i <= Degree())) {
        if (i != 0) {
          newdeg--;
          min--;
          i--;
        } else {
          newdeg--;
          min--;
          break;
        }
      }
    }
    T* res;
    if (newdeg == 0) {
      res = nullptr;
    } else {
      res = new T[newdeg];
      for (size_t i = 0; i < min; i++) {
        res[i] = Data[i] - b[i];
      }
      if (flag) {
        for (size_t j = min; j < newdeg; j++) {
          res[j] = -b[j];
        }
      } else {
        for (size_t j = min; j < newdeg; j++) {
          res[j] = Data[j];
        }
      }
    }
    delete[] Data;
    dd = newdeg;
    if (newdeg != 0) {
      Data = new T[newdeg];
      for (size_t i = 0; i < dd; i++) {
        Data[i] = res[i];
      }
    } else {
      Data = nullptr;
    }
    delete[] res;
    return *this;
  }

  Polynom<T>& operator*=(const Polynom<T>& a) {
    size_t sa = a.Degree();
    size_t sb = Degree();
    if (((a[0] == 0) && (sa == 0)) || ((Data[0] == 0) && (sb == 0))) {
      delete[] Data;
      Data = nullptr;
      dd = 0;
    } else {
      size_t newdeg = sa + sb + 1;
      T* res = new T[newdeg];
      for (size_t k = 0; k < newdeg; k++) {
        res[k] = 0;
      }
      for (size_t i = 0; i < sa + 1; i++) {
        for (size_t j = 0; j < sb + 1; j++) {
          res[i + j] += a[i] * Data[j];
        }
      }
      delete[] Data;
      dd = newdeg;
      Data = new T[dd];
      for (size_t i = 0; i < dd; i++) {
        Data[i] = res[i];
      }
      delete[] res;
    }
    return *this;
  }

  Polynom<double>& operator/=(const Polynom<double>& b) {
    if (((Data == nullptr) || ((Degree() == 0) && (Data[0] == 0))) ||
        (((b.Degree() == 0) && (b[0] == 0)) || (b.Data == nullptr))) {
      return *this;
    } else {
      auto* copyofa = new double[Degree() + 1];
      for (size_t i = 0; i < Degree() + 1; i++) {
        copyofa[i] = Data[i];
      }
      Polynom<double> acp(Degree() + 1, copyofa);
      auto* copyofb = new double[b.Degree() + 1];
      for (size_t i = 0; i < b.Degree() + 1; i++) {
        copyofb[i] = b[i];
      }
      Polynom<double> bcp(b.Degree() + 1, copyofb);
      if (Degree() < b.Degree()) {
        delete[] Data;
        dd = 1;
        Data = new double[1];
        Data[0] = 0;
        return *this;
      } else {
        double* res;
        res = new double[Degree() - b.Degree() + 1];
        double* min;
        min = new double[acp.Degree() - bcp.Degree() + 1];
        while (acp.Degree() >= bcp.Degree()) {
          size_t delimoe = acp.Degree();
          size_t delitel = bcp.Degree();
          res[delimoe - delitel] = acp[acp.Degree()] / bcp[bcp.Degree()];
          for (size_t i = 0; i < acp.Degree() - bcp.Degree() + 1; i++) {
            min[i] = 0;
          }
          min[delimoe - delitel] = res[delimoe - delitel];
          Polynom<double> m(delimoe - delitel + 1, min);
          m *= bcp;
          acp -= m;
        }
        dd = Degree() - b.Degree() + 1;
        delete[] Data;
        Data = new double[dd];
        for (size_t i = 0; i < dd; i++) {
          Data[i] = res[i];
        }
        delete[] res;
        delete[] copyofa;
        delete[] copyofb;
        delete[] min;
        return *this;
      }
    }
  }

  Polynom<double>& operator%=(const Polynom<double>& a) {
    if ((a.Data == nullptr) || ((a.Degree() == 0) && (a[0] == 0))) {
      return *this;
    } else {
      auto* n = new double[dd];
      for (size_t i = 0; i < dd; i++) {
        n[i] = Data[i];
      }
      Polynom<double> ch(dd, n);
      Polynom<double> cp(dd, n);
      ch /= a;
      ch *= a;
      cp -= ch;
      delete[] Data;
      if (cp.Data != nullptr) {
        dd = cp.Degree() + 1;
        Data = new double[dd];
        for (size_t i = 0; i < dd; i++) {
          Data[i] = cp[i];
        }
      } else {
        dd = 0;
        Data = nullptr;
      }
      delete[] n;
      return *this;
    }
  }

  T Func(const T x) {
    T arg = 1;
    T result = 0;
    for (size_t i = 0; i < dd; i++) {
      if (i != 0) {
        arg *= x;
      }
      result += Data[i] * arg;
    }
    return result;
  }
};

template <class T>
Polynom<T> operator+(const Polynom<T>& a, const Polynom<T>& b) {
  size_t newdeg;
  size_t min;
  bool flag = true;
  if (a.Degree() < b.Degree()) {
    newdeg = b.Degree() + 1;
    min = a.Degree() + 1;
  } else {
    newdeg = a.Degree() + 1;
    min = b.Degree() + 1;
    flag = false;
  }
  if (a.Degree() == b.Degree()) {
    size_t i = a.Degree();
    while ((a[i] + b[i] == 0) && (i >= 0) && (i <= a.Degree())) {
      if (i != 0) {
        newdeg--;
        min--;
        i--;
      } else {
        newdeg--;
        min--;
        break;
      }
    }
  }
  T* res;
  if (newdeg == 0) {
    res = nullptr;
  } else {
    res = new T[newdeg];
    for (size_t i = 0; i < min; i++) {
      res[i] = a[i] + b[i];
    }
    if (flag) {
      for (size_t j = min; j < newdeg; j++) {
        res[j] = b[j];
      }
    } else {
      for (size_t j = min; j < newdeg; j++) {
        res[j] = a[j];
      }
    }
  }
  Polynom<T> result(newdeg, res);
  delete[] res;
  return result;
}

template <class T>
Polynom<T> operator-(const Polynom<T>& a, const Polynom<T>& b) {
  size_t newdeg;
  size_t min;
  bool flag = true;
  if (a.Degree() < b.Degree()) {
    newdeg = b.Degree() + 1;
    min = a.Degree() + 1;
  } else {
    newdeg = a.Degree() + 1;
    min = b.Degree() + 1;
    flag = false;
  }
  if (a.Degree() == b.Degree()) {
    size_t i = a.Degree();
    while ((a[i] - b[i] == 0) && (i >= 0) && (i <= a.Degree())) {
      if (i != 0) {
        newdeg--;
        min--;
        i--;
      } else {
        newdeg--;
        min--;
        break;
      }
    }
  }
  T* res;
  if (newdeg == 0) {
    res = nullptr;
  } else {
    res = new T[newdeg];
    for (size_t i = 0; i < min; i++) {
      res[i] = a[i] - b[i];
    }
    if (flag) {
      for (size_t j = min; j < newdeg; j++) {
        res[j] = -b[j];
      }
    } else {
      for (size_t j = min; j < newdeg; j++) {
        res[j] = a[j];
      }
    }
  }
  Polynom<T> result(newdeg, res);
  delete[] res;
  return result;
}

template <class T>
Polynom<T> operator*(const Polynom<T>& a, const Polynom<T>& b) {
  size_t sa = a.Degree();
  size_t sb = b.Degree();
  size_t newdeg;
  T* res;
  if (((sa == 0) && (a[0] == 0)) || ((sb == 0) && (b[0] == 0))) {
    res = nullptr;
    newdeg = 0;
  } else {
    newdeg = sa + sb + 1;
    res = new T[newdeg];
    for (size_t k = 0; k < newdeg; k++) {
      res[k] = 0;
    }
    for (size_t i = 0; i < sa + 1; i++) {
      for (size_t j = 0; j < sb + 1; j++) {
        res[i + j] += a[i] * b[j];
      }
    }
  }
  Polynom<T> result(newdeg, res);
  delete[] res;
  return result;
}

template <class T>
Polynom<double> operator/(const Polynom<T>& a, const Polynom<T>& b) {
  if (((a.Degree() == 0) && (a[0] == 0)) ||
      ((b.Degree() == 0) && (b[0] == 0))) {
    auto* copyofa = new double[a.Degree() + 1];
    for (size_t i = 0; i < a.Degree() + 1; i++) {
      copyofa[i] = a[i];
    }
    Polynom<double> acp(a.Degree() + 1, copyofa);
    delete[] copyofa;
    return acp;
  } else {
    auto* copyofa = new double[a.Degree() + 1];
    for (size_t i = 0; i < a.Degree() + 1; i++) {
      copyofa[i] = a[i];
    }
    Polynom<double> acp(a.Degree() + 1, copyofa);
    auto* copyofb = new double[b.Degree() + 1];
    for (size_t i = 0; i < b.Degree() + 1; i++) {
      copyofb[i] = b[i];
    }
    Polynom<double> bcp(b.Degree() + 1, copyofb);
    delete[] copyofa;
    delete[] copyofb;
    if (a.Degree() < b.Degree()) {
      double* r;
      r = new double[1];
      r[0] = 0;
      Polynom<double> result(1, r);
      delete[] r;
      return result;
    } else {
      double* res;
      res = new double[a.Degree() - b.Degree() + 1];
      while (acp.Degree() >= bcp.Degree()) {
        size_t delimoe = acp.Degree();
        size_t delitel = bcp.Degree();
        res[delimoe - delitel] = acp[acp.Degree()] / bcp[bcp.Degree()];
        auto* min = new double[delimoe - delitel + 1];
        for (size_t i = 0; i < delimoe - delitel + 1; i++) {
          min[i] = 0;
        }
        min[delimoe - delitel] = res[delimoe - delitel];
        Polynom<double> m(delimoe - delitel + 1, min);
        acp = acp - m * bcp;
        delete[] min;
      }
      Polynom<double> result(a.Degree() - b.Degree() + 1, res);
      delete[] res;
      return result;
    }
  }
}

Polynom<double> operator%(const Polynom<double>& a, const Polynom<double>& b) {
  if ((b.Degree() == 0) && (b[0] == 0)) {
    Polynom<double> res;
    res = a;
    return res;
  } else {
    Polynom<double> ch = a / b;
    ch *= b;
    Polynom<double> result = a - ch;
    return result;
  }
}

#endif  // INCLUDE_POLYNOMIAL_HPP_
