#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#include <algorithm>
#include <vector>


#include <sys/time.h>
#include <time.h>

#include <JFunctor.hpp>

class Base
{
public:
  Base() { }
  ~Base() { }

  int a() 
  { 
    return m_a; 
  }
  void a(int a_) 
  { 
    m_a = a_; 
  }
  static int static_b(int a) 
  {  
    return a;
  }

  virtual int virtual_c(int a) 
  { 
    return a; 
  }

  void e(int a) 
  { 
    printf("Base::e(), %d\n", a); 
  }
  void d(int a) 
  { 
    m_a = a;
  }
  void db(int a) 
  { 
    printf("Base::db(), %d\n", a); 
  }
  int d2(int a, int b) 
  { 
     return a+b;
  }
  int d9(int a, int b, int c, int d, int e, int f, int g, int h, int i) 
  { 
    return a+b+c+d+e+f+g+h+i;
  }
  int getBase()
  {
    return m_a;
  }

private:
  int m_a;
};

class Derived : public Base
{
public:
  int virtual_c(int a)
  {
    return 10 + a;
  }

  int Derived_a2(int a, int b)
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
  Base b;

  clock_gettime(CLOCK_REALTIME, &startTimeN);
  functor<int (int, int)> h(&Base::d2);
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

bool mycmp (int i,int j) 
{ 
  return (i<j); 
}

int main(void)
{
/***************************** Natrual Syntax ********************************/
  Base a;
  Base b;
  Base c;
  Derived aa;

  // test ordinary function
  functor<void( ) > g0(&test0);
  g0();

  functor<double (double)> g1;
  g1 = &test1;
  assert(12.123 == g1(12.123));

  // test member function
  functor<void (int)> g2(&Base::d);
  functor<int (int)> g3(&Base::static_b);
  functor<int (int, int, int, int, int, int, int, int, int)> g4(&Base::d9);
  functor<int (int)> g5(&Base::virtual_c);
  // operator =
  functor<int (int, int)> g6;
  g6 = &Derived::Derived_a2; 

  functor<int (int)> g7(&Derived::virtual_c);
  // copy constructor
  functor<int (int)> g7_2;
  g7_2 = g7;
  functor<int (int)> g7_3(g7);
  // reference 
  functor<int (int)> &g7_4 = g7;
  // pointer 
  functor<int (int)> *g7_5 = &g7;


  g2(&a, 18);
  assert(18 == a.getBase());
  assert(g3(29) == 29);
  assert(g4(&b, 1,2,3,4,5,6,7,8,9) == (1+2+3+4+5+6+7+8+9));
  assert(g5(&c, 5) == 5);
  assert(g6(&aa, 5, 6) == 5+6);
  assert(g7(&aa, 6) == 10+6);
  assert(g7_2(&aa, 6) == 10+6);
  assert(g7_3(&aa, 6) == 10+6);
  assert(g7_4(&aa, 6) == 10+6);
  assert((*g7_5)(&aa, 6) == 10+6);

/************************************* STL *************************************/
  int myints[] = {32,71,12,45,26,80,53,33};
  std::vector<int> myvector1(myints, myints+8);
  std::vector<int> myvector2(myints, myints+8);

  functor<bool (int, int)> functorCmp = &mycmp;

  std::sort(myvector1.begin(), myvector1.end());
  std::sort(myvector2.begin(), myvector2.end(), functorCmp);

  assert(myvector1.size() == myvector2.size());
  for (unsigned int i = 0; i < myvector1.size(); ++i) {
    assert(myvector1[i] == myvector2[i]);
  }

/***************************** Performance Test ********************************/
//  performanceTest (500000000);

  return 0;
}


