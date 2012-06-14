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

  virtual int c() { return 0; }

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
  functor<void, int> g(&a, &A::d);
  functor<void, int> i(&A::static_b);
  functor<int, int, int, int, int, int, int, int, int, int> j(&c, &A::d9);

  g(17);
  i(21);
  assert(j(1,2,3,4,5,6,7,8,9) == (1+2+3+4+5+6+7+8+9));

  performanceTest(1000000);

  return 0;
}


