#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <assert.h>

#include <sys/time.h>
#include <time.h>

#include <JFunctor.hpp>

class A
{
public:
  A() { }
  ~A() { }

  int a() 
  { 
    return m_a; 
  }
  void a(int a_) 
  { 
    m_a = a_; 
  }
  static void static_b(int a) 
  {  
     printf("A::static_b(): %d\n", a); 
  }

  virtual int virtual_c(int a) 
  { 
    return a; 
  }

  void d(int a) 
  { 
    printf("A::d(), %d\n", a); 
  }
  int d2(int a, int b) 
  { 
     return a+b;
  }
  int d9(int a, int b, int c, int d, int e, int f, int g, int h, int i) 
  { 
    return a+b+c+d+e+f+g+h+i;
  }

private:
  int m_a;
};

class AA : public A
{
public:
  int virtual_c(int a)
  {
    return 10 + a;
  }

  int AA_a2(int a, int b)
  {
    return a + b;
  }
};

void test0()
{
  printf("test0\n");
}

double test1(double a)
{
  return a;
}

void performanceTest(int n = 500000000)
{
  struct timeval startTimeU, endTimeU;
  struct timespec startTimeN, endTimeN;
  A b;

  clock_gettime(CLOCK_REALTIME, &startTimeN);
  functor<int, int, int> h(&b, &A::d2);
  clock_gettime(CLOCK_REALTIME, &endTimeN);
  printf("time for creating a functor: %ld ns\n", (endTimeN.tv_sec - startTimeN.tv_sec) * 1000000000 + (endTimeN.tv_nsec - startTimeN.tv_nsec));

  clock_gettime(CLOCK_REALTIME, &startTimeN);
  h(19, 20);
  clock_gettime(CLOCK_REALTIME, &endTimeN);
  printf("time for calling functor: %ld ns\n", (endTimeN.tv_sec - startTimeN.tv_sec) * 1000000000 + (endTimeN.tv_nsec - startTimeN.tv_nsec));

  gettimeofday(&startTimeU, NULL);
  for (int counter = 0; counter < n; ++counter) {
    h(19, 20);
  }
  gettimeofday(&endTimeU, NULL);
  printf("time for calling functor for %d times: %ld us\n", n, (endTimeU.tv_sec - startTimeU.tv_sec) * 1000000 + (endTimeU.tv_usec - startTimeU.tv_usec));
}

void performanceTestN(int n = 500000000)
{
  struct timeval startTimeU, endTimeU;
  struct timespec startTimeN, endTimeN;
  A b;

  clock_gettime(CLOCK_REALTIME, &startTimeN);
  functorN<int (int, int)> h(&A::d2);
  clock_gettime(CLOCK_REALTIME, &endTimeN);
  printf("time for creating a functor: %ld ns\n", (endTimeN.tv_sec - startTimeN.tv_sec) * 1000000000 + (endTimeN.tv_nsec - startTimeN.tv_nsec));

  clock_gettime(CLOCK_REALTIME, &startTimeN);
  h(&b, 19, 20);
  clock_gettime(CLOCK_REALTIME, &endTimeN);
  printf("time for calling functor: %ld ns\n", (endTimeN.tv_sec - startTimeN.tv_sec) * 1000000000 + (endTimeN.tv_nsec - startTimeN.tv_nsec));

  gettimeofday(&startTimeU, NULL);
  for (int counter = 0; counter < n; ++counter) {
    h(&b, 19, 20);
  }
  gettimeofday(&endTimeU, NULL);
  printf("time for calling functor for %d times: %ld us\n", n, (endTimeU.tv_sec - startTimeU.tv_sec) * 1000000 + (endTimeU.tv_usec - startTimeU.tv_usec));
}

int main(void)
{
  // test ordinary function
  functor<void> f0(&test0);
  f0();

  functor<double, double> f1(&test1);
  assert(12.123 == f1(12.123));

  // test member function
  A a;
  A b;
  A c;
  AA aa;

  functor<void, int> f2(&a, &A::d);
  functor<void, int> f3(&A::static_b);
  functor<int, int, int, int, int, int, int, int, int, int> f4(&c, &A::d9);
  functor<int, int> f5(&c, &A::virtual_c);
  functor<int, int, int> f6(&aa, &AA::AA_a2);
  functor<int, int> f7(&aa, &AA::virtual_c);

  f2(17);
  f3(21);
  assert(f4(1,2,3,4,5,6,7,8,9) == (1+2+3+4+5+6+7+8+9));
  assert(f5(5) == 5);
  assert(f6(5, 6) == 5+6);
  assert(f7(6) == 10+6);

/***************************** Natrual Syntax ********************************/
  // test ordinary function
  functorN<void( ) > g0(&test0);
  g0();

  functorN<double (double)> g1;
  g1 = &test1;
  assert(12.123 == g1(12.123));

  // test member function
  functorN<void (int)> g2(&A::d);
  functorN<void (int)> g3(&A::static_b);
  functorN<int (int, int, int, int, int, int, int, int, int)> g4(&A::d9);
  functorN<int (int)> g5(&A::virtual_c);
  // operator =
  functorN<int (int, int)> g6;
  g6 = &AA::AA_a2; 

  functorN<int (int)> g7(&AA::virtual_c);
  // copy constructor
  functorN<int (int)> g7_2;
  g7_2 = g7;
  functorN<int (int)> g7_3(g7);
  // reference 
  functorN<int (int)> &g7_4 = g7;
  // pointer 
  functorN<int (int)> *g7_5 = &g7;


  g2(&a, 17);
  g3(21);
  assert(g4(&b, 1,2,3,4,5,6,7,8,9) == (1+2+3+4+5+6+7+8+9));
  assert(g5(&c, 5) == 5);
  assert(g6(&aa, 5, 6) == 5+6);
  assert(g7(&aa, 6) == 10+6);
  assert(g7_2(&aa, 6) == 10+6);
  assert(g7_3(&aa, 6) == 10+6);
  assert(g7_4(&aa, 6) == 10+6);
  assert((*g7_5)(&aa, 6) == 10+6);

  printf("size of functor<>: %ld\n", sizeof (functor<>));
  printf("size of functorN<>: %ld\n", sizeof (g7));

/***************************** Performance Test ********************************/
  performanceTest (500000000);
  performanceTestN(500000000);

  return 0;
}


