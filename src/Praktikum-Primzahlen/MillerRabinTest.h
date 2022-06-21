/*
 * MillerRabinTest.h
 */

#ifndef MILLERRABINTEST_H_
#define MILLERRABINTEST_H_

#include "integer.h"
#include "PRNG.h"

using namespace CryptoPP;

class MillerRabinTest {
public:
  static Integer modularExponentation(const Integer& a, const Integer& b,
			       const Integer& n);

  static bool witness(const Integer& a, const Integer& n);

  static bool extendedEuklid(const Integer& a, const Integer& b, Integer& d,
		      Integer& x, Integer& y);

  static bool isPrime(PRNG* rng, const Integer& n, unsigned int s);

  static Integer exp(const Integer& b, const Integer& e);

  static bool searchSqrt(const Integer& n, Integer& r);
  
  static bool searchRoot(const Integer& n, unsigned int k, Integer& r);

  static bool isIntegerPower(const Integer& n, Integer& b, unsigned int& e);


};

#endif /* MILLERRABINTEST_H_ */
