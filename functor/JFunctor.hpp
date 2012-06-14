#ifndef JFUNCTOR_H
#define JFUNCTOR_H

// you will see: L(0) L(1) L(2) L(3) ......
#define MY_PP_0(L)              L(0)
#define MY_PP_1(L)  MY_PP_0(L)  L(1)
#define MY_PP_2(L)  MY_PP_1(L)  L(2)
#define MY_PP_3(L)  MY_PP_2(L)  L(3)
#define MY_PP_4(L)  MY_PP_3(L)  L(4)
#define MY_PP_5(L)  MY_PP_4(L)  L(5)
#define MY_PP_6(L)  MY_PP_5(L)  L(6)
#define MY_PP_7(L)  MY_PP_6(L)  L(7)
#define MY_PP_8(L)  MY_PP_7(L)  L(8)
#define MY_PP_9(L)  MY_PP_8(L)  L(9)

// you will see: typename P1, typename P2 ......
#define TEMPLATE_ARG(L) typename P##L
#define TEMPLATE_ARG_0		       typename R
#define TEMPLATE_ARG_1 TEMPLATE_ARG_0, TEMPLATE_ARG(1)
#define TEMPLATE_ARG_2 TEMPLATE_ARG_1, TEMPLATE_ARG(2)
#define TEMPLATE_ARG_3 TEMPLATE_ARG_2, TEMPLATE_ARG(3)
#define TEMPLATE_ARG_4 TEMPLATE_ARG_3, TEMPLATE_ARG(4)
#define TEMPLATE_ARG_5 TEMPLATE_ARG_4, TEMPLATE_ARG(5)
#define TEMPLATE_ARG_6 TEMPLATE_ARG_5, TEMPLATE_ARG(6)
#define TEMPLATE_ARG_7 TEMPLATE_ARG_6, TEMPLATE_ARG(7)
#define TEMPLATE_ARG_8 TEMPLATE_ARG_7, TEMPLATE_ARG(8)
#define TEMPLATE_ARG_9 TEMPLATE_ARG_8, TEMPLATE_ARG(9)

// you will see: P1 p1, P2 p2, P3 p3 ...... 
#define FUNCTION_ARG(L) P##L p##L
#define FUNCTION_ARG_0
#define FUNCTION_ARG_1                 FUNCTION_ARG(1)
#define FUNCTION_ARG_2 FUNCTION_ARG_1, FUNCTION_ARG(2)
#define FUNCTION_ARG_3 FUNCTION_ARG_2, FUNCTION_ARG(3)
#define FUNCTION_ARG_4 FUNCTION_ARG_3, FUNCTION_ARG(4)
#define FUNCTION_ARG_5 FUNCTION_ARG_4, FUNCTION_ARG(5)
#define FUNCTION_ARG_6 FUNCTION_ARG_5, FUNCTION_ARG(6)
#define FUNCTION_ARG_7 FUNCTION_ARG_6, FUNCTION_ARG(7)
#define FUNCTION_ARG_8 FUNCTION_ARG_7, FUNCTION_ARG(8)
#define FUNCTION_ARG_9 FUNCTION_ARG_8, FUNCTION_ARG(9)

// you will see: P1, P2, P3 ...... 
#define FUNCTION_ARG2(L) P##L
#define FUNCTION_ARG2_0
#define FUNCTION_ARG2_1                  FUNCTION_ARG2(1)
#define FUNCTION_ARG2_2 FUNCTION_ARG2_1, FUNCTION_ARG2(2)
#define FUNCTION_ARG2_3 FUNCTION_ARG2_2, FUNCTION_ARG2(3)
#define FUNCTION_ARG2_4 FUNCTION_ARG2_3, FUNCTION_ARG2(4)
#define FUNCTION_ARG2_5 FUNCTION_ARG2_4, FUNCTION_ARG2(5)
#define FUNCTION_ARG2_6 FUNCTION_ARG2_5, FUNCTION_ARG2(6)
#define FUNCTION_ARG2_7 FUNCTION_ARG2_6, FUNCTION_ARG2(7)
#define FUNCTION_ARG2_8 FUNCTION_ARG2_7, FUNCTION_ARG2(8)
#define FUNCTION_ARG2_9 FUNCTION_ARG2_8, FUNCTION_ARG2(9)

// you will see: p1, p2, p3...... 
#define FUNCTION_PARAM(L) p##L
#define FUNCTION_PARAM_0
#define FUNCTION_PARAM_1                   FUNCTION_PARAM(1)
#define FUNCTION_PARAM_2 FUNCTION_PARAM_1, FUNCTION_PARAM(2)
#define FUNCTION_PARAM_3 FUNCTION_PARAM_2, FUNCTION_PARAM(3)
#define FUNCTION_PARAM_4 FUNCTION_PARAM_3, FUNCTION_PARAM(4)
#define FUNCTION_PARAM_5 FUNCTION_PARAM_4, FUNCTION_PARAM(5)
#define FUNCTION_PARAM_6 FUNCTION_PARAM_5, FUNCTION_PARAM(6)
#define FUNCTION_PARAM_7 FUNCTION_PARAM_6, FUNCTION_PARAM(7)
#define FUNCTION_PARAM_8 FUNCTION_PARAM_7, FUNCTION_PARAM(8)
#define FUNCTION_PARAM_9 FUNCTION_PARAM_8, FUNCTION_PARAM(9)


class NullClass;

template<typename signature>
class functorN;

#define NaturalSyntax(L) \
template<TEMPLATE_ARG_##L> \
class functorN< R (FUNCTION_ARG2_##L) > \
{ \
private: \
  typedef R (*functor_fp_##L)(FUNCTION_ARG_##L); \
  typedef R (NullClass::*memFun_##L)(FUNCTION_ARG_##L); \
public: \
  functorN(functor_fp_##L a) \
  { \
    isMemFun = false; \
    memcpy((void *) &m_fp, (void *) &a, sizeof(functor_fp_##L)); \
  } \
  template<typename X, typename Y> \
  functorN(X *x, R (Y::*a)(FUNCTION_ARG_##L)) \
  { \
    isMemFun = true; \
    m_pthis = x; \
    memcpy((void *) &m_memFun, (void *) &a, sizeof(memFun_##L)); \
  } \
  R operator () (FUNCTION_ARG_##L) \
  { \
    if (isMemFun) \
      return (((NullClass *) (m_pthis))->*(m_memFun))(FUNCTION_PARAM_##L); \
    else \
      return (m_fp)(FUNCTION_PARAM_##L); \
  } \
private: \
  functor_fp_##L   m_fp; \
  memFun_##L       m_memFun; \
  void             *m_pthis; \
  bool             isMemFun; \
};

MY_PP_9(NaturalSyntax)
/******************************************************************************/

template<typename ret_type = void, typename P1 = NullClass, 
         typename P2 = NullClass,  typename P3 = NullClass, 
         typename P4 = NullClass,  typename P5 = NullClass, 
         typename P6 = NullClass,  typename P7 = NullClass, 
         typename P8 = NullClass,  typename P9 = NullClass>
class functor
{
private: 
  typedef ret_type (*functor_fp)();
  typedef ret_type (NullClass::*memFun)();

public:
  functor() { }
  ~functor() { }

#define myTEMP(L) \
  typedef ret_type (*functor_fp_##L)(FUNCTION_ARG_##L); \
  typedef ret_type (NullClass::*memFun_##L)(FUNCTION_ARG_##L); \
\
  functor(functor_fp_##L a) \
  { \
    isMemFun = false; \
    memcpy((void *) &m_fp, (void *) &a, sizeof(functor_fp)); \
  } \
\
  template<typename X, typename Y> \
  functor(X *x, ret_type (Y::*a)(FUNCTION_ARG_##L)) \
  { \
    isMemFun = true; \
    m_pthis = x; \
    memcpy((void *) &m_memFun, (void *) &a, sizeof(memFun)); \
  } \
\
  ret_type operator () (FUNCTION_ARG_##L) \
  { \
    if (isMemFun) \
      return (((NullClass *) (m_pthis))->*(memFun_##L (m_memFun)))(FUNCTION_PARAM_##L); \
    else \
      return ((functor_fp_##L (m_fp)))(FUNCTION_PARAM_##L); \
  } \

MY_PP_9(myTEMP)

private:
  functor_fp   m_fp;
  memFun       m_memFun;
  void         *m_pthis;
  bool         isMemFun;
};

#endif /* JFUNCTOR_H */

