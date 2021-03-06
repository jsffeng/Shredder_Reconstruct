#include <random>
#include "singleton_random.h"

#ifdef MULTI_THREAD_FLAG
#include <mutex>
#endif

using namespace std;

#ifdef UTFLAG
int SingletonRandom::s_instance_numbers_ = 0;
#endif
unsigned int SingletonRandom::s_max_val_ = 0;
std::unique_ptr<SingletonRandom> SingletonRandom::p_instance_ = nullptr;

// Lazy Singleton
SingletonRandom& SingletonRandom::GetInstance()
{
  // Following will be used if multi-threads
#ifdef MULTI_THREAD_FLAG
   static once_flag oc_flag;
#endif
  
  if (s_max_val_ == 0)
  {
    throw runtime_error("Need to set s_max_val_ value before using SingletonRandom!");	
  }

  // Following will be used if multi-threads
#ifdef MULTI_THREAD_FLAG
   call_once(oc_flag, [&](){ p_instance_.reset(new SingletonRandom);});
#else
  if (p_instance_ == nullptr)
  {
     p_instance_.reset(new SingletonRandom);
  #ifdef UTFLAG
     s_instance_numbers_++; 
  #endif 
  }
#endif
  return *p_instance_;

}

// Generate random numbers
unsigned int SingletonRandom::GenerateRandom()
{
  static default_random_engine s_engine(time(0));
  static uniform_int_distribution<unsigned> s_uniform(0, s_max_val_);

  return s_uniform(s_engine);
}
