#include "dbl-wrap.h"

wrap_type_t WRAP_FUNC (__ieee754_exp) (wrap_type_t);

double
__ieee754_exp (double x)
{
  return (double) WRAP_FUNC (__ieee754_exp) ((wrap_type_t) x);
}
